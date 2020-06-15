#ifndef LISTENER_H
#define LISTENER_H

#include <QObject>
#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QMap>
#include <QListWidget>

#define MMDB "geoip.mmdb"


class Listener : public QObject
{
    Q_OBJECT

    public:
        explicit Listener(QListWidget *dest, QObject *parent = Q_NULLPTR);

        QTcpSocket* getConnection(QListWidgetItem *item) const;
        void startListening(int port);
        void suspendListen();

        bool isListening();

    private slots:
        void newConnection();
        void clientDisconnected();

    private:
        QTcpServer *_listener_sock = nullptr;
        QMap<QTcpSocket*, QListWidgetItem *> _clients;
        QListWidget *_list = nullptr;

};

#endif // LISTENER_H

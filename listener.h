#ifndef LISTENER_H
#define LISTENER_H

#include <QDialog>
#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QMap>
#include <QListWidget>


class Listener : public QDialog
{
    Q_OBJECT

    public:
        Listener(int port, QListWidget *dest);
        ~Listener();

        void getConnection(int id);

    private slots:
        void newConnection();
        void clientDisconnected();

    private:
        QTcpServer *_listener_sock = nullptr;
        QMap<QTcpSocket *, QListWidgetItem *> _clients;
        QListWidget *_list = nullptr;

};

#endif // LISTENER_H

#ifndef CLIENTSHELL_H
#define CLIENTSHELL_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui { class ClientShell; }
QT_END_NAMESPACE

class ClientShell : public QMainWindow
{
    Q_OBJECT

    public:
        ClientShell(QTcpSocket *connection, QWidget *parent = nullptr);
        ~ClientShell();

    public slots:
        void sendCmd();
        void printData();


    private:
        void closeEvent(QCloseEvent *event);

        QTcpSocket *_conn = nullptr;
        Ui::ClientShell *_ui = nullptr;
};

#endif // CLIENTSHELL_H

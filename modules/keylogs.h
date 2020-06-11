#ifndef KEYLOGS_H
#define KEYLOGS_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QGridLayout>
#include <QTextEdit>
#include <QCloseEvent>

class Keylogs : public QMainWindow
{
    Q_OBJECT
    public:
        explicit Keylogs(QTcpSocket* conn, QWidget *parent = nullptr);
        ~Keylogs();

        void closeEvent(QCloseEvent *event);

    public slots:
        void printData();

    private:
        QGridLayout *_main = nullptr;
        QTextEdit *_text = nullptr;
        QWidget *_cent = nullptr;
        QTcpSocket *_conn = nullptr;
};

#endif // KEYLOGS_H

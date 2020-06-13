#ifndef EXPLORER_H
#define EXPLORER_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QListWidgetItem>
#include <QSharedPointer>
#include <QCloseEvent>
#include <QStack>
#include <QPoint>
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui { class ExplorerWindow; }
QT_END_NAMESPACE

class Explorer : public QMainWindow
{
    Q_OBJECT
    public:
        explicit Explorer(QTcpSocket *con, QWidget *parent = nullptr);
        ~Explorer();
        void listDir();

        void closeEvent(QCloseEvent *event);

   signals:
        void buildReady();

    public slots:
        void readSock();
        void buildListView();

        void gotoDir();
        void backHistory();
        void naviguate(QListWidgetItem *item);

        void contextMenu(const QPoint &pos);

    private:
        QTcpSocket *_conn;
        Ui::ExplorerWindow *ui;
        QString _rawData;
        QString _current_dir;
        QStack<QString> _history;
        QMenu *_file_actions;

        QIcon _folder_ico;
        QIcon _file_ico;

};

#endif // EXPLORER_H

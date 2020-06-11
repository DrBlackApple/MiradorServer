#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QMenu>
#include "listener.h"

#include "modules/clientshell.h"
#include "modules/keylogs.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public slots:
        void listen();
        void contextMenu(const QPoint &pos);

        //menu action
        void openShell();
        void getKeys();

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        void clearWindows();

        Ui::MainWindow *ui = nullptr;
        Listener *_li = nullptr;
        QMenu *_actions = nullptr;

        ClientShell *_rem_sh = nullptr;
        Keylogs* _out_keys = nullptr;
};
#endif // MAINWINDOW_H

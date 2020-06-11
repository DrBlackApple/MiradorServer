#include "mainwindow.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFontDatabase::addApplicationFont(":/font/Mermaid1001.ttf");
    QFont font;
    font.setFamily("Mermaid1001");
    font.setPointSize(10);
    a.setFont(font);

    MainWindow w;

    w.show();
    return a.exec();
}

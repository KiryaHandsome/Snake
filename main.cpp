#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Snake");
    w.setBackgroundRole(QPalette::Dark);
    w.show();
    return a.exec();
}

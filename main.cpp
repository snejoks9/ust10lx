#include "mainwindow.h"
#include "Decode.h"
#include <QApplication>
#include <QtOpenGL>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.conn();
    w.show();
    return a.exec();
}

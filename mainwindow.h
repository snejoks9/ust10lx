#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QNetworkRequest>
#include <unistd.h>
#include <string.h>
#include <QVector>

#include "lidarsim.h"
#include "decode.h"
#include <QDebug>
#include <QtNetwork/QHostAddress>
#include <QtOpenGL>
#include <iostream>
#include <drawer3d.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    const int choose = 2;
    const int strElem = 250;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QByteArray GD;
    QByteArray StartStep = "0000";
    QByteArray EndStep = "0100";
    QByteArray ClusterCount = "00";
    QByteArray ScanInterval = "0";
    QByteArray NumberOfScans = "00";

    void conn();
    int getChoose();

    QVector<double> mainFunc();

    struct Coordinates
    {
        double x;
        double y;
        double z;
    }coord;
    QVector<Coordinates> CoordVec;
    int getStrElem();
    QVector<struct Coordinates> getvecX();

public slots:
    void onConnected();
    void onReadyRead();
    void test();
    void resizeEvent(QResizeEvent *event);

private:

    Ui::MainWindow *ui;
    QTcpSocket  _socket;
    QByteArray responseRaw;
    drawer3D* Drawer3D;

};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "decode.h"

#include <QDebug>
#include <QtNetwork/QHostAddress>
#include <QtOpenGL>
#include "drawer3d.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _socket(this)
{
    qDebug() << "mainwindow constructor";

    ui->setupUi(this);

    connect(&_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(&_socket, SIGNAL(connected()), this, SLOT(onConnected()));

    /////////
    connect(&_socket, SIGNAL(hostFound()), this, SLOT(test()));
    ////////

    _socket.connectToHost(QHostAddress("192.168.0.10"), 10940);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onConnected()
{
    qDebug() << "connected!";
    char msg[100];

    sprintf(msg,"BM\n");
    qDebug() << "BM request!\n";
    _socket.write(msg);

    _socket.waitForBytesWritten(100);

    QByteArray gdresp = "GD0000010000\n";
    qDebug() << "msg: " <<  gdresp;
    _socket.write(gdresp);

}


void MainWindow::onReadyRead()
{
    QByteArray responseRaw = _socket.readAll();
    qDebug() << "response: " << responseRaw;
    qDebug() << "end response";
}

void MainWindow::test(){

    //        responseRaw = "GD0000010000\n00P\nTGQjF\n"
    //                      "08A08;08908808408108907S07R08>08U09409J09G09F08G07o07W07W07U07;0g\n"
    //                      "6f06R06Y06U06W06c07J08608J08408G08808J08R09P09P09A09=09D09U09X093\n"
    //                      "X09P09R09C0:G15M15Q15V?om?om?om?om1:81:=19n?om?om?om?om?om?om?omK\n"
    //                      "?om?om?om1S`1Se1Sk1TU1XO1YA1YM1YM0bl0bi0bi0c60bj0c00c?0cE0cC0cB0i\n"
    //                      "cP0cV0cV0ce0ce0cY0a`0_f0_J0^i0^R0^@0]I0\\[0[o0[A8\n\n";

        responseRaw = "GD0000010000\n00P\nTGQjF\n"
                      "0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0D\n"
                      "AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AD\n"
                      "N0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AND\n"
                      "0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0D\n"
                      "0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0D\n"
                      "AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AD\n"
                      "N0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AND\n\n";

//    responseRaw = "GD0000010000\n00P\nTGQjF\n"
//                  "00i00i00i00i00k00k00n01101101101101101101100o00m00o00o0130130140]\n"
//                  "14012012014015017017017016017017016016015015015014014014014015010\n"
//                  "501801<01<01?01D01D01D01F01F01L01O01R01T01V01W01X01X01X01Z01Z01Ze\n"
//                  "01001b01j02;02`09H09H09Z09Z09_0:90:90:@0:@0:@0:;0:@0:;0:;0:90:90]\n"
//                  "9Z08X08408408408608608608408408408408908908908908808608308008008V\n"
//                  "007m07m07j07h07h07h07d06E04D04>04=04=04>04C04H04H04I04J04K04U04Ue\n";

    mainFunc();
}



int MainWindow::mainFunc(){

    Decode d;

    // qDebug() << responseRaw;
    QByteArray rangeData = d.clear(responseRaw);

    for(int i = 0; i < rangeData.size()/3;i++ ){
        d.getCoordinates(rangeData);
        x.append(d.getX());
        y.append(d.getY());
        // qDebug() << x.at(i) << y.at(i);
    }

    /// 3D
    Drawer3D = new drawer3D(ui->OGLQuad);
    Drawer3D->resize(1920,1080);

}

QVector<double> MainWindow::getVecX(){
    return x;
}

QVector<double> MainWindow::getVecY(){
    return y;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Drawer3D->resize(event->size().width(),event->size().height());
}


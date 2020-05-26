#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _socket(this)
{
    ui->setupUi(this);
}

void MainWindow::conn(){
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
    QByteArray GD = "GD" + StartStep + EndStep + ClusterCount + "\n";
    QByteArray MD = "MD" + StartStep + EndStep + ClusterCount + ScanInterval + NumberOfScans + "\n";

    sprintf(msg,"BM\n");
    qDebug() << "BM request!\n";
    _socket.write(msg);

    _socket.waitForBytesWritten(100);

    QByteArray gdresp = GD;
    qDebug() << "msg: " <<  GD;
    _socket.write(gdresp);

}


void MainWindow::onReadyRead()
{
    QByteArray responseRaw = "GD0000010000\n"
                  "00P\n"
                  "TGQjF\n"
                  "0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0?X0?X0?X0?X0?X0?X0?X0?X0?X0?X0D\n"
                  "?X0?X0?X0?X0?X0?X0?X0?X0?X0?X0?X0?X0?X0?l0?l0?l0@@0@@0@@0@^0@^0@D\n"
                  "^0A<0A<0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AND\n";

    QFile outData("outdata.txt");

    if(outData.open(QIODevice::ReadWrite| QIODevice::Text))
    {
        QTextStream writeData(&outData);

        for(int j = 0; j < responseRaw.size(); j++){
            writeData << responseRaw[j];
        }
    }

  // QByteArray responseRaw = _socket.readAll();
    qDebug() << "response: " << responseRaw;
    qDebug() << "end response";
}

void MainWindow::test(){
    LidarSim ls;
    mainFunc();
}

QVector<double> MainWindow::mainFunc(){

    Decode d;
    QByteArray GD = "GD" + StartStep + EndStep + ClusterCount + "\n";
    QByteArray MD = "MD" + StartStep + EndStep + ClusterCount + ScanInterval + NumberOfScans + "\n";

    if(choose == 1){
        QFile outData("outdata.txt");
        responseRaw.clear();
        if(outData.open(QIODevice::ReadWrite| QIODevice::Text)) // Читаем записанные данные
        {
            QTextStream writeData(&outData);
            while(!writeData.atEnd()){
                responseRaw.append(writeData.readLine());
            }
        }

        QByteArray rangeData = d.clear(responseRaw);

        for(int i = 0; i < rangeData.size()/3;i++ ){
            d.getCoordinatesFor1(rangeData);
            coord = {d.getX(), d.getY(), d.getZ()};
            CoordVec.append(coord);
            qDebug() << d.getX();
        }
    }
    if (choose == 2){
        QFile rovData("digitData.txt");
        QVector<QString> rovRaw;
        if(rovData.open(QIODevice::ReadWrite| QIODevice::Text)) // Читаем записанные данные
        {
            QTextStream writeData(&rovData);
            while(!writeData.atEnd()){
                rovRaw.append(writeData.readLine());
            }
        }

        double z = 0;
        int j = 0;

        for(int i = 0; i < rovRaw.size(); i++) {
            if(i%strElem==0){
                j = 0;
                z+=0.0075;
            }
            qDebug() << i << j << z;
            d.getCoordinatesFor2(rovRaw,i,j);
            coord = {d.getX(), d.getY(), z};
            CoordVec.append(coord);
            j++;
        }
    }

    QFile outCoord("outcoord.txt");
    QTextStream writeCoord(&outCoord);

    if(outCoord.open(QIODevice::ReadWrite| QIODevice::Text)) // Записываем координаты
    {
        for(int i = 0; i < CoordVec.size(); i++){
            writeCoord << CoordVec[i].x << "\n";
            writeCoord << CoordVec[i].y << "\n";
            writeCoord << CoordVec[i].z << "\n";

        }
    }
    QByteArray responseRaw = "GD0000010000\n"
                  "00P\n"
                  "TGQjF\n"
                  "0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0?X0?X0?X0?X0?X0?X0?X0?X0?X0?X0D\n"
                  "?X0?X0?X0?X0?X0?X0?X0?X0?X0?X0?X0?X0?X0?l0?l0?l0@@0@@0@@0@^0@^0@D\n"
                  "^0A<0A<0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AN0AND\n";
    qDebug() << responseRaw;

    ///// 3D
    Drawer3D = new drawer3D(ui->OGLQuad);
    Drawer3D->resize(1920,1080);

}

QVector<MainWindow::Coordinates> MainWindow::getvecX(){
    return CoordVec;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Drawer3D->resize(event->size().width(),event->size().height());
}

int MainWindow::getStrElem(){
    return strElem;
}

int MainWindow::getChoose(){
    return choose;
}

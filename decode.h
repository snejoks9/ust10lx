#ifndef DECODE_H
#define DECODE_H
#include <QCoreApplication>
#include <QDebug>
#include "lidarsim.h"
#include <QFile>
#include <QTextStream>

#define PI 3.14
class Decode
{

private:

    int bytesForData = 3;
    double angleMin = -180;
    double angleResolution = 0.25;
    double tetha = 0;
    double x = 0;
    double y = 0;
    double z = 0;
    int i = 0, j = 0;

    QByteArray gdresp = "GD0000010000\n";        // Запрос лидару, потом уберу
    QByteArray threeBytes;                       // Массив, содержащий одну информацию о расстоянии
    QByteArray rangeData;

    int decodeByte(QByteArray code, int byte);   // Декодирование

public:
    double getX();
    double getY();
    double getZ();

    int getSize();
    QVector<double> vecX;
    QVector<double> getVec();


    decode();
    QByteArray clear(QByteArray rangeData);      // Функция, оставляющая в полученном ответе только данные о расстоянии
    void getCoordinatesFor1(QByteArray rangeData);   // Функция, получающая координаты точек
    void getCoordinatesFor2(QVector<QString> rovRaw, int i, int j);

};

#endif // DECODE_H

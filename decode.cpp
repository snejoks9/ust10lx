#include "Decode.h"

Decode::decode()
{
}

int Decode::decodeByte(QByteArray code, int byte) {
    int value = 0;
    int i;
    for (i = 0; i < byte; ++i) {
        value <<= 6;
        value &= ~0x3f;
        value |= code[i] - 0x30;
    }
    return value;
}

QByteArray Decode::clear(QByteArray rangeData){
    int offset = 20;

    for(int i = 0; i<rangeData.size()-offset; i++){   // Оставляем только данные о расстоянии
        rangeData[i] = rangeData[i+offset];
    }

    rangeData.resize(rangeData.size()-offset);

    for (int i = 1; i < (rangeData.size()/65)+1; i++){ // Убираем байт контрольной суммы
        rangeData.remove(64*i,1);
    }
    rangeData.remove(rangeData.size()-1,1);
    qDebug() << rangeData;
    return rangeData;
}

void Decode::getCoordinatesFor1(QByteArray rangeData){

    threeBytes.append(rangeData[0+j]);
    threeBytes.append(rangeData[1+j]);
    threeBytes.append(rangeData[2+j]);

    double range = Decode::decodeByte(threeBytes, threeBytes.size());

    if(range != 65533 && range != 4){

        range = range/1000;

        tetha = (angleMin + i*angleResolution) * PI/180;
        x = range * cos(tetha);
        y = range * sin(tetha);

        if(i % 64 == 0){
            i = 0;
            z += 0.03;
        }
        qDebug() << threeBytes << range << i << z;
        i++;
        threeBytes.clear();
    }
    j+=3;
}

void Decode::getCoordinatesFor2(QVector<QString> rovRaw,int i, int j){
        double rR = rovRaw[i].toDouble();
        angleMin = -200;
        double tetha = (angleMin + j*angleResolution) * PI/180;
        x = rR*sin(tetha);
        y = rR*cos(tetha);

}

double Decode::getX(){
    return x;
}

double Decode::getY(){
    return y;
}

double Decode::getZ(){
    return z;
}

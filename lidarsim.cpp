#include "lidarsim.h"

LidarSim::LidarSim()
{
    responseRaw = "GD0000010000\n"
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
}


#ifndef LIDARSIM_H
#define LIDARSIM_H
#include <QByteArray>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class LidarSim
{
public:
    LidarSim();
    QByteArray responseRaw;
};

#endif // LIDARSIM_H

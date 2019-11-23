#ifndef MQFactory_H
#define MQFactory_H

#include "IMQ.h"

enum MQS { Mq7 = 0, Mq9, Mq131, Mq135};

class MQFactory
{
public:
    MQFactory(double _actualTemp = 20.0, double _actualHum = 65.0);
    ~MQFactory();
    IMQ* createMQ(int sensor, int MqPin);
private:
    double actualHum;
    double actualTemp;
    bool timeElapsed;
};

#endif // MQFactory_H

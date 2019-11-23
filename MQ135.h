#ifndef MQ135_H
#define MQ135_H
#include "Ecuation.h"
#include "MQImpl.h"

class MQ135: public MQImpl
{
public:
    MQ135(int _mqPin);
    ~MQ135();
    String Label();
private:
    MQ135();
};

#endif // MQ135_H

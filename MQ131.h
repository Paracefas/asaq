#ifndef MQ131_H
#define MQ131_H
#include "Ecuation.h"
#include "MQImpl.h"

class MQ131: public MQImpl
{
public:
    MQ131(int _mqPin);
    ~MQ131();    
    String Label();
private:
    MQ131();
};

#endif // MQ131_H

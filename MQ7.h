#ifndef MQ7_H
#define MQ7_H
#include "Ecuation.h"
#include "MQImpl.h"

class MQ7: public MQImpl
{
public:
    MQ7(int _mqPin);
    ~MQ7();
    String Label();
private:
    MQ7();
};

#endif // MQ7_H

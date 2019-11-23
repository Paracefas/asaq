#ifndef MQ9_H
#define MQ9_H
#include "Ecuation.h"
#include "MQImpl.h"

class MQ9: public MQImpl
{
public:
    MQ9(int _mqPin);
    ~MQ9();    
    String Label();
private:
    MQ9();
};

#endif // MQ9_H

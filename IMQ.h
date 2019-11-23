#ifndef IMQ_H
#define IMQ_H
#include <Arduino.h>

struct IMQ
{
    virtual ~IMQ() {}
    virtual double getPPMCorrected() = 0;
    virtual void setRo(long) = 0;
    virtual double getPPM() = 0;
    virtual void setTempYHumValues(double, double) = 0;
    virtual String Label() = 0; 
};

#endif // IMQ_H

#ifndef MQIMPL_H
#define MQIMPL_H

#include "IMQ.h"

#include "Ecuation.h"
#include <math.h>
#include <Arduino.h>

const double READ_SAMPLE_INTERVAL = 1000;
const double READ_SAMPLE_TIMES = 30;
const double ANALOG_RESOLUTION = 1024;
const int MQ_RSROTEMPHUMDGAINPREVENTOUTOFLIMITS = 1;


class MQImpl : public IMQ
{
protected:
    int TempPoints;
    double *Ratio33Hum;
    double *Ratio85Hum;
    double *Temperatures;
    double Hum1Value;//33
    double Hum2Value;//85
    double senRefTemp;//20
    double senRefHum;//65
    double actualTemp;
    double actualHum;
    double maxrsro;
    double minrsro;
    Ecuation ecuationValues;
    int mqPin;
    long RL;
    long Ro;
    long staticRo;
    long RoCorrected;
    double defaultPPM;
    bool correctedRoFlag;
    int countCorrected;
    
    long unsigned int getRo(double);
    long unsigned int getRoCorrected();
    double rsRoTHdiff(double, double);
public:
    virtual ~MQImpl();
    void setTempYHumValues(double, double);
    void setRo(long);
    double readMq();
    double getPPM();
    double getPPMCorrected();
    virtual String Label() = 0; 
};

#endif

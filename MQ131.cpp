#include "MQ131.h"
#include "Math.h"
#include "Arduino.h"

#include <string>

MQ131::MQ131()
{
}

MQ131::MQ131(int _mqPin)
{
    double lista[]={    -10,      0,     10,     20,     30,     40,     50 };
    double _Ratio33Hum[] = {1.7, 1.58, 1.45, 1.28, 1.15, 1.00, 0.88}; // MQ131
    double _Ratio85Hum[] = {1.27, 1.18,1.05, 0.92, 0.85, 0.73, 0.65}; // MQ131
    Ecuation _ecuation{ 0.356, 0.446 };
    double _defaultPPM = 0.04;
    unsigned long int_RL = 10000;
    double _maxrsro = 2000.0;
    double _minrsro = 0.01;
    Hum1Value = 33;//33
    Hum2Value = 85;//85
    senRefTemp = 20;//20
    senRefHum = 65;//65
    correctedRoFlag = false;
    Temperatures=lista;
    TempPoints = 7;
    mqPin = _mqPin;
    defaultPPM = _defaultPPM;
    RL = int_RL;
    ecuationValues = _ecuation;
    maxrsro = _maxrsro;
    minrsro = _minrsro;
    Ratio33Hum = _Ratio33Hum;
    Ratio85Hum = _Ratio85Hum;
    countCorrected = 0;
    staticRo = 0;//poner un valor ya medido
    Ro = staticRo;
}

MQ131::~MQ131()
{
    //dtor
}

String MQ131::Label()
{
    
    return "O3"; 
}

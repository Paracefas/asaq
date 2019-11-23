#include "MQ7.h"
#include "Math.h"
#include "Arduino.h"
#include <string>

MQ7::MQ7()
{
}

MQ7::MQ7(int _mqPin)
{
    double lista[]={    -10,      0,     10,     20,     30,     40,     50 };
    double _Ratio33Hum[] = {1.7, 1.58, 1.43, 1.28, 1.15, 0.95, 0.79}; // MQ7
    double _Ratio85Hum[] = {1.28, 1.18, 0.988, 0.91, 0.87, 0.71, 0.63}; // MQ7
    Ecuation _ecuation{ 64.865, -1.405 };
    double _defaultPPM = 1.26;
    unsigned long int_RL = 10000;
    double _maxrsro = 2000;
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

MQ7::~MQ7()
{
    //dtor
}

String MQ7::Label()
{
    return "CO"; 
}

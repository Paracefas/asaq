#include "MQ9.h"
#include "Math.h"
#include "Arduino.h"
#include <string>

MQ9::MQ9()
{
}

MQ9::MQ9(int _mqPin)
{ 
    double lista[]={    -10,      0,     10,     20,     30,     40,     50 };
    Ecuation _ecuation{ 24.399, -0.384 };
    double _defaultPPM = 2.0;
    unsigned long int_RL = 10000;
    double _maxrsro = 10000;
    double _minrsro = 0.01;
    double _Ratio33Hum[] = {1.7, 1.58, 1.45, 1.28, 1.15, 1.00, 0.88}; // MQ9
    double _Ratio85Hum[] = {1.28, 1.18, 1.7, 0.91, 0.87, 0.71, 0.66}; // MQ9
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

MQ9::~MQ9()
{
    //dtor
}

String MQ9::Label()
{
    return "CH4"; 
}

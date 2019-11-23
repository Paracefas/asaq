#include "MQ135.h"
#include "Math.h"
#include "Arduino.h"

#include <string>
MQ135::MQ135()
{
}

MQ135::MQ135(int _mqPin)
{
    double lista[]={    -10,      0,     10,     20,     30,     40,     50 };
    double _Ratio33Hum[] = {1.7, 1.38, 1.13, 1.0, 0.98, 0.94, 0.90}; // MQ135
    double _Ratio85Hum[] = {1.55, 1.24, 1.03, 0.90, 0.88, 0.84, 0.80}; // MQ135
    Ecuation _ecuation{ 110.374, -2.721 };
    double _defaultPPM = 535.0;
    unsigned long int_RL = 20000;
    double _maxrsro = 1300;
    double _minrsro = 1.0;
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

MQ135::~MQ135()
{
    //dtor
}

String MQ135::Label()
{
    return "CO2"; 
}

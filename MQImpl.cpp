#include "MQImpl.h"

long unsigned int MQImpl::getRo(double ppm) 
{
    long unsigned int aux = this->readMq()*pow((ecuationValues.Avalue/ppm), (1/ecuationValues.Bvalue));
    return aux;
}

long unsigned int MQImpl::getRoCorrected() 
{
    correctedRoFlag = true;
    long ret = 0;
    float m = rsRoTHdiff(actualTemp, actualHum);
    float n = rsRoTHdiff(senRefTemp, senRefHum);
    ret = (long)((n/m)*Ro);
    RoCorrected = ret;
    Serial.println(String("ret=") + ret);
    Serial.println(String("actualTemp=") + actualTemp);
    Serial.println(String("actualHum=") + actualHum);
    Serial.println(String("m=") + m);
    Serial.println(String("n=") + m);
    
    return ret;
}

double MQImpl::rsRoTHdiff(double Temperature, double Humidity) 
{
    double ret = -1;

    int i = 0;
    double rsroth1 = -1;
    double rsroth2 = -1;

    while((i < (TempPoints)) && (actualTemp > Temperatures[i])) {
        i++;
    }

    if(i == TempPoints)
    {
        if (MQ_RSROTEMPHUMDGAINPREVENTOUTOFLIMITS == 1) return -1;
        else
        {
            rsroth1 = Ratio33Hum[i-1];
            rsroth2 = Ratio85Hum[i-1];
        }
    }
    else if(i == 0)
    {
        if (MQ_RSROTEMPHUMDGAINPREVENTOUTOFLIMITS == 1)return -1;
        else
        {
            rsroth1 = Ratio33Hum[i];
            rsroth2 = Ratio85Hum[i];
        }
    }
    else 
    {
        rsroth1 = (Ratio33Hum[i] - Ratio33Hum[i-1]) / (Temperatures[i] - Temperatures[i-1]) * (actualTemp - Temperatures[i]) + Ratio33Hum[i];
        rsroth2 = (Ratio85Hum[i] - Ratio85Hum[i-1]) / (Temperatures[i] - Temperatures[i-1]) * (actualTemp - Temperatures[i]) + Ratio85Hum[i];
    }
    
    ret = rsroth1 + (actualHum - Hum1Value)*(rsroth2 - rsroth1)/(Hum2Value-Hum1Value);

    return ret;
}

MQImpl::~MQImpl() {}

void MQImpl::setTempYHumValues(double _actualTemp, double _actualHum)
{
    actualHum = _actualHum;
    actualTemp = _actualTemp;
}

void MQImpl::setRo(long value) { Ro = value; } 

double MQImpl::readMq() 
{
    double rs = 0;
    for (int i = 0;i<READ_SAMPLE_TIMES;i++) {
        rs += analogRead(mqPin);
        delay(READ_SAMPLE_INTERVAL);
    }    

    float rS = 0;
    rs = rs / READ_SAMPLE_TIMES;
    rS = (ANALOG_RESOLUTION / rs)*RL - RL;
    return rS;
}   

double MQImpl::getPPM() 
{
    double ret = 0; 
    double resvalue =this->readMq();
    ret = ecuationValues.Avalue * pow((resvalue/Ro), ecuationValues.Bvalue);
    if(ret > maxrsro) return maxrsro;
    else if(ret < minrsro) return minrsro;
    return ret;
}

double MQImpl::getPPMCorrected() 
{
    double ret = 0;
    if (correctedRoFlag == false)getRoCorrected();
    long resvalue = (long)this->readMq();
    double t = this->rsRoTHdiff(actualTemp, actualHum);
    double q = this->rsRoTHdiff(senRefTemp, senRefHum);
    long resvalueTempHum = (long)((q/t)*resvalue);
    countCorrected++;
    if (countCorrected > 5) 
    {
        getRoCorrected();
        countCorrected = 0;
    }
    ret = ecuationValues.Avalue * pow((resvalueTempHum/RoCorrected), ecuationValues.Bvalue);
    return ret;
}

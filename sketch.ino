#include "MQFactory.h"
#include "SEN0162.hpp"
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_BMP085.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#include "DSM501.h"
#define DSM501_PM10 3
#define DSM501_PM25 4
#define DHTPIN 4
#define DHTTYPE DHT22

/*
 * DSM501A IS NOT CONNECTED
 * DSM501 dsm501(DSM501_PM10, DSM501_PM25);
 */
String toSend;
String valor;

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        pCharacteristic->setValue(toSend.c_str());
        if (value.length() > 0) {
            Serial.println("*********");
            valor = "";
            for (int i = 0; i < value.length(); i++){
                valor = valor + value[i];
            }
        }
    }
};

Adafruit_BMP085 bmp;
DHT_Unified dht(DHTPIN, DHTTYPE);

double temp = 0;
double humd = 0;

IMQ* mqs[4];
const int MQpins[] = { 34, 39, 35, 36 };

SEN0162 uv_sensor{ 27 };

void setup()
{
    Serial.begin(9600);
    /*
     * DSM501A IS NOT CONNECTED
     * dsm501.begin(MIN_WIN_SPAN);
     */
    bmp.begin();
    dht.begin();
    MQFactory fact;
    for(int i = 0; i < 4; ++i)
        mqs[i] = fact.createMQ(i, MQpins[i]); 
    
    BLEDevice::init("ASAC Beacon");
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(SERVICE_UUID);
    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                           CHARACTERISTIC_UUID,
                                           BLECharacteristic::PROPERTY_READ |
                                           BLECharacteristic::PROPERTY_WRITE
                                         );
  
    pCharacteristic->setCallbacks(new MyCallbacks());
    pCharacteristic->setValue("Iniciado.");
    pService->start();
  
    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();
}

int count = 0;

void loop()
{
    double CO, CO2, CH4, O3, UV, Pressure, PM10, PM25;
    if(count > 5)
    {
        for(int i = 0; i < 4; ++i)
            mqs[i]->setTempYHumValues(temp, humd);    
        count = 0;
    }
    
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    temp = event.temperature;
    Serial.println(String("Temperature: ") + temp + " *C");
    
    dht.humidity().getEvent(&event);
    humd = event.relative_humidity;
    Serial.println(String("Humidity: ") + humd + " %");
    
    Serial.print("Pressure at sealevel (calculated) = ");
    Serial.print(bmp.readSealevelPressure());
    Serial.println(" Pa");
    Pressure = bmp.readSealevelPressure();

    CO  = mqs[0]->getPPMCorrected();
    CO2 = mqs[1]->getPPMCorrected();
    CH4 = mqs[2]->getPPMCorrected();
    O3  = mqs[3]->getPPMCorrected();
    UV  = uv_sensor.GetUVIndex();

    Serial.println(String("CO  = ") + CO  + " ppm - GOOD = [0.00 ; 2.0], NORMAL = [2.1 ; 10.0], DANGEROUS = [ 10.1 ; +34 ]");
    Serial.println(String("CO2 = ") + CO2 + " ppm - GOOD = [0.00 ; 2.0], NORMAL = [2.1 ; 10.0], DANGEROUS = [ 10.1 ; +34 ]");
    Serial.println(String("CH4 = ") + CH4 + " ppm - GOOD = [0.00 ; 2.0], NORMAL = [2.1 ; 10.0], DANGEROUS = [ 10.1 ; +34 ]");
    Serial.println(String("O3  = ") + O3  + " ppm - GOOD = [0.00 ; 100], NORMAL = [101 ; 168 ], DANGEROUS = [ 169  ; +400]");

    /* 
     * DSM501A IS NOT CONNECTED
     * 
    dsm501.update();

    PM10 = dsm501.getParticleWeight(0);
    PM25 = dsm501.getParticleWeight(1);
    
    Serial.print(String("PM10: ") + PM10 + " ug/m3 - GOOD = [0.00 ; 100], NORMAL = [101 ; 250], DANGEROUS = [ 251 ; +430 ]");    
    Serial.print(String("PM25: ") + PM25 + " ug/m3 - GOOD = [0.00 ; 60.0], NORMAL = [61.0 ; 90.0], DANGEROUS = [ 91.0 ; +250 ]");
    */

    Serial.print("PM10: DSM501A IS NOT CONNECTED");
    Serial.print("PM25: DSM501A IS NOT CONNECTED");
    
    Serial.println("*********************************");
    Serial.println("Preparing to send data throw BLE");
    toSend =  (String) "&CO=" + CO + "&CO2="+ CO2 + "&CH4="+ CH4 + "&O3=" + O3 + "&UV=" + UV + "&PM10=null" + "&PM25=null" + "&TEMP="+ temp + "&HUM=" + humd + "PRESS=" + Pressure; // cambiar el nombre de la variable por algo significativo 
    Serial.println(toSend);
  
    ++count;
}

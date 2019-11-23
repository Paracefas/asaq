#include "SEN0162.hpp"
#include <Arduino.h>

SEN0162::SEN0162(int pin)
    : m_pin { pin } {}

int SEN0162::GetUVIndex()
{
    analogReadResolution(10);
    double analogValue = analogRead(m_pin);
    return analogValue < 18.6 ? 0 : 0.05 * analogValue -1;
}

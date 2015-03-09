#ifndef DS18B20_h
#define DS18B20_h

#include "Arduino.h"
#include <OneWire.h>

void initSensor(OneWire sensor, byte address[8]);
float getTemp(OneWire sensor, byte addr[8]);

#endif
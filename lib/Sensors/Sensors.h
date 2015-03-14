#ifndef Sensors
#define Sensors

#include "Arduino.h"
#include <OneWire.h>

class Sensor {
private:
	int _pin;
};

class DS18B20 : public Sensor
{
public:
	DS18B20(int pin, byte address[8]);
	float getTemp();
private:
	OneWire* _sensor;
	byte* _address;
};

#endif
#include <OneWire.h>
#include <DS18B20.h>

// DS18S20 Temperature chip i/o
OneWire g_sensor(10);  // on pin 10
byte g_address[8];

int g_pin = 10;
DS18B20* g_dsTempSensor;

void setup(void) {
  // initialize inputs/outputs
  // start serial port
  Serial.begin(9600);
  g_dsTempSensor = new DS18B20(g_pin, g_address);
  // initSensor( g_sensor, g_address );
}

void loop(void) {
  float temp;
  
  if ( true ) {
    temp = g_dsTempSensor->getTemp();
    Serial.println(temp,1);
  }
  
  delay(3000);

}
#include "Arduino.h"
#include <OneWire.h>
#include "DS18B20.h"

void initSensor( OneWire sensor, byte address[8] ) {
  
    if ( !sensor.search(address)) {
//      Serial.print("No more addresses.\n");
      sensor.reset_search();
      return;
  }


  if ( OneWire::crc8( address, 7) != address[7]) {
      Serial.print("CRC is not valid!\n");
      return;
  }

  if ( address[0] == 0x10) {
      Serial.print("Device is a DS18S20 family device.\n");
  }
  else if ( address[0] == 0x28) {
      //Serial.print("Device is a DS18B20 family device.\n");
  }
  else {
      Serial.print("Device family is not recognized: 0x");
      Serial.println(address[0],HEX);
      return;
  }

//  sensor.reset();
//  sensor.select(address);
//  sensor.write(0x44,1);         // start conversion, with parasite power on at the end

  
  // we might do a ds.depower() here, but the reset will take care of it.
}


float getTemp(OneWire sensor, byte addr[8]) {
  int i, hByte, lByte, tReading, signBit, iTemp;
  float temp;
  byte data[12];
  
  sensor.reset();
  sensor.select(addr);
  sensor.write(0x44,1);
  delay(1000);
  sensor.reset();
  sensor.select(addr);
  sensor.write(0xBE);  // Read Scratchpad
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = sensor.read();
  }
  lByte = data[0];
  hByte = data[1];
  tReading = (hByte << 8) + lByte;
  signBit = tReading & 0x8000;  // test most sig bit
  if (signBit) // negative
  {
    tReading = (tReading ^ 0xffff) + 1; // 2's comp
  }
  iTemp = (6 * tReading) + tReading / 4;    // multiply by (100 * 0.0625) or 6.25
  temp = iTemp/100.0;
  if(!signBit) {
      return temp;
  }
  else {
    return -temp;
  }
}

DS18B20::DS18B20(int pin, byte address[8]) {
  _sensor = new OneWire(pin);
  _address = address;

  if ( !_sensor->search(address)) {
//      Serial.print("No more addresses.\n");
      _sensor->reset_search();
      return;
  }


  if ( OneWire::crc8( address, 7) != address[7]) {
      Serial.print("CRC is not valid!\n");
      return;
  }

  if ( address[0] == 0x10) {
      Serial.print("Device is a DS18S20 family device.\n");
  }
  else if ( address[0] == 0x28) {
      //Serial.print("Device is a DS18B20 family device.\n");
  }
  else {
      Serial.print("Device family is not recognized: 0x");
      Serial.println(address[0],HEX);
      return;
  }
};

float DS18B20::getTemp() {
  //  Получаем температуру с датчика
  int i, hByte, lByte, tReading, signBit, iTemp;
  float temp;
  byte data[12];
  
  _sensor->reset();
  _sensor->select(_address);
  _sensor->write(0x44,1);
  delay(1000);
  _sensor->reset();
  _sensor->select(_address);
  _sensor->write(0xBE);  // Read Scratchpad
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = _sensor->read();
  }
  lByte = data[0];
  hByte = data[1];
  tReading = (hByte << 8) + lByte;
  signBit = tReading & 0x8000;  // test most sig bit
  if (signBit) // negative
  {
    tReading = (tReading ^ 0xffff) + 1; // 2's comp
  }
  iTemp = (6 * tReading) + tReading / 4;    // multiply by (100 * 0.0625) or 6.25
  temp = iTemp/100.0;
  if(!signBit) {
      return temp;
  }
  else {
    return -temp;
  }
}
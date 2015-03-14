#include <OneWire.h>
#include <Sensors.h>

const int N_SENSORS = 1;                   //  Количество датчиков
const int SENSOR_DESC_LEN = 20;
char* g_sensorsDesc[N_SENSORS];       //  Описание (тип) датчиков
int g_pins[N_SENSORS];           //  На каких они пинах

Sensor* g_sensors[N_SENSORS];                    //  Сами датчики
float g_measures[N_SENSORS];          //  Результаты измерений датчиков

DS18B20* g_dsTempSensor;

byte g_address[8];

void setup(void) {
  // initialize inputs/outputs
  // start serial port
  Serial.begin(9600);
  settings();
  initSensors();
  // g_dsTempSensor = new DS18B20(g_pin, g_address);
  // initSensor( g_sensor, g_address );
}

void loop(void) {
  measure();
  sendMeasuresToSerial();
  
  delay(3000);

}

void settings(void) {
  //  Задаем настройки. Описываем датчики.
  g_sensorsDesc[0] = "DS18B20";
  g_pins[0] = 10;
}

void initSensors(void) {
  //  Инициализируем датчики на основе настроек
  for(int icSensor = 0; icSensor < N_SENSORS; icSensor++){
    char* descSensor = g_sensorsDesc[icSensor];
    int pin = g_pins[icSensor];

    if(descSensor == "DS18B20") {
      g_sensors[icSensor] = new DS18B20(pin, g_address);
    }
  } 
}

void measure(void) {
  //  Проводим измерения
  for(int icSensor = 0; icSensor < N_SENSORS; icSensor++) {
    char* descSensor = g_sensorsDesc[icSensor];
    float measureVal;

    if(descSensor == "DS18B20") {
      DS18B20 *dsSensor = (DS18B20 *) &g_sensors[icSensor];
      measureVal = dsSensor->getTemp();
    }

    g_measures[icSensor] = measureVal;

  }
}

void sendMeasuresToSerial() {
  //  Отправляем результаты измерений в ком-порт
  for(int icSensor = 0; icSensor < N_SENSORS; icSensor++) {
    float measureVal = g_measures[icSensor];
    Serial.println(measureVal, 1);
  }
}
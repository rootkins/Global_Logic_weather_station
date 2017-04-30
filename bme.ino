

#include <stdint.h>
#include "SparkFunBME280.h"

#include "Wire.h"

#include "uno_pinout.h"

BME280 g_BME280;
int timestamp = 2000; //2000 ms 
String sTimestamp = "";
bool isNewTimestamp = false;
bool isPortReady = false;

void setup() {
  
  g_BME280.settings.commInterface = I2C_MODE;
  g_BME280.settings.I2CAddress = 0x76;
  g_BME280.settings.runMode = 3; 
  g_BME280.settings.tStandby = 0.5;

  g_BME280.settings.filter = 0;
  g_BME280.settings.tempOverSample = 1;
  g_BME280.settings.pressOverSample = 1;
  g_BME280.settings.humidOverSample = 1;

  Serial.begin(9600);
  delay(10);  
  g_BME280.begin();
}

void loop() {

  if (Serial.available() > 0) 
  {
    char cTimestamp = Serial.read();
    sTimestamp += (char)cTimestamp;  
    isNewTimestamp = true;
  }
  else
  {
    if(isNewTimestamp == true)
    {
      timestamp = sTimestamp.toInt() * 1000; //zamienia sekundy na milisekundy
      isNewTimestamp = false;
      isPortReady = true;
      sTimestamp = "";    
    }

    if(isPortReady == true)
    {
      Serial.print(g_BME280.readTempC(), 2);
      Serial.print("; ");
    
      Serial.print(g_BME280.readFloatPressure(), 2);
      Serial.print("; ");
    
      Serial.print(g_BME280.readFloatAltitudeMeters(), 2);
      Serial.print("; ");
    
      Serial.print(g_BME280.readFloatHumidity(), 2);
      Serial.print(";\n");
    }
    delay(timestamp);
  }



}

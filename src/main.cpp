/*
 * Statement of Authorship:
 * I, Joshi Prachi , student number 0316555, certify that this
 * material is my original work. No other person's work has been
 * used without due acknowledgement
 */

// Extending the temperature measurement: the variable resistor from the
// Analog Signals lab is replaced by a real DS18B20 temperature sensor.

#include <Arduino.h>
// 1-Wire sensor communication libary
#include <OneWire.h>
// DS18B20 sensor library
#include <DallasTemperature.h>

// Pin that the DS18B20 is connected to
const int oneWireBus = D3;
OneWire oneWire(oneWireBus);
DallasTemperature DS18B20(&oneWire);

// unique 8-byte address of our sensor
DeviceAddress sensorAddress;
bool bSensorFound = false;

void setup() {
  Serial.begin(115200);
  delay(500);

  DS18B20.begin();

  Serial.println("\n\nTemperature Application");

  if (DS18B20.getAddress(sensorAddress, 0)) {
    bSensorFound = true;

    String sAddress = "";
    for (int i = 0; i < 8; i++) {
      if (sensorAddress[i] < 0x10) sAddress += "0";
      sAddress += String(sensorAddress[i], HEX);
    }
    Serial.println("Found DS18B20 sensor with address: " + sAddress);
  } else {
    Serial.println("No DS18B20 temperature sensors are installed!");
  }
}

void loop() {
  float fTemp;
  String sJudgement;

  if (!bSensorFound) return;

  DS18B20.requestTemperatures();

  fTemp = DS18B20.getTempC(sensorAddress);

  if (fTemp == DEVICE_DISCONNECTED_C) {
    Serial.println("DS18B20 sensor is not responding!");
    delay(5000);
    return;
  }

  if (fTemp < 10)       sJudgement = "Cold!";
  else if (fTemp < 15)  sJudgement = "Cool";
  else if (fTemp < 25)  sJudgement = "Perfect";
  else if (fTemp < 30)  sJudgement = "Warm";
  else if (fTemp < 35)  sJudgement = "Hot";
  else                  sJudgement = "Too Hot!";

  Serial.println("Current temperature is: " + String(fTemp, 2) +
                 " deg. Celsius or " + sJudgement);

  delay(5000);
}

#include <ArduinoJson.h>
#include <OneWire.h>
#include <DallasTemperature.h>
 
#define ONE_WIRE_BUS 12
#define VOLT_1 10

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

unsigned long previousMillis = 0;
unsigned long voltPreviousMillis = 0;
const long interval = 15000;
const long voltMeasureInterval = 5000;


//VOLTMETETER things
float vPow = 3.3;
float r1 = 87500; //100000;
float r2 = 9600; //10000;

void setup()  {
  Serial.begin(115200);  // Datorn
  Serial1.begin(57600);  // Till MT7688
  sensors.begin();
}

boolean shouldSendData(long inputInterval) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= inputInterval) {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}
boolean shouldMeasureVolt(long inputInterval) {
  unsigned long currentMillis = millis();
  if (currentMillis - voltPreviousMillis >= inputInterval) {
    voltPreviousMillis = currentMillis;
    return true;
  }
  return false;
}

double measureTemp() {
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

double measureVolt() {
  return ((analogRead(VOLT_1) * vPow) / 1024.0) * 11.0434;
}

void loop() {
  char c;
  if(shouldSendData(interval)) {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& data = jsonBuffer.createObject();
    data["temp"] = measureTemp();
    data["volt1"] = measureVolt();
    data.printTo(Serial);
    data.printTo(Serial1);
    Serial.println("");
    Serial1.println("");
  }
  if (Serial.available()) {
    c = Serial.read();
    Serial.print(c);
  }
//  if (Serial1.available()) {
//    c = Serial1.read();
//    Serial.print(c);
//  }
}

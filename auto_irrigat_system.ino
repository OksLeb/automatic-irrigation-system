#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS A0

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const int soilMoistureSensor = A1;
const int soilMoisturePower = 13;
const int waterLevelSensor = A2;
const int waterLevelPower = 12;
const int motorPin = 11;
int upLevelMoisture = 500;
int downLevelMoisture = 250;
int downLevelWater = 360;

void setup() {
  pinMode(soilMoisturePower, OUTPUT);
  digitalWrite(soilMoisturePower, LOW);
  pinMode(waterLevelPower, OUTPUT);
  digitalWrite(waterLevelPower, LOW);
  pinMode(motorPin, OUTPUT);
  sensors.begin();
  Serial.begin(9600);
}

void loop() {
  sensors.requestTemperatures();
  float temperatureCelsius = sensors.getTempCByIndex(0);
  delay(50);
  int moistureValue = readMoistureSensor();
  delay(50);
  int waterValue = readWaterSensor();
  if (moistureValue > upLevelMoisture && temperatureCelsius < 28.0 && waterValue >= downLevelWater) {
    analogWrite(motorPin, LOW);
    Serial.println("The Soil Is Dry!");
  } else if (moistureValue < downLevelMoisture) {
    analogWrite(motorPin, HIGH);
    Serial.println("The Soil Is Wet!");
  } else {
    Serial.println("Moisture Level Is Just Fine!");
  }
  delay(50);
  if (waterValue < downLevelWater) {
    Serial.println("Here\'s Not Enough Water!");
  } else {
    Serial.println("Still Here\'s Enough Water!");
  }
  delay(1000);
}

int readMoistureSensor() {
  digitalWrite(soilMoisturePower, HIGH);
  delay(10);
  int val = analogRead(soilMoistureSensor);
  digitalWrite(soilMoisturePower, LOW);
  return val;
}

int readWaterSensor() {
  digitalWrite(waterLevelPower, HIGH);
  delay(10);
  int val = analogRead(waterLevelSensor);
  digitalWrite(waterLevelPower, LOW);
  return val;
}


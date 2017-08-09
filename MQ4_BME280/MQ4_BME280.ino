#include "Sensors.h"

int methanePin=0;
int sdaPin=4;
int sclPin=5;

BME280 atmosphericSensor(sdaPin, sclPin, "i2c");
MQ4 methaneSensor(methanePin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  atmosphericSensor.start();
  methaneSensor.calibrate();
}

void loop() {
  // put your main code here, to run repeatedly:
  float humidity=(atmosphericSensor.readHumidity("%"))/100.0;
  float temp=atmosphericSensor.readTemp("C");
  Serial.print("H: ");
  Serial.println(humidity);
  methaneSensor.setHumidity(humidity);
  methaneSensor.setTemperature(temp);
  
  Serial.print("T: ");
  Serial.println(temp);

  float methane=methaneSensor.readValue("ppm");
  Serial.print("CH4: ");
  Serial.println(methane);
  delay(1000);
}

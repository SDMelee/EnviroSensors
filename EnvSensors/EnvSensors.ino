#include "Sensors.h"

int methanePin=1;
int COPWMPin=5;
int COLEDPin=4;
int COReadPin=0;
int photoRPin=2;
int sdaPin=4;
int sclPin=5;

MQ4 MethaneSensor(methanePin);
MQ7 COSensor(COPWMPin, COLEDPin, COReadPin);
PhotoR LightSensor(photoRPin);
BME280 AtmosphericSensor(sdaPin, sclPin, "i2c");


void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  // Start communication on BME280
  AtmosphericSensor.start();
}

void loop() {
  COSensor.CoPwrCycler();
  // put your main code here, to run repeatedly:
  float methane=MethaneSensor.readValue("ppm");
  Serial.print("CH4: ");
  Serial.print(methane);
  Serial.println(" ppm");
  float light=LightSensor.readValue("lux");
  Serial.print("Light: ");
  Serial.print(light);
  Serial.println(" lux");
  float temp=AtmosphericSensor.readTemp("F");
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.println("F");
  float co=COSensor.readValue("ppm");
  Serial.print("CO: ");
  Serial.print(co);
  Serial.println(" ppm");
 
  Serial.println("");
  delay(1000);
}

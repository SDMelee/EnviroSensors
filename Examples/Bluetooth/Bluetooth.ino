#include "Sensors.h"

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3

BlueSMiRF bluetooth(bluetoothTx, bluetoothRx);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bluetooth.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  bluetooth.sendData("1, 2, 3, 4");
  delay(1000);
  bluetooth.sendData("5, 6, 7, 8");
  bluetooth.end();
  while(Serial.available()==0){}
}

/****************************************************************************************************
BlueSMiRF.cpp
Bluetooth Module Arduino Library
Amelia Peterson w/ CSDT @ RPI
Contact: petera7@rpi.edu
Last Updated: 08/17/2017

Visit our site at: www.csdt.rpi.edu

Description:
  This class implements an interface for the BlueSMiRF Silver Mate Bluetooth module. It treats it
like any of the other Serial sensors. The code initializes the sensor to 9600bps and waits for the
powershell script (bluetooth.ps1) to connect to the module from a computer and send its first message.
The bluetooth module sends data to the computer through a series of handshakes. First, the bluetooth
module will send 's' to tell the computer it wants to start sending data. The bluetooth module will
then wait for the computer to send "OK" to confirm the start signal was received. If "OK" isn't
received within 5s, the start signal will be sent again. Once the first "OK" is received, the bluetooth
will send the data, and again wait for confirmation. If no confirmation is received, the data will
be sent again after 5 seconds. If the communication is not completed within _timeout, the data will
fail to send.

https://www.sparkfun.com/products/12577

To do:
  -  Implement the code...
****************************************************************************************************/

#include "BlueSMiRF.h"

BlueSMiRF::BlueSMiRF(int rxPin, int txPin){
  _rxPin=rxPin;
  _txPin=txPin;
  _wait=false;
  _send=false;
  _timeout=60000; // Timeout is 1min
  _portPtr= new SoftwareSerial(_rxPin, _txPin);
}

void BlueSMiRF::begin(){
  // Change bluetooth's baudrate to 9600bps
  _portPtr->begin(115200); // The bluetooth mate defaults to 115200bps
  _cmdMode();
  _portPtr->println("U,9600,N"); // 9600bps, no parity
  _portPtr->begin(9600); // Start communication at 9600bps, this will take us out of command mode
  if(!_waitForLink())
    Serial.println("Error: timeout while waiting for connection.");
}

void BlueSMiRF::sendData(String data){
  unsigned long __startTime=millis();
  unsigned long __waitTime=millis();
  while((millis()-__startTime)<_timeout){
    // Receive handshake
    if(_portPtr->available())  // If the bluetooth sent any characters
    {
      String msg=_getMsg();
      Serial.print(msg);
      if(msg == "OK\n" && !_send && _wait){
        _send=true;
        _wait=false;
      }
      else if(msg == "OK\n" && _wait && _send){
        _wait=false;
        _send=false;
        return;
      }
    }
    else if(!_send && _wait && (millis()-__waitTime)>5000){ // If we've been waiting for 5s w/out any response...
      _wait=false;                                          // Stop waiting and send handshake again
    }
    else if(_send && _wait && (millis()-__waitTime)>5000){
      _send=false;
    }
    // Send data or handshake
    if(_send && !_wait){
      Serial.println("Sending Data");
      _portPtr->println(data);
      __waitTime=millis();
      _wait=true;
    }
    else if(!_wait && !_send){
      _portPtr->print((char)115);
      _portPtr->print((char)10);
      __waitTime=millis();
      _wait=true;
    }
  }
  Serial.println("Error: data not sent");
}

String BlueSMiRF::_getMsg(){
  String __msg="";
  while(_portPtr->available()){
      __msg+=(char)_portPtr->read();
      delay(10);
  }
  return __msg;
}

void BlueSMiRF::_cmdMode(){
  // Print '$$$' to enter command mode
  _portPtr->print("$");
  _portPtr->print("$");
  _portPtr->print("$");
  // Short delay to wait for module to enter command mode
  delay(100);
}

void BlueSMiRF::_commMode(){
  // Print '---\n' to enter communication mode
  _portPtr->println("---");
  delay(100);
}

bool BlueSMiRF::_waitForLink(){
  // Wait for computer to connect and send message
  // i.e., bluetooth.ps1 powershell script to send:
  // "Port is opened, listening for data..."
  unsigned long __startTime=millis();
  while((millis()-__startTime)<_timeout){
    if(_portPtr->available()){
      String __msg=_getMsg();
      Serial.println(__msg);
      return true;
    }
  }
  return false;
}

void BlueSMiRF::end(){
  _portPtr->print((char)101);
  _portPtr->print((char)10);
}
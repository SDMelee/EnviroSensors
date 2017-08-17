/****************************************************************************************************
BlueSMiRF.h
Bluetooth Module Arduino Library
Amelia Peterson w/ CSDT @ RPI
Contact: petera7@rpi.edu
Last Updated: 08/15/2017

Visit our site at: www.csdt.rpi.edu

Description:
	This class implements an interface for the BlueSMiRF Silver Mate Bluetooth module. It treats it
like any of the other Serial communication sensors. The class communicates with a powershell script
(bluetooth.ps1) on the computer to which it is linked. The powershell script will take any data written
to it through sendData(String) and write it to a file data.txt. 
 To start the the data transfer, start the bluetooth module first then open bluetooth.bat. The batch file
will call the bluetooth.ps1 file which will send a message to the bluetooth module to confirm the link.
If the message is not sent within _timmeout ms, then the program will exit.
****************************************************************************************************/

#ifndef BlueSMiRF_h
#define BlueSMiRF_h

#include "Arduino.h"
#include <SoftwareSerial.h>

class BlueSMiRF{
public:
  BlueSMiRF(int rxPin, int txPin);
  ~BlueSMiRF(){
    end();
    if(_portPtr!=NULL){
      delete _portPtr;
    }
  }
  void begin();
  void sendData(String data);
  void end();

private:
  int _rxPin, _txPin;
  bool _send, _wait;
  unsigned long _timeout;
  SoftwareSerial* _portPtr;

  void _cmdMode();
  void _commMode();
  bool _waitForLink();
  String _getMsg();
};

#endif

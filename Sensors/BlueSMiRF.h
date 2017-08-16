/****************************************************************************************************
BlueSMiRF.h
Bluetooth Module Arduino Library
Amelia Peterson w/ CSDT @ RPI
Contact: petera7@rpi.edu
Last Updated: 08/15/2017

Visit our site at: www.csdt.rpi.edu

Description:
	This class implements an interface for the BlueSMiRF Silver Mate Bluetooth module. It treats it
like any of the other Serial sensors.

https://www.sparkfun.com/products/12577

To do:
  -  Implement the code...
****************************************************************************************************/

#ifndef BlueSMiRF_h
#define BlueSMiRF_h

#include <SoftwareSerial.h>

class BlueSMiRF{
public:
	BlueSMiRF(int rxPin, int txPin){
		_rxPin=rxPin;
		_txPin=txPin;
		_portPtr= new SoftwareSerial(_rxPin, _txPin);
	}
	~BlueSMiRF(){
		if(_portPtr!=NULL){
			delete _portPtr;
		}
	}
	void begin();
	bool sendData(String data);
	String receiveData();

private:
	int _rxPin, _txPin;
	SoftwareSerial* _portPtr;
};

#endif
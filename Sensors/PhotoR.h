/****************************************************************************************************
PhotoR.h
Photoresistor Arduino library
Amelia Peterson w/ CSDT @ RPI
Contact: petera7@rpi.edu
Last Updated: 08/15/2017

Visit our site at: www.csdt.rpi.edu

Description:
  This class measures the resistance of an SEN-09088 photoresistor and converts that value to
illuminance (lux).
****************************************************************************************************/

#ifndef PhotoR_h
#define PhotoR_h

#include "Arduino.h"

class PhotoR{
public:
	PhotoR(int analogPin){
		_analogPin=analogPin;
	}
	float readValue(String units){
		float analogValue= float(analogRead(_analogPin));
		float convertedValue=0;
		if(units=="lux"){
			convertedValue=0.6*analogValue;
		}
		else{
			Serial.println("PhotoR: units not recognized. Use PhotoR.help() for available units.");
		}
		return convertedValue;
	}
	void help(){
		Serial.println("The Photoresistor detects light intensity.");
		Serial.println("Available units are:");
		Serial.println("  lux");
	}
private:
	int _analogPin;
};

#endif

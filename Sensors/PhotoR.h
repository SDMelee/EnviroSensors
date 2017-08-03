#ifndef PhotoR_h
#define PhotoR_h

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
 #include "stdlib.h"
 #include "wiring.h"
#endif

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
		return convertedValue; // return convertedValue when that code is implemented
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
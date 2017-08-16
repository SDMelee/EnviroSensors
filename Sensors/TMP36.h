#ifndef TPM36_h
#define TMP36_h

#include "Arduino.h"

class TMP36{
public:
	TMP36(int analogPin){
		_analogPin=analogPin;
	}
	float readValue(String units){
		int analogValue=analogRead(_analogPin);
		float convertedValue=0;
		if(units=="F" || units=="Farenheit"){
			convertedValue=(((5/1023)*analogValue-0.5)*100)*(9.0/5.0)+32.0;
		}
		else if(units=="C" || units=="Celsius"){
			convertedValue=((5/1023)*analogValue-0.5)*100;
		}
		else{
			Serial.println("TMP36: units not recognized. Use MQ4.help for available units.");
		}
		return convertedValue;
	}
	void help(){
		Serial.println("The TMP36 sensor is a temperature sensor.");
		Serial.println("Available units are:");
		Serial.println("  Farenheit (F)");
		Serial.println("  Celsius (C)");
	}
private:
	int _analogPin;
};

#endif
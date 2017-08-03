#ifndef MQ4_h
#define MQ4_h

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
 #include "stdlib.h"
 #include "wiring.h"
#endif

class MQ4{
public:
	MQ4(int analogPin){
		_analogPin=analogPin;
	}
	float readValue(String units){
		float analogValue=float(analogRead(_analogPin));
		float convertedValue=0;
		if(units=="ppb"){
			convertedValue=((10000-300)/1023)*analogValue+300;
		}
		else if(units=="ppm"){
			convertedValue=(((10000-300)/1023)*analogValue+300)/(1000);
		}
		else{
			Serial.println("MQ4: units not recognized. Use MQ4.help for available units.");
		}
		return convertedValue;
	}
	void setHumidity(float humidity);
	void setTemperature(float temp);
	void calibrate(float methaneConcentration);
	void help(){
		Serial.println("The MQ4 sensor detects Methane (CH4) concentrations in the air.");
		Serial.println("Available units are:");
		Serial.println("  ppm");
		Serial.println("  ppb");
	}
private:
	int _analogPin;
	float _temp;
	float _humidity;

	void _adjustForAtmosphere();	// Adjusts calibration constants based on humidity and temp
};

#endif
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
		_Rl=4.7;				// Load Resistor 4.7k
		_humidity=0.55;			// Assume humidity is 55%...
		_temp=20;				// ... and assume temp is 20C (from Winsen data sheet)
		_calculateR0();			// Calculate _R0

	}
	MQ4(int analogPin, float Rl){
		_analogPin=analogPin;
		_Rl=Rl;
		_humidity=0.55;			// Assume humidity is 55%
		_temp=20;				// Assume temp is 20C... from Winsen data sheet
		_calculateR0();
	}
	float readValue(String units);		
	void setHumidity(float humidity){
		_humidity=humidity;
	}
	void setTemperature(float temp){
		_temp=temp;
	}
	void calibrate();
	void changeRl(float Rl);
	void help(){
		Serial.println("The MQ4 sensor detects Methane (CH4) concentrations in the air.");
		Serial.println("Available units are:");
		Serial.println("  ppm");
		Serial.println("  ppb");
	}
private:
	int _analogPin;		// analog read pin for methane
	float _Rl;			// load resistor value
	float _R0;			// sensor resistance in clean air 
	float _temp;		// temperature for adjusting sensor resistance
	float _humidity;    // humidity for adjusting sensor resistance

	void _calculateR0();
	float _calculateRs();
	float _adjustForAtmosphere(float Rs);	// Adjusts measured methane based on humidity and temp
};

#endif

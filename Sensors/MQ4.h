/****************************************************************************************************
MQ4.h
MQ4 Methane and Natural Gas Sensor Arduino library
Amelia Peterson w/ CSDT @ RPI
Contact: petera7@rpi.edu
Last Updated: 08/15/2017

Visit our site at: www.csdt.rpi.edu

Description:
	This class provides the functionality for interpreting measurements from the MQ4 gas sensor.
The class allows for calibration of the sensor and adjusts the measured gas concentrations for
temperature and humidity as defined by the datasheet:

https://cdn.sparkfun.com/datasheets/Sensors/Biometric/MQ-4%20Ver1.3%20-%20Manual.pdf

The temperature and humidity values must be provided by the user. It is reccomended that you use
some sort of ambient temperature and humidity sensor such as the BME280 in conjunction with the MQ4
sensor for accurate measurements.
  If no humidity or temperature data is available, assume 20C and 55% humidity. Similarly, unless
otherwise specified, we assume the load resistor is 4.7k-ohm. These are the 'standard' test conditions
provided by the Winsen data sheet.

!!PLEASE READ THE DATASHEET BEFORE USE!!

Some important notes:
	- Do not expose the sensor to significant moisture
	- Do not connect the heater to the Arduino directly - it must be connected to an external
	  power source to provide enough current.
	- Do NOT apply voltage over 5V to the heater.
	- Check that your load resistor matches the _Rl member variable.
	- If soldering, check data sheet for proper heat settings.
	- Calibrate in clean air with no methane or natural gases.
	- MQ4 sensor needs 48 HOURS of preheat time to operate correctly

To do:
	- Add ability to use analog or digital potentiometer (AD5171) to change sensitivity
	- Check accuracy of equations against known concentrations of methane and natural gas
****************************************************************************************************/

#ifndef MQ4_h
#define MQ4_h

#include "Arduino.h"

class MQ4{
public:
	MQ4(int analogPin){
		_analogPin=analogPin;
		_Rl=4.7;					// Load Resistor 4.7k
		_humidity=0.55;				// Assume humidity is 55%...
		_temp=20;					// ... and assume temp is 20C (from Winsen data sheet)
		_calculateR0();				// Calculate sensor resistance in clean air, R0
	}
	MQ4(int analogPin, float Rl){
		_analogPin=analogPin;
		_Rl=Rl;
		_humidity=0.55;
		_temp=20;
		_calculateR0();
	}
	float readValue(String units);
	void setHumidity(float humidity){
		_humidity=humidity;
	}
	void setTemperature(float temp){
		_temp=temp;
	}
	void calibrate();				// recalculates R0
	void changeRl(float Rl);
	void help(){
		Serial.println("The MQ4 sensor detects Methane (CH4) concentrations in the air.");
		Serial.println("Available units are:");
		Serial.println("  Parts per million:  ppm");
		Serial.println("  Parts per billion:  ppb");
		//Serial.println("  For additional help, visit the CSDT site: <csdt page>");	add link to CSDT environmental sensors page when available
	}
private:
	int _analogPin;				// analog read pin for methane
	float _Rl;					// load resistor value
	float _R0;					// sensor resistance in clean air
	float _temp;				// temperature for adjusting sensor resistance
	float _humidity;    		// humidity for adjusting sensor resistance

	void _calculateR0();
	float _calculateRs();
	float _adjustForAtmosphere(float Rs);	// Adjusts measured methane based on humidity and temp
};

#endif

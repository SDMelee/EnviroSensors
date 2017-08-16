/****************************************************************************************************
MQ4.cpp
MQ4 Methane and Natural Gas Sensor Arduino library
Amelia Peterson w/ CSDT @ RPI
Contact: petera7@rpi.edu
Last Updated: 08/15/2017

Visit our site at: www.csdt.rpi.edu

Description:
_calculateRs() calculates the sensor resistance from the voltage divider equation:

       Rs          Rl
VCC----/\/\/\/\----/\/\/\/\---GND
                ^
                |____Vrl

						Vrl=Vcc*(Rl/(Rs+Rl))
						Rs=5*(Rl/Vrl)-Rl

  The gas concentration equation used in readValue(String) was determined from a best fit to the
Rs/R0 plot in the datasheet. The temperature and humidity adjustments were calculated similarly.

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
	- Determine Rs/Rs0=f(T, %RH) under varying gas conditions (100ppm, 500ppm, 1000ppm, 10000ppm)
****************************************************************************************************/

#include "MQ4.h"

float MQ4::_calculateRs(){
	float analogValue=float(analogRead(_analogPin));
	float V_Rl = analogValue*(5.0/1023);						// Convert to Voltage
	return (((5.0*_Rl)/V_Rl)-_Rl)/1000;							// Use voltage divider equation and convert to kOhm
}

float MQ4::readValue(String units){
	float analogValue=float(analogRead(_analogPin));
	float Rs_R0=_calculateRs()/_R0;
	float convertedValue=0;
	if(units=="ppb"){
		convertedValue=float(_adjustForAtmosphere(25.1047/pow(Rs_R0,1.656)));
		convertedValue /= 1000;
	}
	else if(units=="ppm"){
		convertedValue=float(_adjustForAtmosphere(25.1047/pow(Rs_R0,1.656)));
	}
	else{
		Serial.println("MQ4: units not recognized. Use MQ4.help for available units.");
	}
	return convertedValue;
}


void MQ4::_calculateR0(){
	Serial.println("Calibrating sensor for R0, make sure sensor is in clean air.");
	_R0=_calculateRs();
}

void MQ4::calibrate(){
	_calculateR0();
}

// Resistance will decrease with increasing temperature humidity. This function
// uses the Winsen datasheet's plots to claculate what the sensor resistance
// would be under 'normal' conditions of 55% humidity and 20C temp.
float MQ4::_adjustForAtmosphere(float Rs){
	float Rs_Rs0 = (0.006*_humidity-0.0156)*_temp-0.7834*_humidity+1.7842;
	return Rs/Rs_Rs0;
}

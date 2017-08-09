#include "MQ4.h"

float MQ4::_calculateRs(){
	float analogValue=float(analogRead(_analogPin));
	float V_Rl = analogValue*(5.0/1023);	// Convert to Voltage
	return (((5.0*_Rl)/V_Rl)-_Rl)/1000;
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
	//Serial.println("Calibrating sensor for R0, make sure sensor is in clean air.");
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

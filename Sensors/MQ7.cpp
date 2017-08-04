
/*  
	CS_MQ7_02.h - Library for reading the MQ-7 Carbon Monoxide Sensor
	Breakout, as part of the Citizen Sensor project.	
	http://citizensensor.cc
	
	Released into the public domain.
	
	Created by J Saavedra, October 2010.
	http://jos.ph
*/

#if (ARDUINO >= 100)
    #include "Arduino.h"
#else
    #include <avr/io.h>
    #include "WProgram.h"
#endif

#include "MQ7.h"

MQ7::MQ7(int CoPWMPin, int CoIndicatorPin, int analogPin){

	pinMode(CoIndicatorPin, OUTPUT);
	pinMode(CoPWMPin, OUTPUT);
	
	_CoIndicatorPin = CoIndicatorPin;
	_CoPWMPin = CoPWMPin;
	_analogPin=analogPin;
    
    indicatorAttached = true; //we are using an LED to show heater
	
	time = 0;
	currTime = 0;
	prevTime = 0;
	currCoPwrTimer = 0;
	CoPwrState = LOW;
  	currCoPwrTimer = 500;
	
}

MQ7::MQ7(int CoPWMPin, int analogPin){
    
	pinMode(CoPWMPin, OUTPUT);
	
    indicatorAttached = false; //not using an LED
    
	_CoPWMPin = CoPWMPin;
	_analogPin=analogPin;
	
	time = 0;
	currTime = 0;
	prevTime = 0;
	currCoPwrTimer = 0;
	CoPwrState = LOW;
  	currCoPwrTimer = 500;
}

MQ7::MQ7(int analogPin){
  _analogPin=analogPin;
}

void MQ7::CoPwrCycler(){
  
  currTime = millis();
   
  if (currTime - prevTime > currCoPwrTimer){
    prevTime = currTime;
    
    if(CoPwrState == LOW){
      CoPwrState = HIGH;
      currCoPwrTimer = 60000;  //60 seconds at 5v
    }
    else{
      CoPwrState = LOW;
      currCoPwrTimer = 90000;  //90 seconds at 1.4v
    }
    if(indicatorAttached) digitalWrite(_CoIndicatorPin, CoPwrState);
    digitalWrite(_CoPWMPin, CoPwrState);
  }
}

float MQ7::readValue(String units){
	float analogValue=float (analogRead(_analogPin));
	float convertedValue;
	// TODO: Add conversion for other concentration units
	if(units=="ppm"){
		convertedValue=(((2000-20)/1023)*analogValue+20)/(1000);
	}
	else if(units=="ppb"){
		convertedValue=(((10000-300)/1023)*analogValue+300);
	}
	else{
		Serial.println("MQ7 units not recognized, please use help() function for available units");
	}
	return convertedValue;
}

bool  MQ7::dataAvailable(){
	if(CoPwrState == LOW){
		return false;
	}
	else{
		return true;
	}
}

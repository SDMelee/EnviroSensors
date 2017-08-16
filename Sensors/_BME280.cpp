/****************************************************************************************************
_BME280.cpp
BME280 Arduino library
Amelia Peterson w/ CSDT @ RPI
Contact: petera7@rpi.edu
Last Updated: 08/15/2017

Visit our site at: www.csdt.rpi.edu

Description:
  Implementation of functions defined in _BME280.h; see header file for general overview and concepts.
  The functionality of _BME280::begin() is taken from the Sparkfun BME280 example code,
I2C_and_SPI_Multisensor.ino. This is the main component of the BME280 code that we need to encapsulate
for the students to use the sensor. It will automatically define the necessary settings for the
specified communication protocol. It calls the parent BME280::begin() function at the end.
  Note that the BME280 read functions will call Wire.beginTransmission(settings.I2CAddress) before reading,
so we do not have to worry about I2C device management here when controlling multiple sensors.
****************************************************************************************************/

#include "_BME280.h"

_BME280::_BME280(int sda, int scl, String mode){
	_sda=sda;
	_scl=scl;
	_mode=mode;	
}

void _BME280::begin(){
	if(_mode=="i2c"){
		// FROM I2C_and_SPI_Multisensor.ino
		/***Set up sensor '_I2C'******************************/
		settings.commInterface = I2C_MODE;
		//specify I2C address.  Can be 0x77(default) or 0x76
		settings.I2CAddress = 0x77;
		settings.runMode = 3; //  3, Normal mode
		settings.tStandby = 0; //  0, 0.5ms
		settings.filter = 0; //  0, filter off
		//tempOverSample can be:
		//  0, skipped
		//  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
		settings.tempOverSample = 1;
		//pressOverSample can be:
		//  0, skipped
		//  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
	    settings.pressOverSample = 1;
		//humidOverSample can be:
		//  0, skipped
		//  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
		settings.humidOverSample = 1;
	}
	else if(_mode=="spi"){
		//***Set up sensor 'SPI'******************************//
		//specify chipSelectPin using arduino pin names
		settings.commInterface = SPI_MODE;
		settings.chipSelectPin = 10;
		settings.runMode = 3; //  3, Normal mode
		settings.tStandby = 0; //  0, 0.5ms
		settings.filter = 0; //  0, filter off
		//tempOverSample can be:
		//  0, skipped
		//  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
		settings.tempOverSample = 1;
		//pressOverSample can be:
		//  0, skipped
		//  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
	    settings.pressOverSample = 1;
		//humidOverSample can be:
		//  0, skipped
		//  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
		settings.humidOverSample = 1;
	}
	else{
		Serial.println("BME280 mode not recognized. Use BME280::help() for available modes.");
	}
	Serial.begin(57600);
	delay(10);  //Make sure sensor had enough time to turn on. BME280 requires 2ms to start up.
	//Calling BME280::begin() causes the settings to be loaded
	BME280::begin();
}

float _BME280::readTemp(String units){
	if(units=="C")
		return readTempC();
	else if(units=="F")
		return readTempF();
	else if(units=="K")
		return (readTempC()+273.15);
	else
		Serial.println("BME280 units not recognized. Use help() for available units.");
}

float _BME280::readPressure(String units){
	if(units=="Pa")
		return readFloatPressure();
	else if(units=="Torr")
		return (readFloatPressure()*(760.0/101325.0));		// 760 torr/101325 Pa
	else if(units=="atm")
		return (readFloatPressure()*(1/101325.0));			// 1 atm/101325 Pa
	else
		Serial.println("BME280 units not recognized. Use help() for available units.");
}

float _BME280::readAltitude(String units){
	if(units=="meters")
		return readFloatAltitudeMeters();
	else if(units=="km")
		return readFloatAltitudeMeters()/1000.0;
	else if(units=="ft")
		return readFloatAltitudeFeet();
	else
		Serial.println("BME280 units not recognized. Use help() for available units.");
}

float _BME280::readHumidity(String units){
	if(units=="%")
		return readFloatHumidity();
	else
		Serial.println("BME280 units not recognized. Use help() for available units.");
}

void _BME280::help(){
	bool _exit=false;
	Serial.print("The BME280 sensor provides information about the atmosphere.");
	Serial.print("It can sense temperature, humidity, barometric pressure, and");
	Serial.println(" altitude.");
	// Serial.println("For additional information about wiring, go to: <csdt page>");		// Link to environmental sensors page on CSDT site once it is setup
	Serial.println(" To see available units for a variable, enter one of the following letters:");
	Serial.println("  Temperature:    T");
	Serial.println("  Humidity:       H");
	Serial.println("  Pressure:       P");
	Serial.println("  Altitude:       A");
	Serial.println("  Exit help:      E");
	while(!_exit){
		// Get character
		char _input=0;
		while(_input==0){
			if(Serial.available()>0)
				_input=Serial.read();
		}
		if(_input=='T'){
			Serial.println("Available units for Temperature: ");
			Serial.println("  Celsius:        C");
			Serial.println("  Farhenheit:     F");
			Serial.println("  Kelvin:         K");
		}
		else if(_input=='H'){
			Serial.println("Available units for Humidity: ");
			Serial.println("  Percent:        %");
		}
		else if(_input=='P'){
			Serial.println("Available units for Pressure: ");
			Serial.println("  Pascal:         Pa");
			Serial.println("  Torr:           Torr");
			Serial.println("  Atmospheres:    atm");
		}
		else if(_input=='A'){
			Serial.println("Available units for Altitude: ");
			Serial.println("  Meters:         m");
			Serial.println("  Kilometers:     km");
			Serial.println("  Feet:           ft");
		}
		else if(_input=='E'){
			Serial.println("Exiting help...");
			_exit=true;
		}
		else{
			Serial.println("Input not recognized.");
		}
	}
}
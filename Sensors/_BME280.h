/****************************************************************************************************
_BME280.h
BME280 Atmospheric Sensor Arduino library
Amelia Peterson w/ CSDT @ RPI
Contact: petera7@rpi.edu
Last Updated: 08/15/2017

Visit our site at: www.csdt.rpi.edu

Description:
  This class inherits from the Sparkfun BME280 class (see https://github.com/sparkfun/BME280_Breakout).
It is meant to simplify the use of the BME280 atmospheric sensor on Arduino boards so that K-12
students can use them without needing to learn about the underlying communication protocol.
  The read functions defined here simply call the BME280's read functions and convert their units
as necessary.
  The SDA and SCL pins will be A4 and A5 for the Arduino UNO boards. We don't actually use the _sda
and _scl members, but but they are included to provided students with consistency between sensor 
constructors and to bring their attention to where they are placing their pins.
****************************************************************************************************/

#ifndef BME280_H
#define BME280_H

#include "Arduino.h"
#include "SparkFunBME280.h"

class _BME280 : public BME280{
public:
	  _BME280(int sda, int scl, String mode);

    void begin();          // sets and loads communication settings
                           // use in setup() to begin communication

    float readHumidity(String units);
    float readAltitude(String units);
    float readTemp(String units);
    float readPressure(String units);

    void help();

private:
    int _sda;
    int _scl;
    String _mode;           // "i2c" or "spi"
};

#endif

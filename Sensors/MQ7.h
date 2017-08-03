
/*
  This is a modified version of the Citizen Sensor MQ7 project:  
    CS_MQ7_02.h - Library for reading the MQ-7 Carbon Monoxide Sensor
    Breakout, as part of the Citizen Sensor project.  
    http://citizensensor.cc
    
    Released into the public domain.
    
    Created by J Saavedra, October 2010.
    http://jos.ph
  This code interacts with a slightly different circuitry that requires
  a PWM output instead of just a toggle pin. It also makes the interface
  different for use with the environmental sensors library.

  TODO:: 
        1.  Run power cycling in the background via interrupts.
          Make sure this doesn't interfere with communication protocols
          on others sensors.
        2.  Add option for relay circuit OR op amp circuit.
*/

#ifndef MQ7_h
#define MQ7_h

class MQ7{

  public:
    MQ7(int CoPWMPin, int CoIndicatorPin, int analogPin);
    MQ7(int CoPWMPin, int analogPin);
    void CoPwrCycler();
    bool dataAvailable();
    float readValue(String units);
    
    unsigned long time;
    unsigned long currTime;
    unsigned long prevTime;
    unsigned long currCoPwrTimer;

    bool CoPwrState;
    bool indicatorAttached;
    
  private:
    int _CoIndicatorPin;
    int _CoPWMPin;
    int _analogPin;
};

#endif
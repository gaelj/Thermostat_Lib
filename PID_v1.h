#ifndef PID_v1_h
#define PID_v1_h
#define LIBRARY_VERSION    2.0.0

#include <Arduino.h>
#include "settings.h"
#include "globals.h"

class PID {
public:
    #define AUTOMATIC   1
    #define MANUAL      0

    #define DIRECT      0
    #define REVERSE     1
    
    #define P_ON_M      0
    #define P_ON_E      1

    #define POn                     P_ON_E
    #define ControllerDirection     DIRECT

    PID();
    void Create(float, float, float, float*, float*);     // * Constructor. Initial tuning parameters are set here.
                                          // * clamps the output to a specific range. 0-255 by default, but
                                          //   it's likely the user will want to change this depending on
                                          //   the application
                                          //   sets the frequency, in Milliseconds, with which 
                                          //   the PID calculation is performed.  default is 100

    float Compute();                      // * performs the PID calculation.  it should be
                                          //   called every time loop() cycles. ON/OFF and
                                          //   calculation frequency can be set using SetMode
                                          //   SetSampleTime respectively

    void SetMode(int);                    // * sets PID to either Manual (0) or Auto (non-0)

    float outputSum, lastInput, lastOutput, error, dInput, lastSetpoint;

private:
    void Initialize();
    void InvertPidParameters();           // * Make each PID parameter negative
    void SetTunings();                    // * While most users will set the tunings once in the 
                                          //   constructor, this function gives the user the option
                                          //   of changing tunings during runtime for Adaptive control
                                          //   and proportional mode

    float kp;                             // * (P)roportional Tuning Parameter
    float ki;                             // * (I)ntegral Tuning Parameter
    float kd;                             // * (D)erivative Tuning Parameter

    unsigned long lastTime;
    float outMin, outMax;

    float* input;
    float* mySetpoint;
    bool inAuto;
};

extern PID PIDREG;

#endif // PID_v1_h

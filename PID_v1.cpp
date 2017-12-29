/**********************************************************************************************
 * Arduino PID Library - Version 2.0.0
 * by Brett Beauregard <br3ttb@gmail.com> brettbeauregard.com
 * modified by Gaël James <gaeljames@gmail.com>
 *
 * This Library is licensed under a GPLv3 License
 **********************************************************************************************/

#include <PID_v1.h>

unsigned long now;

/*Constructor (...)*********************************************************
 *    The parameters specified here are those for which we can't set up
 *    reliable defaults, so we need to have the user set them.
 ***************************************************************************/
PID::PID()
{
    lastOutput = 0;
    outputSum = 0;
    error = 0;
    dInput = 0;
}

void PID::Create(const float initialInput, const float Min, const float Max, float* temperature, float* setPoint)
{
    input = temperature;
    mySetpoint = setPoint;

    lastInput = initialInput;
    inAuto = false;

    // Set output limits
    if (Min >= Max) return;
    outMin = Min;
    outMax = Max;

    SetTunings();

    if (millis() > TheSettings.SampleTime)
        lastTime = millis() - TheSettings.SampleTime;
    else
        lastTime = 0;
}

/* Compute() **********************************************************************
 *     This, as they say, is where the magic happens. this function should be called
 *   every time "void loop()" executes. returns the output when the output is computed,
 *   or -1 when nothing has been done.
 **********************************************************************************/
float PID::Compute()
{
    //Serial.println("Computing PID");

    if (!inAuto) return -1;
    now = millis();
    //unsigned long timeChange = (now - lastTime);
    //if (timeChange < TheSettings.SampleTime) return -1;

    //Compute all the working error variables
    error = *mySetpoint - *input;
    dInput = (*input - lastInput);
    outputSum += (ki * error);

    //Add Proportional on Measurement, if P_ON_M is specified
    if (POn != P_ON_E) outputSum -= kp * dInput;

    constrain(outputSum, outMin, outMax);

    //Add Proportional on Error, if P_ON_E is specified
    if (POn == P_ON_E) lastOutput = kp * error;
    else lastOutput = 0;

    //Compute Rest of PID Output
    lastOutput += outputSum - (kd * dInput);

    constrain(lastOutput, outMin, outMax);
    
    //Remember some variables for next time
    lastInput = *input;
    lastTime = now;

    return lastOutput;
}

/* SetTunings(...)*************************************************************
 * This function allows the controller's dynamic performance to be adjusted.
 * it's called automatically from the constructor, but tunings can also
 * be adjusted on the fly during normal operation
 ******************************************************************************/
void PID::SetTunings()
{
    float SampleTimeInSec = float(TheSettings.SampleTime) / 1000;
    kp = TheSettings.Kp;
    ki = TheSettings.Ki * SampleTimeInSec;
    kd = TheSettings.Kd / SampleTimeInSec;

    if (ControllerDirection == REVERSE)
        InvertPidParameters();
}

/* SetMode(...)****************************************************************
 * Allows the controller Mode to be set to manual (0) or Automatic (non-zero)
 * when the transition from manual to auto occurs, the controller is
 * automatically initialized
 ******************************************************************************/
void PID::SetMode(int Mode)
{
    bool newAuto = (Mode == AUTOMATIC);
    if (newAuto && !inAuto)  //we just went from manual to auto
        Initialize();
    inAuto = newAuto;
}

/* Initialize()****************************************************************
 *    does all the things that need to happen to ensure a bumpless transfer
 *  from manual to automatic mode.
 ******************************************************************************/
void PID::Initialize()
{
    outputSum = lastOutput;
    lastInput = lastInput;
    constrain(outputSum, outMin, outMax);
}

/**
* @brief Make each PID parameter negative
*
*/
void PID::InvertPidParameters()
{
    kp = (0 - kp);
    ki = (0 - ki);
    kd = (0 - kd);
}

#include <Arduino.h>
#include "ExtendedStepper.hpp"
#include "SM_42BYG011_25.hpp"

#define pwmA 3
#define pwmB 11
#define brakeA 9
#define brakeB 8
#define dirA 12
#define dirB 13

SM_42BYG011_25 stepMotor(dirA, dirB, brakeA, brakeB, pwmA, pwmB);

//const float ROTATION_MAX = 360.0;
//const float ROTATION_MAX = 180.0;
const float ROTATION_MAX = 90;

void restartRotation(ExtendedStepper& instance)
{
    Serial.println("Max. rotation reached. Reversing...");
    Serial.flush();

    instance.Rotate(ROTATION_MAX * -instance.GetStepDirection());
}

void setup(void)
{
    delay(2500);
    Serial.begin(9600);

    stepMotor.Begin();
    stepMotor.setSpeed(10);
    stepMotor.SetOnEndRotationEvent(restartRotation);
    stepMotor.Rotate(ROTATION_MAX / 2.0);
}

void loop(void)
{
    stepMotor.UpdateRotation();
}

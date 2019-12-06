#ifndef __EXTENDEDSTEPPER_HPP__
#define __EXTENDEDSTEPPER_HPP__

#include <stdint.h>     /* uint8_t */
#include <Arduino.h>
#include <Stepper.h>

class ExtendedStepper : public Stepper
{
public:
    typedef void(*OnRotationEndedEventHandler)(ExtendedStepper&);

private:
    int m_StepsPerRevolution;
    float m_StepsPerDegree;

    int m_StepEndpoint = 0;
    int m_Steps = 0;
    int8_t m_StepDirection = 0;

    OnRotationEndedEventHandler m_OnEndRotationEvent;

    void Initialize(const int steps);

public:
    float GetAngle(void) const;
    int8_t GetStepDirection(void) const;

    void SetOnEndRotationEvent(const OnRotationEndedEventHandler value);

    void Rotate(const float degrees);
    void UpdateRotation(void);

    ExtendedStepper(const int stepsPerRevolution, const bool halfSteps, const uint8_t motorPin1, const uint8_t motorPin2);
    ExtendedStepper(const int stepsPerRevolution, const bool halfSteps, const uint8_t motorPin1, const uint8_t motorPin2, const uint8_t motorPin3, const uint8_t motorPin4);
    ExtendedStepper(const int stepsPerRevolution, const bool halfSteps, const uint8_t motorPin1, const uint8_t motorPin2, const uint8_t motorPin3, const uint8_t motorPin4, const uint8_t motorPin5);
};

#endif // __EXTENDEDSTEPPER_HPP__

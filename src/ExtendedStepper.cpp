#include "ExtendedStepper.hpp"

#define sgn(x) (((x) > 0) - ((x) < 0))  // (x > 0) - (x < 0)

float ExtendedStepper::GetAngle(void) const
{
    int steps = m_Steps;
    if(steps >= m_StepEndpoint)
    {
        steps = steps - ((int)(steps / 360.0) * 360.0);
    }

    float angle = (m_StepDirection >= 0 && steps ? steps : m_StepEndpoint - steps) / m_StepsPerDegree;
    return angle;
}

int8_t ExtendedStepper::GetStepDirection(void) const
{
    return m_StepDirection;
}

void ExtendedStepper::SetOnEndRotationEvent(const OnRotationEndedEventHandler value)
{
    m_OnEndRotationEvent = value;
}

void ExtendedStepper::Rotate(const float degrees)
{
    m_StepDirection = sgn(degrees);
    m_StepEndpoint = abs(degrees) * m_StepsPerDegree;
    m_Steps = 0;
}

void ExtendedStepper::UpdateRotation(void)
{
    if(m_Steps >= m_StepEndpoint) { return; }

    step(m_StepDirection);
    m_Steps++;

    if(m_Steps >= m_StepEndpoint)
    {
        if(m_OnEndRotationEvent != nullptr)
        {
            m_OnEndRotationEvent(*this);
        }
    }
}

void ExtendedStepper::Initialize(const int steps)
{
    m_StepsPerRevolution = steps;
    m_StepsPerDegree = steps / 360.0f;
}

ExtendedStepper::ExtendedStepper(const int stepsPerRevolution, const bool halfSteps, const uint8_t motorPin1, const uint8_t motorPin2) : Stepper::Stepper(stepsPerRevolution, motorPin1, motorPin2)
{
    Initialize(halfSteps ? stepsPerRevolution / 2 : stepsPerRevolution);
}

ExtendedStepper::ExtendedStepper(const int stepsPerRevolution, const bool halfSteps, const uint8_t motorPin1, const uint8_t motorPin2, const uint8_t motorPin3, const uint8_t motorPin4) : Stepper::Stepper(stepsPerRevolution, motorPin1, motorPin2, motorPin3, motorPin4)
{
    Initialize(halfSteps ? stepsPerRevolution / 2 : stepsPerRevolution);
}

ExtendedStepper::ExtendedStepper(const int stepsPerRevolution, const bool halfSteps, const uint8_t motorPin1, const uint8_t motorPin2, const uint8_t motorPin3, const uint8_t motorPin4, const uint8_t motorPin5) : Stepper::Stepper(stepsPerRevolution, motorPin1, motorPin2, motorPin3, motorPin4, motorPin5)
{
    Initialize(halfSteps ? stepsPerRevolution / 2 : stepsPerRevolution);
}

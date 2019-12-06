#include "SM_42BYG011_25.hpp"

void SM_42BYG011_25::Begin(void) const
{
    pinMode(m_PWMPins[0], OUTPUT);
    pinMode(m_PWMPins[1], OUTPUT);
    pinMode(m_BrakePins[0], OUTPUT);
    pinMode(m_BrakePins[1], OUTPUT);

    digitalWrite(m_PWMPins[0], HIGH);
    digitalWrite(m_PWMPins[1], HIGH);
    digitalWrite(m_BrakePins[0], LOW);
    digitalWrite(m_BrakePins[1], LOW);
}

SM_42BYG011_25::SM_42BYG011_25(const uint8_t dirPinA, const uint8_t dirPinB, const uint8_t brakePinA, const uint8_t brakePinB, const uint8_t pwmPinA, const uint8_t pwmPinB) : ExtendedStepper(SM_42BYG011_25::STEPS_PER_REVOLUTION, false, dirPinA, dirPinB), m_DirPins {dirPinA, dirPinB}, m_BrakePins { brakePinA, brakePinB }, m_PWMPins { pwmPinA, pwmPinB } { }

#ifndef __SM_42BYG011_25_HPP__
#define __SM_42BYG011_25_HPP__

#include <stdint.h>
#include <Arduino.h>
#include "ExtendedStepper.hpp"

class SM_42BYG011_25 : public ExtendedStepper
{
private:
    uint8_t m_DirPins[2];
    uint8_t m_BrakePins[2];
    uint8_t m_PWMPins[2];

public:
    static const int STEPS_PER_REVOLUTION = 200;

    void Begin(void) const;

    SM_42BYG011_25(const uint8_t dirPinA, const uint8_t dirPinB, const uint8_t brakePinA, const uint8_t brakePinB, const uint8_t pwmPinA, const uint8_t pwmPinB);
};

#endif // __SM_42BYG011_25_HPP__

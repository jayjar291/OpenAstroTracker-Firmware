#pragma once

#include "Driver.hpp"
#include "utils/SteppingHelper.hpp"

#define INIT_STATE_FULL_STEP 0b00110011
#define INIT_STATE_HALF_STEP 0b00000111

class ULN2003 : public Driver
{
public:
    ULN2003(
        const StepperSpecs &stepper,
        uint16_t ms,
        uint8_t pin_in1,
        uint8_t pin_in2,
        uint8_t pin_in3,
        uint8_t pin_in4);

    void setup() override;

    void loop() override;

    float getPosition() const override;

private:
    inline void applySequenceStateToPins();

    const uint8_t _pin_in1;
    const uint8_t _pin_in2;
    const uint8_t _pin_in3;
    const uint8_t _pin_in4;

    uint8_t _pinStateSequence;

    uint8_t (*rot)(const uint8_t, const uint8_t);

    SteppingHelper _stepHelper;
};

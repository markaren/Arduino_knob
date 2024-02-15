
#ifndef ANALOGPIN_HPP
#define ANALOGPIN_HPP

#include <Arduino.h>

struct AnalogPin {

    explicit AnalogPin(int pin) : pin_(pin) {}

    int read() const {
        return analogRead(pin_);
    }

private:
    int pin_;
};

#endif// ANALOGPIN_HPP

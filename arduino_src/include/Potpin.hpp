
#include <Arduino.h>

#ifndef POTPINS_POTPIN_HPP
#define POTPINS_POTPIN_HPP

struct Potpin {

  explicit Potpin(int pin) : pin_(pin) {}

  int read() const {
    return analogRead(pin_);
  }

private:
  int pin_;
};

#endif // POTPINS_POTPIN_HPP

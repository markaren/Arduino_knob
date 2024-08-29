#include "ArduinoJson.hpp"
#include <Arduino.h>

#include "AnalogPin.hpp"

using namespace ArduinoJson;

namespace {
    AnalogPin p1(A0);
    AnalogPin p2(A1);

    StaticJsonDocument<24> doc;

    volatile bool buttonPressed{false};
}// namespace

void buttonInterrupt() {
    buttonPressed = true;// Set the flag when the interrupt is triggered
}

void setup() {
    pinMode(PIN2, INPUT);
    attachInterrupt(digitalPinToInterrupt(PIN2), buttonInterrupt, FALLING);

    Serial.begin(115200);
}

void loop() {

    doc["potVal1"] = p1.read();
    doc["potVal2"] = p2.read();
    doc["buttonPressed"] = buttonPressed ? 1 : 0;
    if (buttonPressed) {
        buttonPressed = false;
    }

    serializeJson(doc, Serial);
    Serial.println();

    delay(50);
}



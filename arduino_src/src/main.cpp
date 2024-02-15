#include "ArduinoJson.hpp"
#include <Arduino.h>

#include "AnalogPin.hpp"

using namespace ArduinoJson;

namespace {
    AnalogPin p1(A0);
    AnalogPin p2(A1);

    volatile bool buttonPressed{false};
}// namespace

void buttonInterrupt();

void setup() {
    pinMode(PIN2, INPUT);
    attachInterrupt(digitalPinToInterrupt(PIN2), buttonInterrupt, FALLING);

    Serial.begin(115200);
}

void loop() {
    int potVal1 = p1.read();
    int potVal2 = p2.read();

    StaticJsonDocument<32> doc;
    doc["potVal1"] = potVal1;
    doc["potVal2"] = potVal2;
    doc["buttonPressed"] = buttonPressed ? 1 : 0;
    if (buttonPressed) {
        buttonPressed = false;
    }

    serializeJson(doc, Serial);
    Serial.println();

    delay(50);
}

void buttonInterrupt() {
    buttonPressed = true;// Set the flag when the interrupt is triggered
}

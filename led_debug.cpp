#include "led_debug.h"
#include <Arduino.h>

LedDebug::LedDebug(const int pin, const long flashTimeMS) :
    ledPin(pin),
    flashTimeMS(flashTimeMS),
    lastFlashTime(0) {}

LedDebug::~LedDebug() {}

void LedDebug::initialize() {
    pinMode(this->ledPin, OUTPUT);    
}

void LedDebug::update() {
    unsigned long currentTime = millis();
    if(currentTime > (this->lastFlashTime + this->flashTimeMS)) {
        digitalWrite(this->ledPin, LOW);    
    }
}

void LedDebug::flash() {
    digitalWrite(this->ledPin, HIGH);
    this->lastFlashTime = millis(); 
}


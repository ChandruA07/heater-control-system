#include "heater_fsm.h"
#include <Arduino.h>

// Thresholds
#define HEATING_THRESHOLD 20.0
#define TARGET_TEMP 23.0
#define STAB_BAND 0.5
#define OVERHEAT_THRESHOLD 28.0
#define HOLD_MS 5000

HeaterFSM::HeaterFSM(int t, int h, int l, int b) :
   tempSensor(t), heater(h), led(l), buzzer(b), state(Idle), lastStable(0) {}

void HeaterFSM::init() {
    pinMode(heater, OUTPUT);
    pinMode(led, OUTPUT);
    pinMode(buzzer, OUTPUT);
}

float HeaterFSM::readTemperature() {
    int ad = analogRead(tempSensor);
    return ad * 50.0 / 4095; 
}

void HeaterFSM::updateState(float t) {
    switch(state) {
        case Idle:
            if (t < HEATING_THRESHOLD) state = Heating;
            else if (t > OVERHEAT_THRESHOLD) state = Overheat;
            break;
        case Heating:
            if (t >= TARGET_TEMP - STAB_BAND) state = Stabilizing;
            else if (t > OVERHEAT_THRESHOLD) state = Overheat;
            break;
        case Stabilizing:
            if (t <= TARGET_TEMP + STAB_BAND && t >= TARGET_TEMP - STAB_BAND) {
                if (!lastStable) lastStable = millis();
                if (millis() - lastStable > HOLD_MS) state = TargetReached;
            } else {
                lastStable = 0;
                if (t < HEATING_THRESHOLD) state = Heating;
                else if (t > OVERHEAT_THRESHOLD) state = Overheat;
            }
            break;
        case TargetReached:
            if (t < TARGET_TEMP - STAB_BAND) state = Heating;
            else if (t > OVERHEAT_THRESHOLD) state = Overheat;
            break;
        case Overheat:
            if (t < TARGET_TEMP) state = Idle;
            break;
    }
}

void HeaterFSM::controlOutputs() {
    // Heater control
    digitalWrite(heater, (state == Heating || state == Stabilizing) ? HIGH : LOW);
    // LED/buzzer feedback
    if (state == Overheat) {
        digitalWrite(led, HIGH);
        digitalWrite(buzzer, HIGH);
    } else if (state == TargetReached) {
        digitalWrite(led, HIGH); digitalWrite(buzzer, LOW);
    } else {
        digitalWrite(led, LOW); digitalWrite(buzzer, LOW);
    }
}

void HeaterFSM::log(float t) {
    Serial.print("Temp: "); Serial.print(t, 2);
    Serial.print(" | State: ");
    switch(state) {
        case Idle: Serial.print("Idle"); break;
        case Heating: Serial.print("Heating"); break;
        case Stabilizing: Serial.print("Stabilizing"); break;
        case TargetReached: Serial.print("TargetReached"); break;
        case Overheat: Serial.print("Overheat"); break;
    }
    Serial.print(" | Heater: "); Serial.println(digitalRead(heater) ? "ON" : "OFF");
}

void HeaterFSM::run() {
    float t = readTemperature();
    updateState(t);
    controlOutputs();
    log(t);
}

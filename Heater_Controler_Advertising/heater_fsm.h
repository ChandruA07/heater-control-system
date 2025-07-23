#pragma once
#include <BLEDevice.h>

enum HeaterState { Idle, Heating, Stabilizing, TargetReached, Overheat };

class HeaterFSM {
public:
    HeaterFSM(int tempPin, int heaterPin, int ledPin, int buzzerPin);
    void init();
    void run();
private:
    void updateState(float temp);
    float readTemperature();
    void controlOutputs();
    void log(float temp);
    void advertiseState();
    String stateToString();

    HeaterState state, prevState;
    int tempSensor, heater, led, buzzer;
    unsigned long lastStable;
    BLEAdvertising* pAdvertising;
};

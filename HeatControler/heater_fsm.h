#pragma once

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

    HeaterState state;
    int tempSensor, heater, led, buzzer;
    unsigned long lastStable;
};

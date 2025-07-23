#include "heater_fsm.h"
#include <Arduino.h>

#define HEATING_THRESHOLD    20.0
#define TARGET_TEMP          23.0
#define STAB_BAND            0.5
#define OVERHEAT_THRESHOLD   28.0
#define HOLD_MS            5000

HeaterFSM::HeaterFSM(int t, int h, int l, int b)
  : tempSensor(t), heater(h), led(l), buzzer(b),
    state(Idle), prevState(Idle), lastStable(0), pAdvertising(nullptr) {}

void HeaterFSM::init() {
  pinMode(heater, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);

  BLEDevice::init("HeaterFSM");
  pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->setScanResponse(false);
  advertiseState();
  pAdvertising->start();
}

float HeaterFSM::readTemperature() {
  return analogRead(tempSensor) * 50.0 / 4095;
}

String HeaterFSM::stateToString() {
  switch(state) {
    case Idle:           return "Idle";
    case Heating:        return "Heating";
    case Stabilizing:    return "Stabilizing";
    case TargetReached:  return "Target";
    case Overheat:       return "Overheat";
    default:             return "Unknown";
  }
}

void HeaterFSM::advertiseState() {
  String advData = "State:" + stateToString();
  BLEAdvertisementData adv;
  adv.setName("HeaterFSM");
  adv.setManufacturerData(advData);
  if (pAdvertising) {
    pAdvertising->setAdvertisementData(adv);
    pAdvertising->start();
  }
  // Optional for debug:
  Serial.print("BLE Advertise: "); Serial.println(advData);
}

void HeaterFSM::updateState(float t) {
  prevState = state;
  switch(state) {
    case Idle:
      if (t < HEATING_THRESHOLD)        state = Heating;
      else if (t > OVERHEAT_THRESHOLD)  state = Overheat;
      break;
    case Heating:
      if (t >= TARGET_TEMP - STAB_BAND) state = Stabilizing;
      else if (t > OVERHEAT_THRESHOLD)  state = Overheat;
      break;
    case Stabilizing:
      if (t >= TARGET_TEMP - STAB_BAND && t <= TARGET_TEMP + STAB_BAND) {
        if (!lastStable) lastStable = millis();
        if (millis() - lastStable > HOLD_MS) state = TargetReached;
      } else {
        lastStable = 0;
        if (t < HEATING_THRESHOLD)      state = Heating;
        else if (t > OVERHEAT_THRESHOLD) state = Overheat;
      }
      break;
    case TargetReached:
      if (t < TARGET_TEMP - STAB_BAND)      state = Heating;
      else if (t > OVERHEAT_THRESHOLD)      state = Overheat;
      break;
    case Overheat:
      if (t < TARGET_TEMP) state = Idle;
      break;
  }
  if (state != prevState) advertiseState();
}

void HeaterFSM::controlOutputs() {
  digitalWrite(heater, (state == Heating || state == Stabilizing) ? HIGH : LOW);
  static unsigned long lastBlink = 0;
  static bool ledState = false;
  if (state == Overheat) {
    // Blink status LED at 2 Hz
    if (millis() - lastBlink > 250) {
      ledState = !ledState;
      digitalWrite(led, ledState);
      lastBlink = millis();
    }
    digitalWrite(buzzer, HIGH);
  } else if (state == TargetReached) {
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, LOW);
    ledState = false;
  } else {
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
    ledState = false;
  }
}

void HeaterFSM::log(float t) {
  Serial.print("Temp: "); Serial.print(t, 2);
  Serial.print(" | State: "); Serial.print(stateToString());
  Serial.print(" | Heater: "); Serial.println(digitalRead(heater) ? "ON" : "OFF");
}

void HeaterFSM::run() {
  float t = readTemperature();
  updateState(t);
  controlOutputs();
  log(t);
}

#include <Arduino.h>
#include "heater_fsm.h"

const int TEMP_SENSOR_PIN = 34; 
const int HEATER_PIN = 2;       
const int STATUS_LED_PIN = 4;   
const int BUZZER_PIN = 16;     

HeaterFSM heater(TEMP_SENSOR_PIN, HEATER_PIN, STATUS_LED_PIN, BUZZER_PIN);

void setup() {
  Serial.begin(115200);
  heater.init();
}

void loop() {
  heater.run();
  delay(500);
}

#include <Arduino.h>
#include <arduino_homekit_server.h>
#include "wifi_info.h"
#include <Servo.h> 

Servo servoObject; 
int position = 0;
int posEin = 90;
int posAus = 90; 
const int waitTime = 5; 

void setup() {
  pinMode(D8, OUTPUT);
  pinMode(D0, OUTPUT);
  Serial.begin(115200);
  // Servo an digiteln Port D0
  servoObject.attach(D0);
  digitalWrite(D8, HIGH);
  wifi_connect();
  homekit_storage_reset();
  my_homekit_setup();
}

void loop() {
  my_homekit_loop();
  delay(10);
}

//==============================
// HomeKit setup and loop
//==============================

// Zugriff auf die Definitionen des Accessories in my_accessory.c
extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_switch_on;

static uint32_t next_heap_millis = 0;

#define PIN_SWITCH D1

// Diese Funktion wird aufgerufen, wenn der Schalter in HomeKit betätigt wird
void cha_switch_on_setter(const homekit_value_t value) {
  bool myPowerState = value.bool_value;
  Serial.println(myPowerState ? "wurde eingeschaltet" : "wurde ausgeschaltet");
  if (myPowerState == HIGH) {
    digitalWrite(D8, 1); // turn on Relais
    delay(500);
    servoObject.write(95); // turn Servo to On-position
    delay(500);
    digitalWrite(D8, 0); // turn off Relais
  } else {
    digitalWrite(D8, 1); // turn on Relais
    delay(500);
    servoObject.write(75); // turn Servo to Off-position
    delay(500);
    digitalWrite(D8, 0); // turn off Relais
  }
}

void my_homekit_setup() {
  pinMode(PIN_SWITCH, OUTPUT);
  digitalWrite(PIN_SWITCH, HIGH);
  cha_switch_on.setter = cha_switch_on_setter;
  arduino_homekit_setup(&config);
}

void my_homekit_loop() {
  arduino_homekit_loop();
  const uint32_t t = millis();
  if (t > next_heap_millis) {
    // heap-Info alle 30 Sekunden im seriellen Monitor ausgeben
    next_heap_millis = t + 30 * 1000;
  }
}

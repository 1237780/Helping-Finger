#ifdef ENABLE_DEBUG
#define DEBUG_ESP_PORT Serial
#define NODEBUG_WEBSOCKETS
#define NDEBUG
#endif

#include <Arduino.h>
#include "wifi.h"
#include "SinricPro.h"
#include "SinricProSwitch.h"
#include <Servo.h>

#define APP_KEY           "4733d0f7-0ed4-4d44-a414-1c55e9ecabaa"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "efe58dd5-d701-4bcd-be65-5a68f41d9cff-b9bcb344-8763-4623-83a4-47fde7777c7c"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define SWITCH_ID         "602bec4ae63687229a387eb1"    // Should look like "5dc1564130xxxxxxxxxxxxxx"
#define BAUD_RATE         115200                // Change baudrate to your need

Servo servoObject;
bool myPowerState = false;

bool onPowerState(const String &deviceId, bool &state) {
  Serial.printf("Device %s turned %s (via SinricPro) \r\n", deviceId.c_str(), state ? "on" : "off");
  myPowerState = state;
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
  return true; // request handled properly
}

// setup function for SinricPro
void setupSinricPro() {
  // add device to SinricPro
  SinricProSwitch& mySwitch = SinricPro[SWITCH_ID];

  // set callback function to device
  mySwitch.onPowerState(onPowerState);

  // setup SinricPro
  SinricPro.onConnected([]() {
    Serial.printf("Connected to SinricPro\r\n");
  });
  SinricPro.onDisconnected([]() {
    Serial.printf("Disconnected from SinricPro\r\n");
  });
  SinricPro.begin(APP_KEY, APP_SECRET);
}

// main setup function
void setup() {
  pinMode(D8, OUTPUT); // Relais
  digitalWrite(D8, HIGH);
  pinMode(D0, OUTPUT); // Servo
  servoObject.attach(D0);
  pinMode(D1, INPUT_PULLUP);
  Serial.begin(BAUD_RATE); Serial.printf("\r\n\r\n"); // Start serial port
  setupWiFi(LOW);
  setupSinricPro();
}

void loop() {
  SinricPro.handle();
  if(digitalRead(D1)==0) {
    setupWiFi(HIGH);
    Serial.println("Taster gedrückt");
  }
}

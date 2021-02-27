#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"
#define SERIAL_BAUDRATE                 115200
fauxmoESP fauxmo;
 
// -----------------------------------------------------------------------------
// Wifi definieren
// -----------------------------------------------------------------------------

#define WIFI_SSID "Starlink"
#define WIFI_PASS "JaJoLaKa122"

// -----------------------------------------------------------------------------
// PINs definieren
// -----------------------------------------------------------------------------

#define RELAY_PIN1 LED_BUILTIN
#define ID_YELLOW  "Lampe"

 
 
void wifiSetup() {
  // Set WIFI module to STA mode
  WiFi.mode(WIFI_STA);
 
  // Verbinden
  Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
 
  // Warten
  while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(100);
  }
  Serial.println();
 
  // Verbunden!
  Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}
 
 
void setup() {

// -----------------------------------------------------------------------------
// PINs setzen
// -----------------------------------------------------------------------------
  
  pinMode(RELAY_PIN1, OUTPUT);
  digitalWrite(RELAY_PIN1, LOW);
  
    // Init serial port and clean garbage
    Serial.begin(SERIAL_BAUDRATE);
    Serial.println();
    Serial.println();
    Serial.println("FauxMo Relay Setup");
    Serial.println("Nach der Verbindung sage: Alexa schalte test / test2 an / aus .");
 
  // Wifi
  wifiSetup();
  
// -----------------------------------------------------------------------------
// Endgeraete Namen definieren
// -----------------------------------------------------------------------------

  // Fauxmo
  fauxmo.createServer(true);
  fauxmo.setPort(80);
  fauxmo.enable(true);
  fauxmo.addDevice(ID_YELLOW);
  
  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
        
        // Callback when a command from Alexa is received. 
        // You can use device_id or device_name to choose the element to perform an action onto (relay, LED,...)
        // State is a boolean (ON/OFF) and value a number from 0 to 255 (if you say "set kitchen light to 50%" you will receive a 128 here).
        // Just remember not to delay too much here, this is a callback, exit as soon as possible.
        // If you have to do something more involved here set a flag and process it in your main loop.
        
        Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

        // Checking for device_id is simpler if you are certain about the order they are loaded and it does not change.
        // Otherwise comparing the device_name is safer.

        if (strcmp(device_name, ID_YELLOW)==0) {
            digitalWrite(RELAY_PIN1, state ? HIGH : LOW);
        } 
    });

}
 
void loop() {
  fauxmo.handle();

  static unsigned long last = millis();
    if (millis() - last > 5000) {
        last = millis();
        Serial.printf("[MAIN] Free heap: %d bytes\n", ESP.getFreeHeap());
    }
}

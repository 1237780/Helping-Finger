//Blynk Home Automation with Physical Button and ON OFF State Feedback


#define BLYNK_PRINT Serial            
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266mDNS.h>  // For OTA with ESP8266
#include <WiFiUdp.h>  // For OTA
#include <ArduinoOTA.h>  // For OTA


BlynkTimer timer;

int relay1State = LOW;
int pushButton1State = HIGH;

int relay2State = LOW;
int pushButton2State = HIGH;

int relay3State = LOW;
int pushButton3State = HIGH;

int relay4State = LOW;
int pushButton4State = HIGH;

#define AUTH "Bxw1gdyJIm_2AP30hsJ2x4OzuKThkNFy"   // You should get Auth Token in the Blynk App.  
#define WIFI_SSID "Starlink"                      //Enter Wifi Name
#define WIFI_PASS "JaJoLaKa122"                   //Enter wifi Password

#define SERVER "blynk-cloud.com "             // Comment-out if use Blynk hosted cloud service
#define PORT 8442

#define RELAY_PIN_1      0   //D3


#define VPIN_BUTTON_1    V3


#define OTA_HOSTNAME "Home_Automation"


BLYNK_CONNECTED() {

  // Request the latest state from the server

  Blynk.syncVirtual(VPIN_BUTTON_1);
}

// When App button is pushed - switch the state

  BLYNK_WRITE(VPIN_BUTTON_1) {
  relay1State = param.asInt();
  digitalWrite(RELAY_PIN_1, relay1State);
  Serial.println(relay1State);
}

void setup()
{

  Serial.begin(115200);
  Blynk.begin(AUTH, WIFI_SSID, WIFI_PASS,"blynk-cloud.com", 8442);
  ArduinoOTA.setHostname(OTA_HOSTNAME);  // For OTA - Use your own device identifying name
  ArduinoOTA.begin();  // For OTA

  pinMode(RELAY_PIN_1, OUTPUT);
  digitalWrite(RELAY_PIN_1, relay1State);

  // Setup a function to be called every 100 ms
  //timer.setInterval(500L);
}

void loop()
{
  Blynk.run();
  ArduinoOTA.handle();  // For OTA
  //timer.run();
}

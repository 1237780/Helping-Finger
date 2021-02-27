#ifndef WIFI_H_
#define WIFI_H_

#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

void setupWiFi(bool reset_request) {
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP

    // put your setup code here, to run once:
    Serial.begin(115200);
    
    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;
    if(reset_request == HIGH) {
      wm.resetSettings();      
    }

    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // then goes into a blocking loop awaiting configuration and will return success result

    bool res;
    res = wm.autoConnect("AutoConnectESP","password"); // password protected ap

    if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
    }
}

#endif

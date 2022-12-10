//---------------------------------------------------------
// File       : ESP_8266_WiFi_Connect.h
// Author     : J.Burnham (11-11-2022)
// Purpose    : Definitions File WiFiConnect Class
//---------------------------------------------------------
#include <ESP8266WiFi.h>

#include "ESP_8266_Defs.h"

#ifndef ESP_8266_WIFI_CONNECT_H
#define ESP_8266_WIFI_CONNECT_H


class WiFiConnect {
  public:
  // Constructor(s)
  //-------------------------------------------------------
  WiFiConnect();
  WiFiConnect(String wifi_ssid, String wifi_password);

  // Accessors
  //-------------------------------------------------------
  String getWifiSSID();
  String getWifiPassword();

  void setWifiSSID(String ssid);
  void setWifiPassword(String password);

  // Member Methods
  //-------------------------------------------------------
  IPAddress ConnectToWifi(); 

  protected:
  // Properties
  //-----------------------------------------------------
    String wifi_ssid;
    String wifi_password;

};


#endif //ESP_8266_WIFI_CONNECT_H
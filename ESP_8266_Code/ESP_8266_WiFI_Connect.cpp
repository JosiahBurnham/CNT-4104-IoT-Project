//---------------------------------------------------------
// File       : ESP_8266_WiFi_Connect.cpp
// Author     : J.Burnham (11-11-2022)
// Purpose    : Implementation File WiFiConnect Class
//---------------------------------------------------------
#include "ESP_8266_WiFi_Connect.h"

// Constructor(s)
//-------------------------------------------------------

/**
* Defalut Constructor, creates an "empty" object
*/
WiFiConnect::WiFiConnect(){
  wifi_ssid = "";
  wifi_password = "";
}


/**
* Property Constructor for when the wifi_ssid and wifi_password is known
* at time of instantiation
*
* @param wifi_ssid - the ssid of the network to connect to
* @param wifi_password - the password to the network to connect to
*/
WiFiConnect::WiFiConnect(String wifi_ssid, String wifi_password){
  this->wifi_ssid = wifi_ssid;
  this->wifi_password = wifi_password;
}


// Accessors
//-------------------------------------------------------

String WiFiConnect::getWifiSSID(){ return wifi_ssid;}
String WiFiConnect::getWifiPassword(){return wifi_password;}

void WiFiConnect::setWifiSSID(String ssid){ wifi_ssid = ssid;}
void WiFiConnect::setWifiPassword(String password){wifi_password = password;}

// Member Methods
//-------------------------------------------------------

/**
* connect ESP 8266 to wifi with the passed in ssid and password
* @return - the local ip that the esp 8266 connected to
*/
IPAddress WiFiConnect::ConnectToWifi(){
  // Begin WiFi
  WiFi.begin(wifi_ssid, wifi_password);

  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  return WiFi.localIP();

}






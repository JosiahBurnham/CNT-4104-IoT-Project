#include "ESP_8266_Defs.h"
#include "ESP_8266_WiFi_Connect.h"
#include "ESP_8266_API_Interface.h"



APIInterface apiInterface = APIInterface(HOST, URL, API_KEY, FINGERPRINT); // only passing 3 parameters to API


void setup() {

  // Setup serial port
  Serial.begin(9600);

  // connect to WiFi
  WiFiConnect wifiClient = WiFiConnect(WIFI_SSID, WIFI_PASS);
  IPAddress response = wifiClient.ConnectToWifi();
  Serial.println(response); 
  

  // connect to the API
  String result = apiInterface.connectToHost();
  if (result == "Connection Failed"){ // end if the connection failed
    Serial.println("Connection Failed");
    return;
  }


}


void loop() {

  // the sensor data is coming from the arduino over serial
  if(Serial.available()){
    // the output of the sensors is already in the format for a GET request
    // hence we can just do a Serial.read()
    String str = Serial.readStringUntil('\n');
    Serial.println(str);
    String apiResponse = apiInterface.sendApiRequest( str); 
    Serial.println(apiResponse);
  }


}
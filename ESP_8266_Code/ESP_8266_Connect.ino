#include "ESP_8266_Defs.h"
#include "ESP_8266_WiFi_Connect.h"
#include "ESP_8266_API_Interface.h"



APIInterface apiInterface = APIInterface(HOST, URL, API_KEY, FINGERPRINT); // only passing 3 parameters to API
int api_request_count = 0;

void setup() {

  // Setup serial port
  // the software serial output of the arduino is connected to the
  // RX and TX of the ESP
  Serial.begin(115200);

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
  while(api_request_count < 1){ // this will only trigger once
    if(Serial.available()){
      // the output of the sensors is already in the format for a GET request
      // hence we can just do a Serial.read()
      String str = Serial.readStringUntil('\n');
      String apiResponse = apiInterface.sendApiRequest( str); 
      Serial.println(apiResponse);
      api_request_count++;
    }
  }


}
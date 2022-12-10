//---------------------------------------------------------
// File       : ESP_8266_API_Interface.cpp
// Author     : J.Burnham (11-12-2022)
// Purpose    : Implementation File APIInterface class
//---------------------------------------------------------
#include "ESP_8266_API_Interface.h"

// Constructor(s)
//-------------------------------------------------------

/**
* Default Constructor, creates an "empty" object
*/
APIInterface::APIInterface(){
  host = nullptr;
  url = "";
  apiKey = nullptr;
  fingerprint = nullptr;
}


/**
* Parameter constructor for when the host, url, api key, fingerprint, 
* and number of parameters to send to the api are know
*/
APIInterface::APIInterface(const char* host, String url, const char* apiKey, const char* fingerprint){
  this->host = host;
  this->url = url;
  this->apiKey = apiKey;
  this->fingerprint = fingerprint;
}


// Accessors
//------------------------------------------------------
const char* APIInterface::getHost(){return host;}
String APIInterface::getUrl(){return url;}
const char* APIInterface::getApiKey(){return apiKey;}
const char* APIInterface::getFingerprint(){return fingerprint;}

void APIInterface::setHost(const char* value){host = value;}
void APIInterface::setUrl(String value){url = value;}
void APIInterface::setApiKey(const char* value){apiKey = value;}
void APIInterface::getFingerprint(const char* value){fingerprint = value;}

// Member Methods
//-------------------------------------------------------

/***/
String APIInterface::connectToHost(){
  client.setFingerprint(fingerprint);

  if (!client.connect(host, HTTPS_PORT)){ // the port is 443
    return "Connection Failed";
  }
  return "Connected to HOST";

}



/**
* Send GET request to REST API hosted in AWS API Gateway
* @param parameters - the parameters to send in GET request (format obj1=val&obj2=val, etc)
*/
String APIInterface::sendApiRequest(String parameters){

    client.print(String("GET ") + url +
                "?" + parameters + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +
                "x-api-key: " + apiKey + "\r\n" +
                "User-Agent: 14 ESP8266\r\n" +
                "Connection: close\r\n\r\n");

    String line;
    while (client.connected()) {
      line = client.readStringUntil('\n');
    }

    return line;

}






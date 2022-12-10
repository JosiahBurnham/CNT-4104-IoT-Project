//---------------------------------------------------------
// File       : ESP_8266_API_Interface.h
// Author     : J.Burnham (11-12-2022)
// Purpose    : Definitions File APIInterface class
//---------------------------------------------------------
#include <WiFiClientSecure.h>

#include "ESP_8266_Defs.h"

#define HTTPS_PORT 443

class APIInterface {

  public:
  // Constructor(s)
  //-------------------------------------------------------
  APIInterface();
  APIInterface(const char* host, String url, const char* apiKey, const char* fingerprint);


  // Accessors
  //------------------------------------------------------
  const char* getHost();
  String getUrl();
  const char* getApiKey();
  const char* getFingerprint();

  void setHost(const char* value);
  void setUrl(String value);
  void setApiKey(const char* value);
  void getFingerprint(const char* value);

  // Member Methods
  //-------------------------------------------------------
  String connectToHost();
  String sendApiRequest(String parameters);


  protected:

  // Properties
  //-----------------------------------------------------
  const char* host;
  String url;
  const char* apiKey;
  const char* fingerprint;
  WiFiClientSecure client;
};

#include <DHT.h>
#include <Adafruit_seesaw.h>
#include <SoftwareSerial.h>

#include "IoT_Watering_Defs.h"



// GLOBAL VARS
Adafruit_seesaw ss;
SoftwareSerial ESPserial(2,3); // RX | TX
DHT dht(DHTPIN, DHTTYPE);

//Adafruit_seesaw ss;
int dht_count, soil_count, pump_count = 0;


void setup() {
  Serial.begin(115200);
  ESPserial.begin(115200);

  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT)

  // begin the sensors
  dht.begin();
  if (!ss.begin(0x36)) {
      Serial.println("ERROR! seesaw not found");
    while(1) delay(1);
  } else {
      Serial.print("seesaw started! version: ");
      Serial.println(ss.getVersion(), HEX);
  }
}


void loop() {
 float t = dht.readTemperature();
 float h = dht.readHumidity();
 uint16_t s = ss.touchRead(0);


 // Sensor data in the form of a GET request
 String str = "temperature=" + (String) t + "&humidity=" + (String) h + "&soilmoisture=" + (String) s;
 Serial.println(str);
 ESPserial.write(str);
 ESPserial.write('\n');
 delay(5000);

 String apiResponse = ESPserial.readString();

 if (apiResponse == "water"){
  digitalWrite(PUMP_PIN, HIGH);
  delay(8000);
  digitalWrite(PUMP_PIN, LOW);
 }
}

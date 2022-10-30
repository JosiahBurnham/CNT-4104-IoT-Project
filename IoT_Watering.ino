#include "DHT.h"
#include "Adafruit_seesaw.h"
#include "pitches.h"

#define DHTPIN 9 // the digital pin the DHT11 is connected to
#define DHTTYPE DHT11 // DHT11
#define PUMP_PIN 8
#define SPEAKER_PIN 10


// GLOBAL VARS
DHT dht(DHTPIN, DHTTYPE);
Adafruit_seesaw ss;
int dht_count, soil_count, pump_count = 0;

// notes in the song 'Mukkathe Penne'
// Video at https://www.youtube.com/watch?v=LgtcUxe8fmA, Arduino speaker song tutorial, by Akshay James
int melody[] = {
NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_A4,
NOTE_G4, NOTE_C5, NOTE_AS4, NOTE_A4,                   
NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_FS4, NOTE_DS4, NOTE_D4,
NOTE_C4, NOTE_D4,0,                                 

NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_A4,
NOTE_G4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_AS4, NOTE_A4,    
NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_FS4, NOTE_DS4, NOTE_D4,
NOTE_C4, NOTE_D4,0,                                       

NOTE_D4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_DS5, NOTE_D5,
NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_C5,
NOTE_C4, NOTE_D4, NOTE_DS4, NOTE_FS4, NOTE_D5, NOTE_C5,
NOTE_AS4, NOTE_A4, NOTE_C5, NOTE_AS4,      

NOTE_D4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_DS5, NOTE_D5,
NOTE_C5, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_C5, NOTE_G4,
NOTE_A4, 0, NOTE_AS4, NOTE_A4, 0, NOTE_G4,
NOTE_G4, NOTE_A4, NOTE_G4, NOTE_FS4, 0,

NOTE_C4, NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_DS4,
NOTE_C4, NOTE_D4, 0,
NOTE_C4, NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_DS4,
NOTE_C4, NOTE_D4, END

};

// note durations: 8 = quarter note, 4 = 8th note, etc.
// Video at https://www.youtube.com/watch?v=LgtcUxe8fmA, Arduino speaker song tutorial, by Akshay James
int noteDurations[] = {       //duration of the notes
8,4,8,4,
4,4,4,12,
4,4,4,4,4,4,
4,16,4,

8,4,8,4,
4,2,1,1,2,1,1,12,
4,4,4,4,4,4,
4,16,4,

4,4,4,4,4,4,
4,4,4,12,
4,4,4,4,4,4,
4,4,4,12,

4,4,4,4,4,4,
2,1,1,2,1,1,4,8,4,
2,6,4,2,6,4,
2,1,1,16,4,

4,8,4,4,4,
4,16,4,
4,8,4,4,4,
4,20,
};

int speed=90;  //higher value, slower notes


void setup() {
  Serial.begin(115200);

  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);

  dht.begin();
  ss.begin(0x36);

  for (int thisNote = 0; melody[thisNote]!=-1; thisNote++) {

    int noteDuration = speed*noteDurations[thisNote];
    tone(SPEAKER_PIN, melody[thisNote],noteDuration*.95);

    delay(noteDuration); 

    noTone(3);
  }


}



void loop() {

  while(dht_count < 1){ // read the DHT sensor once

    float h = dht.readHumidity(); // humidity
    float t = dht.readTemperature(true); // temperature

    if (isnan(h) || isnan(t)){
      Serial.println(F("failed to read from DHT sensor"));
      
    }
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F(" %, Temperature: "));
    Serial.print(t);
    Serial.print(F( " degrees F\n"));
    dht_count++;

  }// end DHT Sensor

  while(soil_count < 1) { // read soil sensor once
    uint16_t capread = ss.touchRead(0);

    if(isnan(capread)){
      Serial.print("failed to read form soil sensor");

    }else{
      Serial.print("Capacitive: "); Serial.println(capread);
      soil_count++;
    }
  }// end soil sensor



  while(pump_count < 3){
    digitalWrite(PUMP_PIN, HIGH);
    delay(1000);
    digitalWrite(PUMP_PIN, LOW);
    pump_count++;
  }// end pump

 
}


/*


int serial1 = 10;
int serial2 = 11;


SoftwareSerial mySoftwareSerial(serial1, serial2); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
//void printDetail(uint8_t type, int value);

void setup()
{
  pinMode(serial1, INPUT);
  pinMode(serial2, OUTPUT);

  mySoftwareSerial.begin(9600);
  //Serial.begin(115200);

  //Serial.println(F("Initializing DFPlayer ..."));

  if (!myDFPlayer.begin(mySoftwareSerial, true)) {
    //Serial.println(F("Unable to begin:"));
    //Serial.println(F("1.Please recheck the connection!"));
    //Serial.println(F("2.Please insert the SD card!"));
  }
  else
  {
    //Serial.println(F("DFPlayer Mini online."));
  }

  myDFPlayer.volume(25);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3
}

void loop()
{
  
}
*/
/*
int pinLED = 9;

 
void setup() {
  pinMode(pinLED, OUTPUT);
}
 
void loop() {  
    
   //ledRed
  for (int i = 0; i <= 255; i++) { //RED LED fade in
    analogWrite(pinLED, i);
    delay (75);
  }
  for (int i = 255; i >= 0; i--) {  //RED LED fade out
    analogWrite(pinLED, i);
    delay (50);
  }
 
}
*/
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

int infrared  = 8;

unsigned long duration, distance;
unsigned int pinLED = 9;
int serial1 = 10;
int serial2 = 11;
int cnt, state;
SoftwareSerial mySoftwareSerial(serial1, serial2);
DFRobotDFPlayerMini myDFPlayer;

void setup() {
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);
  myDFPlayer.begin(mySoftwareSerial, true);


  pinMode(serial1, INPUT);
  pinMode(serial2, OUTPUT);
  myDFPlayer.volume(24);  //Set volume value. From 0 to 30
}

void loop() {
  cnt = 0;
  for (int i =0; i<=20-1; i++){
    state = digitalRead(infrared);
    cnt = cnt + state;
    delay(45);
  }
  //Serial.println(cnt);

  if(cnt == 0){
    myDFPlayer.play(1);
    for (int i = 0; i <= 255; i++) { //RED LED fade in
      analogWrite(pinLED, i);
      delay (75);
      //Serial.println(myDFPlayer.readState());
    }
    delay(1000*32.5);
    delay(1000*32.5);
    delay(1000*32.5);
    delay(1000*32.5);
  }
  else
  {
    myDFPlayer.stop();
    analogWrite(pinLED, 0);
  }
}
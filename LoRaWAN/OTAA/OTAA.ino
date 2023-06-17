#include <MKRWAN.h>
#include "arduino_secrets.h"


LoRaModem modem;

String appEui = SECRET_APP_EUI;
String appKey = SECRET_APP_KEY;


uint8_t pl = 0x01;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  if (!modem.begin(KR920)) {
    digitalWrite(LED_BUILTIN, HIGH);
    while (1) {}
  };

  int connected = modem.joinOTAA(appEui, appKey);

  if (!connected) {
    digitalWrite(LED_BUILTIN, HIGH);
    while (1) {}
  }
}

void loop() 
{
  digitalWrite(LED_BUILTIN, HIGH);
  modem.beginPacket();
  int err = modem.write(pl);
  err = modem.endPacket(false);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  if(modem.available()) {
    pl = modem.read();
  }
  else{delay(2000);}
  
}

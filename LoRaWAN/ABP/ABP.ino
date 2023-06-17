#include <MKRWAN.h>


LoRaModem modem;

String devAddr = "01ee3e72";
String nwkSKey = "12fc7e87446e72cbd461e67457bd6e73";
String appSKey = "e1026147e0d611e201e108bc633b6967";


void setup() {
  if (!modem.begin(KR920)) {
    while (1) {}
  };

  int connected = modem.joinABP(devAddr, nwkSKey, appSKey);

  if (!connected) {
    while (1) {}
  }
}

void loop() 
{
  modem.beginPacket();
  int err = modem.write(0x01);
  err = modem.endPacket(false);
  delay(4*1000);
  
}

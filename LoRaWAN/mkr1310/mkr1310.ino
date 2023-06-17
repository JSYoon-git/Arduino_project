#include <MKRWAN.h>
#include "DHT.h"
#include "arduino_secrets.h"

#define DHTPIN 6
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

LoRaModem modem;

String appEui = SECRET_APP_EUI;
String appKey = SECRET_APP_KEY;

typedef union 
{
  struct
  {
    uint8_t humidity;
    uint8_t temperature;
    float heat_index;
  } buf;
  uint8_t pl[6];
} union_pl;

union_pl payload;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  dht.begin();
  
  if (!modem.begin(KR920)) {
    while (1) {}
  };

  int connected = modem.joinOTAA(appEui, appKey);

  if (!connected) {
    while (1) {}
  }
}

void loop() 
{
  uint8_t h = dht.readHumidity();
  uint8_t t = dht.readTemperature();
    
  float hic = dht.computeHeatIndex(t, h, false);

  payload.buf.humidity = h;
  payload.buf.temperature = t;
  payload.buf.heat_index = hic;
  
  digitalWrite(LED_BUILTIN, LOW);
  modem.beginPacket();
  int err = modem.write(payload.pl);
  err = modem.endPacket(false);
  delay(2*60*1000);
  
}

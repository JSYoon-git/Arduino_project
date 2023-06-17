#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     0

#include <MKRWAN.h>
#include <am1008w_k_i2c.h>
#include "SAMDTimerInterrupt.h"
#include "arduino_secrets.h"

#define LED_BUILTIN       13
#define TIMER0_INTERVAL_MS        15000

LoRaModem modem;
AM1008W_K_I2C am1008w_k_i2c;

String appEui = SECRET_APP_EUI;
String appKey = SECRET_APP_KEY;

typedef struct packet_s 
{ 
  uint16_t voc;          // 2byte
  uint16_t co2;          // 2byte
  uint16_t humidity;     // 2byte
  uint16_t temp;         // 2byte 
  uint8_t pm1p0;         // 1byte
  uint8_t pm2p5;         // 1byte
  uint8_t pm10;          // 1byte
  uint8_t now_r_ref_r;   // 1byte
  uint16_t ref_r;        // 2byte
  uint16_t now_r;        // 2byte
}Packet_s;  //16byte

typedef union packet_u 
{ 
  Packet_s ps;  
  uint8_t pl[16]; 
}Packet_u;

Packet_u packet_data;

SAMDTimer ITimer0(TIMER_TCC);

void TimerHandler0()
{
  digitalWrite(LED_BUILTIN, HIGH);
  uint8_t ret = am1008w_k_i2c.read_data_command();

  packet_data.ps.co2 = am1008w_k_i2c.get_co2();
  packet_data.ps.voc = am1008w_k_i2c.get_voc();
  packet_data.ps.humidity = uint16_t(am1008w_k_i2c.get_humidity()*100);
  packet_data.ps.temp = uint16_t(am1008w_k_i2c.get_temperature()*100);
  packet_data.ps.pm1p0 = am1008w_k_i2c.get_pm1p0();
  packet_data.ps.pm2p5 = am1008w_k_i2c.get_pm2p5();
  packet_data.ps.pm10 = am1008w_k_i2c.get_pm10();
  packet_data.ps.now_r_ref_r = am1008w_k_i2c.get_voc_now_r_ref_r();
  packet_data.ps.ref_r = am1008w_k_i2c.get_voc_ref_r();
  packet_data.ps.now_r = am1008w_k_i2c.get_voc_now_r();
  
  modem.beginPacket();
  int err = modem.write(packet_data.pl, sizeof(packet_data.pl));
  modem.endPacket(false);
  digitalWrite(LED_BUILTIN, LOW);
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  am1008w_k_i2c.begin();
  delay(1000);
  
  if (!modem.begin(KR920)) {
    while (1) {}
  };

  int connected = modem.joinOTAA(appEui, appKey);

  if (!connected) {
    while (1) {}
  }
  
  packet_data.ps.co2 = 0;
  packet_data.ps.voc = 0;
  packet_data.ps.humidity = 0;
  packet_data.ps.temp = 0;
  packet_data.ps.pm1p0 = 0;
  packet_data.ps.pm2p5 = 0;
  packet_data.ps.pm10 = 0;
  packet_data.ps.now_r_ref_r = 0;
  packet_data.ps.ref_r = 0;
  packet_data.ps.now_r = 0;

  ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler0);
}

void loop(){}

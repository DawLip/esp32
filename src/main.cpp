#include "data.h"
#include "main.h"
#include <EEPROM.h>
#include "Time.h"
/*
mode:
0 => configure WIFI_SSID mode
1 => work mode
2 => configure WIFI_PASSWORD mode
*/

int mode=-5;

// int mode = MODE_CONF_SSID;

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  // init outputs
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);

  const int freq = 5000;
  const int resolution = 8;
  ledcSetup(0, freq, resolution);
  ledcSetup(1, freq, resolution);
  ledcSetup(2, freq, resolution);

  ledcAttachPin(RGB_RED_PIN, 0);
  ledcAttachPin(RGB_GREEN_PIN, 1);
  ledcAttachPin(RGB_BLUE_PIN, 2);

  ledcWrite(0, 255);
  ledcWrite(1, 255);
  ledcWrite(2, 255);

  Serial.begin(9600);
  EEPROM.begin(40);
  WiFi.mode(WIFI_STA);

  delay(200);
  bool wifiConnected = wifi_init();
  Serial.println(wifiConnected?"WIFI CONNECTED":"WIFI NOT CONNECTED");
  if(wifiConnected)  {change_mode(MODE_WORK);}
  else{
    WiFi.disconnect();
    change_mode(MODE_CONF_SSID);
  }
  
  rfid_init();
  tft_init();
  time_sync();
}

void loop() {
  rfid_read();
  if(mode == MODE_WORK){
    update_time();
  }
  keybordRead();
  tft_update();
  // delay(1000);
}
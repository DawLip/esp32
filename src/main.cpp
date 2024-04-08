#include <Arduino.h>

// UTILS
#include "WIFI.h"
#include "TFT.h"
#include "RFID.h"

//SOC
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  Serial.begin(9600);

  delay(200);
  rfid_init();
  tft_init();
  wifi_init();

  myGLCD.fillScreen(TFT_BLACK);
  myGLCD.setTextColor(TFT_WHITE, TFT_BLACK);
  myGLCD.setTextSize(1);


  myGLCD.drawString("15:17", 64, 16, 6);
  myGLCD.drawString("Enter your PIN:", 40, 90, 4);

  for(int i=0; i<4; i++){
    myGLCD.drawRect(26+(i*(32+20)), 156, 32, 1, TFT_WHITE);
  }

  myGLCD.drawString("Sat  08/04/2024", 36, 200, 4);
}



void loop() {
  // Serial.print(rfid_read());
  

  delay(500);
}
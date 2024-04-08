#include "TFT.h"
#include "data.h"

TFT_eSPI myGLCD = TFT_eSPI();
String PIN = "";

void tft_init(){
  myGLCD.init();
  myGLCD.setRotation(2);

  myGLCD.fillScreen(TFT_BLACK);
  myGLCD.setTextColor(TFT_WHITE, TFT_BLACK);
  myGLCD.setTextSize(1);

  myGLCD.drawString("15:17", 64, 16, 6);
  myGLCD.drawString("Enter your PIN:", 40, 90, 4);

  tft_pin_update();
  
  myGLCD.setTextColor(TFT_GREY, TFT_BLACK);
  myGLCD.drawString("Sat  08/04/2024", 36, 200, 4);
  myGLCD.setTextColor(TFT_WHITE, TFT_BLACK);
}

void tft_pin_update(){
  myGLCD.fillRect(26, 136, 200, 32, TFT_BLACK);

  for(int i=0; i<4; i++){
    if(PIN.length()>i){
      myGLCD.setTextSize(2);
      myGLCD.drawString("*", 26+5+(i*(32+20)), 136, 4);
      myGLCD.setTextSize(1);
    }else{
      myGLCD.drawRect(26+(i*(32+20)), 166, 32, 1, TFT_WHITE);
    }
  }
}

#include "TFT.h"
#include "WIFI.h"
#include "data.h"

TFT_eSPI myGLCD = TFT_eSPI();
String PIN = "";
unsigned long tft_access_status_rst = millis();
unsigned long tft_time = millis();
int selectedWifi = 0;
/*
mode:
0 => configure WIFI_SSID mode
1 => work mode
2 => configure WIFI_PASSWORD mode
*/
int mode = 1;

void tft_init(){
  myGLCD.init();
  myGLCD.setRotation(2);

  myGLCD.fillScreen(TFT_BLACK);
  myGLCD.setTextColor(TFT_WHITE, TFT_BLACK);
  myGLCD.setTextSize(1);

  change_mode(0);
}

void change_mode(int newMode){
  mode = newMode;
  myGLCD.fillScreen(TFT_BLACK);
  switch (mode){
    case 0:
      break;
    case 1:
      myGLCD.drawString("Enter your PIN:", 40, 90, 4);
      tft_pin_update();
      break;
  }
}

void tft_mode2_update(unsigned long curr_time){
  myGLCD.drawString("Password:", 8, 8, 4);
  myGLCD.drawString(PIN+"    ", 8, 36, 4);

}

int currWifi=-100;
int n = -1;
void tft_mode0_update(unsigned long curr_time){
  if(currWifi==selectedWifi){return;}
  if(n==-1){n=WiFi.scanNetworks();}

  // myGLCD.fillScreen(TFT_BLACK);
  myGLCD.drawString("WiFi networks:", 8, 8, 4);

  if (n == 0) {
      myGLCD.drawString("Networks not found :(", 8, 8+28, 4);
  } else {
    for (int i = 0; i < n; ++i) {
      if(selectedWifi==i){
        myGLCD.setTextColor(TFT_RED, TFT_BLACK);
        myGLCD.drawString("=>", 16, 8+28+(18*i), 2);
        }else{
          myGLCD.drawString("  ", 16, 8+28+(18*i), 2);
        };

      myGLCD.drawString(WiFi.SSID(i)+" ("+WiFi.RSSI(i)+")", 16+20, 8+28+(18*i), 2);

      if(selectedWifi==i){myGLCD.setTextColor(TFT_WHITE, TFT_BLACK);};
    }
  }
  currWifi=selectedWifi;
}
/* 
accessStatus:
-2 => make reset
-1 => do nothing
 0 => display date
 1 => access denied
 2 => access granted
*/ 
void tft_mode1_update(unsigned long curr_time){
  // Time & date update
  if(tft_time < curr_time){
      if(accessStatus == 0){tft_date_update();}
      tft_time_update();
      tft_time += 30000;
  }

  // Access
  switch(accessStatus){
    case -2:
      tft_overlay(TFT_BLACK);
      tft_date_update();
      accessStatus = 0;
      break;
    case -1:
      if(tft_access_status_rst<curr_time) {accessStatus = -2;}
      break;
    case 0:
      break;
    case 1:
      tft_access_denied();
      break;
    case 2:
      tft_access_granted();
      break;
    
  }
}

void tft_update(){
  unsigned long curr_time = millis();

  switch (mode){
    case 0:
      tft_mode0_update(curr_time);
      break;
    case 1:
      tft_mode1_update(curr_time);
      break;
    case 2:
      tft_mode2_update(curr_time);
      break;
    }
}

String format_time() {
  String res;
  res += time_hour>9 ? String(time_hour) : '0' + String(time_hour);
  res += ':';
  res += time_min>9 ? String(time_min) : '0' + String(time_min);
  
  return res;
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

void tft_time_update(){
  myGLCD.drawString(format_time(), 64, 16, 6);
}

void tft_date_update(){
  myGLCD.setTextColor(TFT_GREY, TFT_BLACK);
  myGLCD.drawString("Sat  08/04/2024", 36, 200, 4);
  myGLCD.setTextColor(TFT_WHITE, TFT_BLACK);
}
void tft_overlay(uint16_t color){
  myGLCD.fillRect(0, 0, 240, 8, color);
  myGLCD.fillRect(0, 0, 8, 240, color);
  myGLCD.fillRect(232, 0, 8, 240, color);

  myGLCD.fillRect(0, 180, 240, 60, color);
}

void tft_access_denied(){
  tft_overlay(TFT_RED);

  myGLCD.setTextColor(TFT_WHITE);
  myGLCD.drawString("ACCESS DENIED", 22, 200, 4);
  myGLCD.setTextColor(TFT_WHITE, TFT_BLACK);

  accessStatus=-1;
  tft_access_status_rst = millis() + 2000;
}

void tft_access_granted(){
  tft_overlay(TFT_DARKGREEN);

  myGLCD.setTextColor(TFT_WHITE);
  myGLCD.drawString("ACCESS GRANTED", 8, 200, 4);
  myGLCD.setTextColor(TFT_WHITE, TFT_BLACK);

  accessStatus=-1;
  tft_access_status_rst = millis() + 2000;
}

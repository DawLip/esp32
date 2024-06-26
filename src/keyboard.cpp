#include "keyboard.h"
#include "TFT.h"
#include "WIFI.h"
#include "data.h"

bool is_keyboard_relased=true;

// 0-9 normal value, 10 - ok, 11 - cansel, -1 - none
int keyboard_analog_handle(int analog_input){
  if(analog_input<121) return -1;
  if(analog_input<391) return 9;
  if(analog_input<678) return 6;
  if(analog_input<988) return 3;
  if(analog_input<1333) return 10;
  if(analog_input<1711) return 0;
  if(analog_input<2103) return 2;
  if(analog_input<2462) return 5;
  if(analog_input<2783) return 8;
  if(analog_input<3091) return 7;
  if(analog_input<3509) return 4;
  if(analog_input<3931) return 1;
  return 11;
}

void keyboardMode0(int x){
  if (x == 8) {
    selectedWifi -= 1;
  }else if (x == 2) {
    selectedWifi += 1;
  } else if (x == 10) { 
    WIFI_SSID = WiFi.SSID(selectedWifi);
    save_auch_data();
    change_mode(2);
  }
}
void keyboardMode1(int x){
  if (x == 11) {
    PIN = "";
  } else if (x == 10) { 
    if (PIN.length() == 4){
      permission_request();
    } else {
      accessStatus=1;
      PIN="";
    }
  } else if(PIN.length()<4) {
    PIN += String(x);
  }
  tft_pin_update();
}

int prev_num = -1;
int num=-1;
String txt[] = {"0 ", "1","2aAbBcC","3dDeEfF","4gGhHiI", "5jJkKlL", "6mMnNoO", "7pPqQrRsS", "8tTuUvV", "9wWxXyYzZ"};
void keyboardMode2(int x){
  if (x == 11) {
    PIN.remove(PIN.length()-1);
  } else if (x == 10) { 
    WIFI_PASSWORD = PIN;
    save_auch_data();
    PIN = "";
    if(wifi_init()){
      change_mode(1);
    }else{
      change_mode(0);
    }
    
  } else {
    if(prev_num==x){
      num += 1;
      if(num==txt[prev_num].length()){num = 0;}
      PIN[PIN.length()-1] = txt[prev_num][num];
    }else{
      prev_num=x;
      num = 0;
      PIN += String(x);
    }
  }
}

void keybordRead(){
  int analog_read = analogRead(keyboard_pin);
  int x = keyboard_analog_handle(analog_read);
  if (x == -1) {
    is_keyboard_relased = true;
  } else if (is_keyboard_relased) {
    is_keyboard_relased = false;
    Serial.println(x);

    if(mode==1){keyboardMode1(x);}
    else if(mode==0){keyboardMode0(x);}
    else if(mode==2){keyboardMode2(x);}
  } 
}
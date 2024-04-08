#include <NTPClient.h>
#define keyboard_pin 12
#define keyboard_len 12

#include "data.h"
#include "main.h"

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  Serial.begin(9600);

  delay(200);
  rfid_init();
  tft_init();
  wifi_init();

}



void loop() {
  // Serial.print(rfid_read());
  tft_pin_update();

  delay(1000);
  PIN += "1";
}

int time_hour, time_min, time_sec;
unsigned long previousMillis;
void time_sync() {
  time_hour = timeClient.getHours();
  time_min = timeClient.getMinutes();
  time_sec = timeClient.getSeconds();
}
void update_time() {
  if ((unsigned long)(millis() - previousMillis) >= 1000){
    previousMillis = millis();

    bool is_time_to_sync = false;
    time_sec++;

    if(time_sec == 60){
      time_sec = 0;
      time_min++;
      if(time_min == 60){
        is_time_to_sync = true;
        time_min = 0;
        time_hour++;
        if(time_hour == 24){
          time_hour = 0;
        }
      }
    }
    if(is_time_to_sync){
      time_sync();
    }
  }
}
void setup_time(){
  timeClient.begin();
  timeClient.setTimeOffset(7200); // GMT +1 = 3600
  while(!timeClient.isTimeSet()){
    timeClient.update();
  }
  time_hour = timeClient.getHours();
  time_min = timeClient.getMinutes();
  time_sec = timeClient.getSeconds();
}

bool is_keyboard_relased = true;
String current_input = "";

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
void keybordRead(){
  int analog_read = analogRead(keyboard_pin);
  int x = keyboard_analog_handle(analog_read);
  if (x == -1) {
    is_keyboard_relased = true;
  } else if (is_keyboard_relased) {
    is_keyboard_relased = false;

    if (x == 11) {
      current_input = "";
    } else if (x == 10) { 
      // ADD HERE CODE CHECK 
      current_input = "";
    } else {
      current_input += String(x);
    }
  } 
}
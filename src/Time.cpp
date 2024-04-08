#include <WiFiUdp.h>
#include <NTPClient.h>

#include "Time.h"
#include "data.h"

int time_hour, time_min, time_sec;
unsigned long previousMillis;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

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

void time_init(){
  timeClient.begin();
  timeClient.setTimeOffset(7200); // GMT +1 = 3600
  while(!timeClient.isTimeSet()){
    timeClient.update();
  }
  time_hour = timeClient.getHours();
  time_min = timeClient.getMinutes();
  time_sec = timeClient.getSeconds();
}
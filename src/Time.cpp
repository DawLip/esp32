#include <WiFiUdp.h>
#include <NTPClient.h>

#include "Time.h"
#include "data.h"

int time_hour, time_min, time_sec,  time_day;
time_t time_epochTime;
unsigned long previousMillis;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

String format_date() {
  struct tm *ptm = gmtime ((time_t *)&time_epochTime); 
  int day = ptm->tm_mday;
  int month = ptm->tm_mon+1;
  int year = ptm->tm_year+1900;
  String weekDays[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"}, res;

  res += weekDays[time_day];
  res += "  ";
  res += day>9? String(day) : '0' + String(day);
  res += "/";
  res += month>9? String(month) : '0' + String(month);
  res += "/"  + String(year);

  return res;
}

void time_sync() {
  time_hour = timeClient.getHours();
  time_min = timeClient.getMinutes();
  time_sec = timeClient.getSeconds();
  time_day = timeClient.getDay();
  time_epochTime = timeClient.getEpochTime();
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
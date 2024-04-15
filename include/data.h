#ifndef DATA_H
#define DATA_H

#include <Arduino.h>

#define MODE_CONF_SSID 0
#define MODE_WORK 1
#define MODE_CONF_PASSWORD 2

extern String PIN;

extern int time_hour, time_min, time_sec;

extern unsigned long previousMillis;
extern bool is_keyboard_relased;
extern int accessStatus;

extern int mode;

#endif
#include <WiFi.h>
#include <EEPROM.h>
#include "Time.h"
#include "TFT.h"

extern String WIFI_SSID;
extern String WIFI_PASSWORD;

bool wifi_init();
void permission_request(bool isPIN);

void read_auch_data();
void save_auch_data();
#include <WiFi.h>

extern String WIFI_SSID;
extern String WIFI_PASSWORD;

void wifi_init();
void permission_request(bool isPIN);
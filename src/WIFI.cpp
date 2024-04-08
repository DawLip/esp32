#include "WIFI.h"
#include "data.h"

String WIFI_SSID     = "Ryb&Lip";
String WIFI_PASSWORD = "Kebabowo219";

int accessStatus=-1;

void wifi_init(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to WiFi ..");
  delay(100);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println(WiFi.localIP());

}
void _permission_request(bool isPIN){
  if(isPIN){
    if(PIN.length() != 4) {accessStatus=1; return;}

    accessStatus=2;
  }else{

  }
}

void permission_request(bool isPIN){
  _permission_request(isPIN);

  PIN="";
};
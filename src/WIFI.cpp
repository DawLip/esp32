#include "WIFI.h"
#include "data.h"

// String WIFI_SSID     = "Ryb&Lip";
// String WIFI_PASSWORD = "Kebabowo219";
String WIFI_SSID     = "";
String WIFI_PASSWORD = "";

int accessStatus=-1;

void read_auch_data(){
  WIFI_SSID = "";
  WIFI_PASSWORD = "";
  int x = 0;

  for(int i=0; i<20; i++){
    x = EEPROM.read(i);
    WIFI_SSID += x > 32 && x<135 ? (char)x : (char)' ';
  }
  for(int i=0; i<20; i++){
    x = EEPROM.read(20+i);
    WIFI_PASSWORD += x > 32 && x<135 ? (char)x : (char)' ';
  }
  WIFI_SSID.trim();
  WIFI_PASSWORD.trim();

  Serial.println("READED: <"+WIFI_SSID+"> <"+ WIFI_PASSWORD+">");
}

void save_auch_data(){
  Serial.println("SAVED: <"+WIFI_SSID+"> <"+ WIFI_PASSWORD+">");
  for(int i=0; i<20; i++){
    EEPROM.write(i, WIFI_SSID[i]);
  }
  for(int i=0; i<20; i++){
    EEPROM.write(20+i, WIFI_PASSWORD[i]);
  }
  EEPROM.commit();
}

bool wifi_init(){
  // save_auch_data();
  read_auch_data();
  // WIFI_SSID     = "";
  // WIFI_PASSWORD = "";
  Serial.println("WIFI credencials: <"+WIFI_SSID+"> <"+WIFI_PASSWORD+">");
  if(WIFI_SSID.length()==0) return false;

  try{

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting to WiFi ");
    delay(100);
    int i =0;
    while (WiFi.status() != WL_CONNECTED) {
      if(i>10){return false;}
      Serial.print('.');
      i++;
      delay(500);
    }
    Serial.println("\nConnected");
    delay(100);
    Serial.println(WiFi.localIP());
    time_init();
    // tft_update();
  }catch(...){
    Serial.print("WIFI login failed witch credencials: <"+WIFI_SSID+"> <"+WIFI_PASSWORD+">");
    return false;
  }
  return true;
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
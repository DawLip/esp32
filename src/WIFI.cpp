
#include "WIFI.h"
#include "data.h"
#include "main.h"
#include <HTTPClient.h>

// String WIFI_SSID     = "Galaxy A51 5G A34C";
// String WIFI_PASSWORD = "1234554321";
String WIFI_SSID     = "";
String WIFI_PASSWORD = "";

int accessStatus=-1;

WiFiClient client;
HTTPClient http;
// String serverName = "http://192.168.0.4:80";
String serverName = "http://192.168.0.129:80";

void setColor(int redValue, int greenValue,  int blueValue) {
  ledcWrite(0, 255-redValue);
  ledcWrite(1, 255-greenValue);
  ledcWrite(2, 255-blueValue);
}

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

bool req_check_code(String id) {
  String serverPath="";

  if (id.length()>0 && PIN.length()>0){serverPath = serverName + "/check-card-and-code?code="+PIN+"&card="+id+"&id=d1";}
  else if(PIN.length()>0)             {serverPath = serverName + "/check-code?code=" + PIN + "&id=d1";}
  else                                {serverPath = serverName + "/check-code?code=" + id  + "&id=d1";}
  Serial.println(serverPath);

  http.begin(serverPath.c_str());
  int httpResponseCode = http.GET();
  if(httpResponseCode == 200) {
      Serial.println("Access Granted");
      http.end();
      accessStatus=2;
      return true;
  } else if (httpResponseCode == 401) {
    Serial.println("Access Denied");
    http.end();
    accessStatus=1;
    return false;
  } else {
    Serial.println("Server connection error");
    http.end();
    accessStatus=1;
    return false;
  }     
}

void permission_request(String id){
  req_check_code(id);

  PIN="";
  tft_pin_update();
};
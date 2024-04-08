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
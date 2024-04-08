#include "data.h"
#include "main.h"

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  Serial.begin(9600);

  delay(200);

  wifi_init();
  time_init();
  rfid_init();
  tft_init();

}

void loop() {
  // Serial.print(rfid_read());
  update_time();
  keybordRead();
  tft_update();

  // delay(1000);
}
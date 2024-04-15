#ifndef TFT_H
#define TFT_H

#include <TFT_eSPI.h>

#define TFT_GREY 0x7BEF
extern TFT_eSPI myGLCD;
extern int selectedWifi;

void tft_init();
void tft_update();

void tft_pin_update();
void tft_time_update();
void tft_date_update();

void tft_access_granted();
void tft_access_denied();

void tft_overlay(uint16_t color);
void change_mode(int newMode);

#endif
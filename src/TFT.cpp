#include "TFT.h"

TFT_eSPI myGLCD = TFT_eSPI();

void tft_init(){
  myGLCD.init();
  myGLCD.setRotation(2);
}

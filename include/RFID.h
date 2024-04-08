#include <SPI.h>
#include <MFRC522.h>
#define RC522_SS_PIN  5 
#define RC522_RST_PIN 0 

extern MFRC522 rfid;

void rfid_init();
unsigned int rfid_read();
unsigned int rfid_getCardID();
#include "RFID.h"

MFRC522 rfid(RC522_SS_PIN, RC522_RST_PIN);

void rfid_init(){
  SPI.begin(); 
  rfid.PCD_Init();
}

unsigned int rfid_read(){
  if (!rfid.PICC_IsNewCardPresent()) {return 0;} // new tag is available
  if (!rfid.PICC_ReadCardSerial()) {return 1;} // NUID has been readed

  unsigned int id = rfid_getCardID();

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1(); 

  return id;
}

unsigned int rfid_getCardID() {
  unsigned int id;

  id =  rfid.uid.uidByte[0] << 24;
  id += rfid.uid.uidByte[1] << 16;
  id += rfid.uid.uidByte[2] <<  8;
  id += rfid.uid.uidByte[3];

  return id;
}
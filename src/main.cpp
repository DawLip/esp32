#include <Arduino.h>
// #include <WiFi.h>

// #include <Adafruit_GFX.h>    // Core graphics library
// // #include <Adafruit_I2CDevice.h>
// #include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
// #include <SPI.h>             // Arduino SPI library

// #define TFT_MOSI 23  // SDA Pin on ESP32
// #define TFT_SCLK 18  // SCL Pin on ESP32
// #define TFT_CS   -1  // Chip select control pin
// #define TFT_DC    5  // Data Command control pin
// #define TFT_RST   4  // Reset pin (could connect to RST pin)

// #define WIFI_SSID     "Ryb&Lip"
// #define WIFI_PASSWORD "Kebabowo219"

// Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
// float p = 3.1415926;

// void tftPrintTest() {
//   tft.setTextWrap(false);
//   tft.fillScreen(ST77XX_BLACK);
//   tft.setCursor(0, 30);
//   tft.setTextColor(ST77XX_RED);
//   tft.setTextSize(1);
//   tft.println("Hello World!");
//   tft.setTextColor(ST77XX_YELLOW);
//   tft.setTextSize(2);
//   tft.println("Hello World!");
//   tft.setTextColor(ST77XX_GREEN);
//   tft.setTextSize(3);
//   tft.println("Hello World!");
//   tft.setTextColor(ST77XX_BLUE);
//   tft.setTextSize(4);
//   tft.print(1234.567);
//   delay(1500);
//   tft.setCursor(0, 0);
//   tft.fillScreen(ST77XX_BLACK);
//   tft.setTextColor(ST77XX_WHITE);
//   tft.setTextSize(0);
//   tft.println("Hello World!");
//   tft.setTextSize(1);
//   tft.setTextColor(ST77XX_GREEN);
//   tft.print(p, 6);
//   tft.println(" Want pi?");
//   tft.println(" ");
//   tft.print(8675309, HEX); // print 8,675,309 out in HEX!
//   tft.println(" Print HEX!");
//   tft.println(" ");
//   tft.setTextColor(ST77XX_WHITE);
//   tft.println("Sketch has been");
//   tft.println("running for: ");
//   tft.setTextColor(ST77XX_MAGENTA);
//   tft.print(millis() / 1000);
//   tft.setTextColor(ST77XX_WHITE);
//   tft.print(" seconds.");
// }

// void setup() {
//   Serial.begin(9600);

//   // WiFi.mode(WIFI_STA);
//   // WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//   // Serial.print("Connecting to WiFi ..");
//   // while (WiFi.status() != WL_CONNECTED) {
//   //   Serial.print('.');
//   //   delay(1000);
//   // }
//   // Serial.println(WiFi.localIP());
//   tft.init(240, 240, SPI_MODE0);    // Init ST7789 display 135x240 pixel
//   tft.setRotation(2);
//   tft.fillScreen(ST77XX_BLACK);
// }

// void loop() {
//   tft.invertDisplay(true);
//   tftPrintTest();
//   delay(1000);
//   tft.invertDisplay(false);
//   tftPrintTest();
//   delay(1000);
// }

#include <Adafruit_GFX.h>   
#include <Adafruit_ST7789.h> 
// #define VSPI_MISO   MISO
// #define VSPI_MOSI   MOSI
// #define VSPI_SCLK   SCK
// #define VSPI_SS     SS

// #define HSPI_MISO   12
// #define HSPI_MOSI   13
// #define HSPI_SCLK   14
// #define HSPI_SS     15

#define TFT_DC    5   
#define TFT_RST   4   

#define TFT_DC_HSPI    26   
#define TFT_RST_HSPI   27 

#define TFT_CS    -1

#define RC522_SS  5
#define RC522_RST 0

SPIClass * vspi = NULL;
SPIClass * hspi = NULL;
Adafruit_ST7789 * tft = NULL;
Adafruit_ST7789 * tft1 = NULL;

void setup(void) {
  Serial.begin(9600);

  delay(100);
  vspi = new SPIClass(VSPI);
  hspi = new SPIClass(HSPI);

  vspi->begin();
  hspi->begin();

  tft = new Adafruit_ST7789(hspi ,TFT_CS, TFT_DC_HSPI,TFT_RST_HSPI);
  tft->init(240, 240, SPI_MODE3);  
  tft->setRotation(2);
  tft->fillScreen(ST77XX_BLACK);

  tft1 = new Adafruit_ST7789(vspi ,TFT_CS, TFT_DC, TFT_RST);
  tft1->init(240, 240, SPI_MODE3);  
  tft1->setRotation(2);
  tft1->fillScreen(ST77XX_BLACK);

}
 
void loop() {
  tft->invertDisplay(true);
  tft1->invertDisplay(true);
  delay(500);
  tft->invertDisplay(false);
  tft1->invertDisplay(false);
  delay(500);
}

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "MAX30100_PulseOximeter.h"
Adafruit_SSD1306 display(128, 64, &Wire, -1);
#define REPORTING_PERIOD_MS 1000
PulseOximeter pox; // I2C
 
uint32_t tsLastReport = 0;
 
const unsigned char bitmap [] PROGMEM=
{
0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x00, 0x0f, 0xe0, 0x7f, 0x00, 0x3f, 0xf9, 0xff, 0xc0,
0x7f, 0xf9, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xf0,
0xff, 0xf7, 0xff, 0xf0, 0xff, 0xe7, 0xff, 0xf0, 0xff, 0xe7, 0xff, 0xf0, 0x7f, 0xdb, 0xff, 0xe0,
0x7f, 0x9b, 0xff, 0xe0, 0x00, 0x3b, 0xc0, 0x00, 0x3f, 0xf9, 0x9f, 0xc0, 0x3f, 0xfd, 0xbf, 0xc0,
0x1f, 0xfd, 0xbf, 0x80, 0x0f, 0xfd, 0x7f, 0x00, 0x07, 0xfe, 0x7e, 0x00, 0x03, 0xfe, 0xfc, 0x00,
0x01, 0xff, 0xf8, 0x00, 0x00, 0xff, 0xf0, 0x00, 0x00, 0x7f, 0xe0, 0x00, 0x00, 0x3f, 0xc0, 0x00,
0x00, 0x0f, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void onBeatDetected()
{
  display.drawBitmap( 60, 20, bitmap, 28, 28, 1);
  display.display();
}
void setup()
{
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))  // I2C
  {
    for(;;);
  }
  display.display();
  delay(200); 
  display.clearDisplay();
  display.setTextSize(1);             
  display.setTextColor(WHITE);        
  display.setCursor(30,15);             
  display.println("Welcom to");
  display.setCursor(0,40);             
  display.println("      team 10");
  display.display();
  display.setTextSize(1);
  delay(2000);
  if (!pox.begin()) 
  {
      for(;;);
  }
  pox.setOnBeatDetectedCallback(onBeatDetected); 
}

void loop() 
{
   pox.update();
 
   if (millis() - tsLastReport > REPORTING_PERIOD_MS) 
   {
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(1);
        display.setCursor(0,16);
        display.println(pox.getHeartRate());
        
        display.setTextSize(1);
        display.setTextColor(1);
        display.setCursor(0, 0);
        display.println("Heart BPM");
        
        display.setTextSize(1);
        display.setTextColor(1);
        display.setCursor(0, 30);
        display.println("Spo2");
        
        display.setTextSize(1);
        display.setTextColor(1);
        display.setCursor(0,45);
        display.println(pox.getSpO2());
        display.display();
        tsLastReport = millis();
  }
}

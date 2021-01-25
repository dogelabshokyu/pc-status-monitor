#include <SPI.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DRGB_PIN        13 // NEOPIXEL Digital data pin
#define NUMPIXELS 20 // NEOPIXEL SIZE

Adafruit_NeoPixel pixels(NUMPIXELS, DRGB_PIN, NEO_GRB + NEO_KHZ800);

#define SCREEN_W 128 // OLED Display Width
#define SCREEN_H 32 // OLED Display Height
#define SCREEN_ADR 0x3C
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_W, SCREEN_H, &Wire, OLED_RESET);

String sig;
String cpu, cpu_clock, cpu_load, cpu_temp, mb, fan, pump;
char check[2];
void setup() {
  Serial.begin(9600);
  pixels.begin(); //neopixel start

  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADR); //oled display start
  display.clearDisplay();
}
/*
void loop() {
  pixels.clear(); // Set all pixel colors to 'off'
  display.clearDisplay();

  for(int i=0; i<255; i++)
  {
    for(int j=0; j<NUMPIXELS; j++)
    {
      pixels.setPixelColor(j, pixels.Color(0, 0, i));
      pixels.show();
    }
    oledprint(0, 0, String(i));
    delay(25);
  }
  for(int i=255; i>0; i--)
  {
    for(int j=0; j<NUMPIXELS; j++)
    {
      pixels.setPixelColor(j, pixels.Color(0, 0, i));
      pixels.show();
    }
    oledprint(0, 0, String(i));
    delay(25);
  }
  display.clearDisplay();
  delay(1000);
}
*/

void loop()
{
  while(Serial.available())
  {
    char wait = Serial.read();
    sig.concat(wait);
  }
  display.clearDisplay();
  oledprint(0, 0, sig);
  delay(1000);
}

void oledprint(int x, int y, String showprint)
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(x, y);
  display.setTextColor(WHITE);
  display.println(showprint);
  display.display();
  return;
}

void rgbctrl(int r, int g, int b, int pxlpos)
{
  pixels.setPixelColor(pxlpos, pixels.Color(r, g, b));
  pixels.show();
}

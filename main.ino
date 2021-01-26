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

char Ard1;
String sig, value1;
String cpu, cpu_clock, cpu_load, cpu_temp, mb, fan, pump;
char check[1];

int LED_BUILTIN = 14;

void setup() {
  Serial.begin(9600);
  pixels.begin(); //neopixel start

  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADR); //oled display start
  display.clearDisplay();
  pinMode(LED_BUILTIN,OUTPUT);
}

void loop()
{
  display.clearDisplay();
  oledprint(0, 0, Serial.readString());
}

void oledprint(int x, int y, String showprint)
{
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

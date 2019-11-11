#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip(8, GPIO_NUM_23, NEO_GRB + NEO_KHZ800);

uint8_t color = 0;

void setup() {
  pinMode(GPIO_NUM_2,OUTPUT);
  strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
  strip.show();  // Initialize all pixels to 'off'
}

void loop() {
  color++;
  strip.setPixelColor(1, strip.Color(100,100,100));
  strip.fill(strip.ColorHSV(color*256));
  strip.show();
  delay(100);
}
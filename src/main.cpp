#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Servo.h>

Adafruit_NeoPixel strip1(100, GPIO_NUM_22, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(100, GPIO_NUM_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3(100, GPIO_NUM_3, NEO_GRB + NEO_KHZ800);

uint8_t color = 0;

float servoPos = 0;
bool servoDir = false;

Servo servo1;

const int32_t color_inc = 1;
const float servo_inc = 0.2;

void setup() {
  strip1.begin(); // Initialize NeoPixel strip object (REQUIRED)
  strip2.begin();
  strip3.begin();
  strip1.show();  // Initialize all pixels to 'off'
  strip2.show();
  strip3.show();
  servo1.attach(GPIO_NUM_23);
}

uint32_t timer = xTaskGetTickCount();
void loop() {
  vTaskDelayUntil(&timer, 10);

  color += color_inc;
  strip1.fill(strip1.ColorHSV(color*256,255,100));
  strip2.fill(strip2.ColorHSV(color*256,255,100));
  strip3.fill(strip3.ColorHSV(color*256,255,100));
  delay(1);
  portDISABLE_INTERRUPTS();
  strip1.show();
  strip2.show();
  strip3.show();
  portENABLE_INTERRUPTS();

  if(servoDir){
    servoPos += servo_inc;
    if(servoPos >= 180){
      servoDir = false;
    }
  }else{
    servoPos -= servo_inc;
    if(servoPos <= 0){
      servoDir = true;
    }
  }

  servo1.write((int)servoPos);
}
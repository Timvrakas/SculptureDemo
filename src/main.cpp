#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Servo.h>

Adafruit_NeoPixel wing1(100, GPIO_NUM_22, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel wing2(100, GPIO_NUM_3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel body(100, GPIO_NUM_21, NEO_GRB + NEO_KHZ800);

uint16_t color = 0;

float servoPos = 0;
bool servoDir = false;

Servo servo1;

const uint16_t color_max = 65535;
const uint16_t color_inc = 50;
const float servo_inc = 0.1;

void setup() {
  wing1.begin(); // Initialize NeoPixel strip object (REQUIRED)
  wing2.begin();
  body.begin();
  wing1.show();  // Initialize all pixels to 'off'
  wing2.show();
  body.show();
  servo1.attach(GPIO_NUM_23);
}

uint32_t timer = xTaskGetTickCount();
void loop() {
  vTaskDelayUntil(&timer, 7);

  color += color_inc;
  wing1.fill(wing1.ColorHSV(color,255,100));
  wing2.fill(wing2.ColorHSV(color,255,100));
  body.fill(body.ColorHSV(color_max - color,255,100));
  delay(1);
  portDISABLE_INTERRUPTS();
  wing1.show();
  wing2.show();
  body.show();
  portENABLE_INTERRUPTS();

  if(servoDir){
    servoPos += servo_inc;
    if(servoPos >= 180){
      servoDir = false;
    }
  }else{
    servoPos -= servo_inc;
    if(servoPos <= 20){
      servoDir = true;
    }
  }

  servo1.write((int)servoPos);
}

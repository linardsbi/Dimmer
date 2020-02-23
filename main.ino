#include "src/helpers.hpp"

const uint8_t green = 3;           // the PWM pin the LED is attached to
const uint8_t red = 5;           // the PWM pin the LED is attached to
const uint8_t blue = 6;           // the PWM pin the LED is attached to
uint16_t brightness = 0;    // how bright the LED is
uint16_t fadeAmount = 5;    // how many points to fade the LED 

bool fade = false;
String inStr = "";
char colors[] = "000000000";

String handleSerial() {
  char rx_byte = Serial.read(); 
  String rx_str = "";
  
  while (rx_byte != '\n') {
    rx_str += rx_byte;
    rx_byte = Serial.read();
  } 

  return rx_str;
}

void doFade() {
  setBrightness(brightness, brightness, brightness);

  brightness = brightness + fadeAmount;
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  } 
}

void setBrightness(const uint8_t redVal, const uint8_t greenVal, const uint8_t blueVal) {
  analogWrite(red, redVal);
  analogWrite(green, blueVal);
  analogWrite(blue, greenVal);
}

void setBrightness(const char* brightness) {
  char redVal[4] = {0};
  char blueVal[4] = {0};
  char greenVal[4] = {0};
  Serial.println(brightness);
  
  memcpy(redVal, brightness + OFFSET_RED, LENGTH_VALUE);
  memcpy(greenVal, brightness + OFFSET_GREEN, LENGTH_VALUE);
  memcpy(blueVal, brightness + OFFSET_BLUE, LENGTH_VALUE);
  
  setBrightness(atoi(redVal), atoi(greenVal), atoi(blueVal));
}

void setup() {
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    inStr = handleSerial();
    
    if (inStr == "fade") {
      fade = !fade;
    } else {
      fade = false;
      
      memset(colors, '0', strlen(colors));
      parseColors(inStr.c_str(), colors);
      setBrightness(colors);
    }
  }
  
  if (fade) doFade();
  
  delay(30);
}

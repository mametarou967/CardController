//Control rotation angle  or speed and direction by sending pulse 
//Servo PIN 26

#define COUNT_LOW 1500
#define COUNT_HIGH 8500
#define TIMER_WIDTH 16
#include "esp32-hal-ledc.h"
#include <M5Stack.h>

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  ledcSetup(1, 50, TIMER_WIDTH);
  ledcAttachPin(26, 1);
  M5.Lcd.setCursor(20, 80, 2);
  M5.Lcd.print("SERVO");
  Serial.println("hello");
}

bool continuousMode = false;

void loop() {
  // put your main code here, to run repeatedly:
  // for(int i = COUNT_LOW; i < COUNT_HIGH; i = i + 100){  
  //   ledcWrite(1, i);
  //  delay(50);
  // }
  if (Serial.available()) {
    String text = Serial.readStringUntil(0x0d);
    if (text.length() > 0) {
      text.trim();
      // text.replace("*","");
      Serial.println(text);
      if(text[0] == '0')
      {
        continuousMode = false;
          ledcWrite(1, 0);
      }
      if(text[0] == '1')
      { 
          ledcWrite(1, 500);
          delay(10);
          ledcWrite(1, 0);
      }

      if(text[0] == '2')
      {
          ledcWrite(1, 1500);
          delay(63);
          ledcWrite(1, 0);
      }
      if(text[0] == '3')
      {
        continuousMode = true;
      }
      // = text
    }
  } 

  if(continuousMode)
  {
    ledcWrite(1, 1500);
    delay(63);
    ledcWrite(1, 0);
    ledcWrite(1, 1500);
    delay(63);
    ledcWrite(1, 0);
  }

  delay(100);
}
#include <M5Stack.h>
//Control rotation angle  or speed and direction by sending pulse 
//Servo PIN 26

int led1 = 26;

//PWMの設定
const double PWM_Hz = 50;   //PWM周波数
const uint8_t PWM_level = 16; //PWM 16bit(0～65535)

void setup() {
  Serial.begin(115200);
  m5.begin();
  pinMode(led1, OUTPUT);
  //モータのPWMのチャンネル、周波数の設定
  ledcSetup((uint8_t)1, PWM_Hz, PWM_level);

  //モータのピンとチャンネルの設定
  ledcAttachPin(led1, 1);
}

bool continuousMode = false;

void loop() {
  
  
  if (Serial.available()) {
    String text = Serial.readStringUntil(0x0d);
    if (text.length() > 0) {
      text.trim();
      // text.replace("*","");
      Serial.println(text);
      if(text[0] == '0')
      {
        continuousMode = false;
      }
      if(text[0] == '1')
      { 
        for (int i = 2300; i <= 9000; i=i+100) {
          ledcWrite(1, i);
          delay(30);
          Serial.printf("%d\n", i);
        }
      }

      if(text[0] == '2')
      {
        for (int i = 9000; i > 2300; i=i-100) {
          ledcWrite(1, i);
          delay(30);
          Serial.printf("%d\n", i);
        }
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
    for (int i = 2300; i <= 9000; i=i+100) {
      ledcWrite(1, i);
      delay(30);
      Serial.printf("%d\n", i);
    }
    for (int i = 9000; i > 2300; i=i-100) {
      ledcWrite(1, i);
      delay(30);
      Serial.printf("%d\n", i);
    }
  }

  delay(100);
}
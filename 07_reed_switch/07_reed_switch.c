/**************************************
 * 文件名: 07_reed_switch.c
 * 版本: 2.0
 * 作者: 何友表
 * 说明: 干簧管传感器实验，未检测到磁性物质时绿灯亮，检测到磁性物质时红灯亮
 *************************************/

#include <stdio.h>
#include <wiringPi.h>

typedef unsigned char uchar;
#define REED_SWITCH_SIG_PIN 0
#define RED_PIN 1
#define GREEN_PIN 2

int main() {
  if (wiringPiSetup() == -1) {
    printf("wiringPi Setup failed");
    return 1;
  }
  pinMode(REED_SWITCH_SIG_PIN, INPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  while (1) {
    if (0 == digitalRead(REED_SWITCH_SIG_PIN)) {
      delay(10);
      if (0 == digitalRead(REED_SWITCH_SIG_PIN)) {
        // 干簧管检测到磁性物质
        digitalWrite(RED_PIN, LOW);
        digitalWrite(GREEN_PIN, HIGH);
      }

    } else if (1 == digitalRead(REED_SWITCH_SIG_PIN)) {
      // 干簧管未检测到磁性物质
      delay(10);
      if (1 == digitalRead(REED_SWITCH_SIG_PIN)) {
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(GREEN_PIN, LOW);
      }
    }
  }
  return 0;
}
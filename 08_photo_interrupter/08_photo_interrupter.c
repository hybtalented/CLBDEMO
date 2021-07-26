/**************************************
 * 文件名 08_photo_interrupter.c
 * 版本 2.0
 * 作者 何友表
 * 说明 光电传感器实验，没有物体遮挡时绿灯亮，物体遮挡时红灯亮
 *************************************/

#include <stdio.h>
#include <wiringPi.h>

typedef unsigned char uchar;
#define PHOTO_INTERRUPTER_SIG_PIN 0
#define RED_PIN 1
#define GREEN_PIN 2

int main() {
  if (wiringPiSetup() == -1) {
    printf("wiringPi Setup failed");
    return 1;
  }
  pinMode(PHOTO_INTERRUPTER_SIG_PIN, INPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  while (1) {
    if (0 == digitalRead(PHOTO_INTERRUPTER_SIG_PIN)) {
      delay(10);
      if (0 == digitalRead(PHOTO_INTERRUPTER_SIG_PIN)) {
        // 光电传感器无物体遮挡
        digitalWrite(RED_PIN, LOW);
        digitalWrite(GREEN_PIN, HIGH);
      }

    } else if (1 == digitalRead(PHOTO_INTERRUPTER_SIG_PIN)) {
      delay(10);
      if (1 == digitalRead(PHOTO_INTERRUPTER_SIG_PIN)) {
        // 光电传感器有物体遮挡
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(GREEN_PIN, LOW);
      }
    }
  }
  return 0;
}
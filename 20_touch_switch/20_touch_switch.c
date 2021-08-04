/**************************************
 * 文件名: 20_touch_switch.c
 * 版本: 1.0
 * 作者: 何友表
 * 说明: 触摸开关传感器实验， 触摸发生时输入高电平,
 * 否者输入低电平
 *************************************/
#include <stdio.h>
#include <wiringPi.h>
typedef unsigned char uchar;
#define TOUCH_SIG_PIN 0
#define RED_PIN 1
#define GREEN_PIN 2

int main() {
  int state = -1, tmp;
  if (wiringPiSetup() == -1) {
    printf("wiringPi Setup failed");
    return 1;
  }
  pinMode(TOUCH_SIG_PIN, INPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  while (1) {
    tmp = digitalRead(TOUCH_SIG_PIN);
    delay(10);
    if (tmp == digitalRead(TOUCH_SIG_PIN)) {
      if (tmp != state) {
        state = tmp;
        switch (state) {
        case 0:
          // 没有触摸发生
          printf("\n***********************\n");
          printf("未检测到触摸");
          printf("\n***********************\n");
          digitalWrite(RED_PIN, LOW);
          digitalWrite(GREEN_PIN, HIGH);
          break;
        case 1:
          // 发生触摸
          printf("\n***********************\n");
          printf("检测到触摸");
          printf("\n***********************\n");
          digitalWrite(RED_PIN, HIGH);
          digitalWrite(GREEN_PIN, LOW);
          break;
        default:
          printf("\n***********************\n");
          printf("错误的触摸状态 %d", state);
          printf("\n***********************\n");
        }
      }
    }
  }
  return 0;
}
/**************************************
 * 文件名: 15_sound_sensor.c
 * 版本: 1.0
 * 作者: 何友表
 * 说明: 光敏传感器使用，检测光线强度,输出越小
 * 说明关线强度越强
 *************************************/
#include <pcf8591.h>
#include <stdio.h>
#include <wiringPi.h>
#define PCF_PIN 120

int main() {
  int photo_value;
  if (wiringPiSetup() == -1) {
    printf("wiringPi Setup failed");
    return 1;
  }
  if (pcf8591Setup(PCF_PIN, 0x48) == -1) {
    printf("wiringPi pcf8591 Setup PIN %d failed", PCF_PIN);
    return 1;
  }
  while (1) {
    photo_value = analogRead(PCF_PIN + 0);

    printf("当前光线强度: %d\n", photo_value);

    delay(200);
  }
  return 0;
}
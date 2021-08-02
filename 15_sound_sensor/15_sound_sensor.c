/**************************************
 * 文件名: 15_sound_sensor.c
 * 版本: 1.0
 * 作者: 何友表
 * 说明: 声音传感器使用，检测噪声强度
 *************************************/
#include <pcf8591.h>
#include <stdio.h>
#include <wiringPi.h>
#define PCF_PIN 120

int main() {
  int sound_value;
  if (wiringPiSetup() == -1) {
    printf("wiringPi Setup failed");
    return 1;
  }
  if (pcf8591Setup(PCF_PIN, 0x48) == -1) {
    printf("wiringPi pcf8591 Setup PIN %d failed", PCF_PIN);
    return 1;
  }
  while (1) {
    sound_value = analogRead(PCF_PIN + 0);

    printf("当前声音强度: %d\n", sound_value);
    if (sound_value < 80) {
      printf("声音输入\n");
    }
    delay(200);
  }
  return 0;
}
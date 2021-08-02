/**************************************
 * 文件名: 15_sound_sensor.c
 * 版本: 1.0
 * 作者: 何友表
 * 说明: 火焰传感器实验，有火焰或或者强光照射时
 * 显示低电平，否者为高电平
 *************************************/
#include <pcf8591.h>
#include <stdio.h>
#include <wiringPi.h>
#define PCF_PIN 120
#define FLAME_DO_PIN 0

int main() {
  int flame_value;
  int status = -1, tmp;
  if (wiringPiSetup() == -1) {
    printf("wiringPi Setup failed");
    return 1;
  }
  if (pcf8591Setup(PCF_PIN, 0x48) == -1) {
    printf("wiringPi pcf8591 Setup PIN %d failed", PCF_PIN);
    return 1;
  }
  pinMode(FLAME_DO_PIN, INPUT);
  while (1) {
    flame_value = analogRead(PCF_PIN + 0);
    tmp = digitalRead(FLAME_DO_PIN);
    printf("当前红外光强度: %d\n", flame_value);

    if (tmp != status) {
      status = tmp;
      switch (status) {
      case 0:
        printf("\n***********************\n");
        printf("有火焰");
        printf("\n***********************\n");
        break;
      case 1:
        printf("\n***********************\n");
        printf("安全");
        printf("\n***********************\n");
        break;
      default:
        printf("\n***********************\n");
        printf("状态异常");
        printf("\n***********************\n");
        break;
      }
    }
    delay(200);
  }
  return 0;
}
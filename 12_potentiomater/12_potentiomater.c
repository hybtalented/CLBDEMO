/**************************************
 * 文件名: 12_potentiomater.c
 * 版本: 1.0
 * 作者: 何友表
 * 说明: PS2 电位器实验，读取电位器的值
 *************************************/
#include <pcf8591.h>
#include <stdio.h>
#include <wiringPi.h>

#define PCF_PIN 120

int main() {
  int value;
  if (wiringPiSetup() == -1) {
    printf("wiringPi Setup failed");
    return 1;
  }
  if (pcf8591Setup(PCF_PIN, 0x48) == -1) {
    printf("wiringPi pcf8591 Setup PIN %d failed", PCF_PIN);
    return 1;
  }
  while (1) {
    value = analogRead((PCF_PIN + 0));
    printf("电位器电压 %f V\n", value / 255.0 * 5);
    delay(200);
  }
  return 0;
}
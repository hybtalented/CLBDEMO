/**************************************
 * 文件名: 14_thermistor.c
 * 版本: 1.0
 * 作者: 何友表
 * 说明: 模拟温度传感器实验
 *************************************/

#include <math.h>
#include <pcf8591.h>
#include <stdio.h>
#include <wiringPi.h>
#define PCF_PIN 120
#define THERMISTOR_DIGITAL_PIN 0

int main() {
  int value;
  double Tvr, Trt, T;
  if (wiringPiSetup() == -1) {
    printf("wiringPi Setup failed");
    return 1;
  }
  if (pcf8591Setup(PCF_PIN, 0x48) == -1) {
    printf("wiringPi pcf8591 Setup PIN %d failed", PCF_PIN);
    return 1;
  }
  pinMode(THERMISTOR_DIGITAL_PIN, INPUT);
  while (1) {
    value = analogRead(PCF_PIN + 0);
    Tvr = value / 255.0;
    T = 1 / (-log(1 / Tvr - 1) / 3950 + 1 / (273.15 + 25));
    T = T - 273.15;
    printf("当前温度为 %lf 摄氏度\n", T);
    delay(200);
  }
  return 0;
}
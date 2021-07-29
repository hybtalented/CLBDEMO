/**************************************
 * 文件名 09_pcf8591.c
 * 版本 1.0
 * 作者 何友表
 * 说明 A/D转换实验，通过创博乐pcf8591模块上
 * 的电位器控制LED红灯的亮度，并且读取打印出
 * 光敏电阻和热敏电阻的值
 *************************************/
#include <pcf8591.h>
#include <stdio.h>
#include <wiringPi.h>

#define PCF_PIN 120

int main() {
  int pot_value, photo_value, ntc_value;
  if (wiringPiSetup() == -1) {
    printf("wiringPi Setup failed");
    return 1;
  }
  if (pcf8591Setup(PCF_PIN, 0x48) == -1) {
    printf("wiringPi pcf8591 Setup PIN %d failed", PCF_PIN);
    return 1;
  }
  while (1) {
    // 读取 AIN0 上的值，插上跳线帽以后实际上采用的是内部的电位器
    pot_value = analogRead(PCF_PIN + 0);
    // 读取 AIN1 上的值，插上跳线帽以后实际上采用的是光敏电阻
    photo_value = analogRead(PCF_PIN + 1);
    // 读取 AIN2 上的值，插上跳线帽以后实际上采用的是热敏电阻
    ntc_value = analogRead(PCF_PIN + 2);
    printf("pcf POT value is %d\n    photo value is %d\n    ntc value is %d\n",
           pot_value, photo_value, ntc_value);
    // AOUT 模拟输出控制LED灯
    analogWrite(PCF_PIN + 0, pot_value);
    delay(1000);
  }
  return 0;
}
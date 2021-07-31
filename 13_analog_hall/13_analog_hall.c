/**************************************
 * 文件名: 13_analog_hall.c
 * 版本: 1.0
 * 作者: 何友表
 * 说明: 模拟霍尔传感器实验
 *************************************/
#include <pcf8591.h>
#include <stdio.h>
#include <wiringPi.h>

#define PCF_PIN 120
const char *direction_str[] = {"无磁场", "北", "南"};
int main() {
  int value, direction = -1, tmp;
  if (wiringPiSetup() == -1) {
    printf("wiringPi Setup failed");
    return 1;
  }
  if (pcf8591Setup(PCF_PIN, 0x48) == -1) {
    printf("wiringPi pcf8591 Setup PIN %d failed", PCF_PIN);
    return 1;
  }
  while (1) {
    value = analogRead(PCF_PIN + 0);
    if (value < 128) {
      tmp = 1;
    } else if (value > 138) {
      tmp = 2;
    } else {
      tmp = 0;
    }
    if (tmp != direction) {
      direction = tmp;
      printf("\n***********************\n");
      printf("磁场方向改变: %s", direction_str[direction]);
      printf("\n***********************\n");
    }
    printf("当前磁场值 %d\n", value);
    delay(200);
  }
  return 0;
}
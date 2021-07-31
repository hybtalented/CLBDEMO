/**************************************
 * 文件名: 10_rain_detector.c
 * 版本: 1.0
 * 作者: 何友表
 * 说明: 雨滴传感器实验，传感器上有水时低电平，没有水时为高电平
 *************************************/
#include <pcf8591.h>
#include <stdio.h>
#include <wiringPi.h>

#define PCF_PIN 120
#define DETECTOR_OD_PIN 0
int main() {
  int detector_value, detector_status, tmp_status;
  if (wiringPiSetup() == -1) {
    printf("wiringPi Setup failed");
    return 1;
  }
  if (pcf8591Setup(PCF_PIN, 0x48) == -1) {
    printf("wiringPi pcf8591 Setup PIN %d failed", PCF_PIN);
    return 1;
  }

  pinMode(DETECTOR_OD_PIN, INPUT);
  while (1) {
    // 读取 AIN0 上雨滴传感器的值
    detector_value = analogRead(PCF_PIN + 0);
    // 读取雨滴传感器状态
    tmp_status = digitalRead(DETECTOR_OD_PIN);
    // 读取 AIN2 上的值，插上跳线帽以后实际上采用的是热敏电阻
    printf("rain detector value is %d\n", detector_value);
    if (detector_status != tmp_status) {
      switch (tmp_status) {
      case 1:
        printf("\n***********************\n");
        printf("未下雨");
        printf("\n***********************\n");
        break;
      case 0:
        printf("\n***********************\n");
        printf("正在下雨");
        printf("\n***********************\n");
        break;
      default:
        printf("\n***********************\n");
        printf("错误状态");
        printf("\n***********************\n");
        break;
      }
      detector_status = tmp_status;
    }
    delay(200);
  }
  return 0;
}
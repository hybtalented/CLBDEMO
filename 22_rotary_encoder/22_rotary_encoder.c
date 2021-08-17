/**************************************
 * 文件名: 22_rotary_encoder.c
 * 版本: 1.0
 * 作者: 何友表
 * 说明: 旋转编码器实验，顺时针方向旋转时计数器减，
 * 逆时针旋转时计数器加，按下编码器是重置计数器
 *************************************/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>

#define CLK_PIN 1
#define DT_PIN 2
#define SW_PIN 6  // GPIO 0 在连接MAKE ROBOT 主板后作为输入管脚有点问题
static volatile int globalCounter = 0;

unsigned char flag;              // 是否发生旋转标志位
unsigned char Last_DT_Status;    // DT 状态
unsigned char Current_DT_Status; // CLK 为状态
// 中断函数，当SW管脚为0时，使能中断
void btnISR() { globalCounter = 0;  printf("sw pressed \n"); }
// 方向判断函数
void rotaryDeal() {
  Last_DT_Status = digitalRead(DT_PIN);
  while (!digitalRead(CLK_PIN)) { // 判断CLK管脚的电平变化来区分方向
    Current_DT_Status = digitalRead(DT_PIN);
    flag = 1; // 标记位，用于判断是否未检测到 DT 状态发生改变
  }

  if (flag == 1) {
    if ((Last_DT_Status == 0) && (Current_DT_Status == 1)) { // 逆时针方向旋转
      globalCounter++;
      flag = 0;
    }
    if ((Last_DT_Status == 1) && (Current_DT_Status == 0)) { // 顺时针方向旋转
      globalCounter--;
      flag = 0;
    }
  }
}
int main() {
  if (wiringPiSetup() == -1) {
    fprintf(stderr, "wiringPi Setup failed:%s", strerror(errno));
    return 1;
  }
  pinMode(SW_PIN, INPUT);
  pinMode(DT_PIN, INPUT);
  pinMode(CLK_PIN, INPUT);
  pullUpDnControl(SW_PIN, PUD_UP); // 设置 SWPin 管脚为上拉模式
  if (wiringPiISR(SW_PIN, INT_EDGE_FALLING, &btnISR) < 0) {
    // 初始化中断函数，当SW管脚为0，使能中断
    fprintf(stderr, "Unable to init ISR\n");
    return 1;
  }
  int tmp = -1;
  while (1) {
    rotaryDeal(); // 调用方向判断函数
    if (tmp != globalCounter) {
      printf("current value is %d\n", globalCounter);
      tmp = globalCounter;
    }
  }
  return 0;
}
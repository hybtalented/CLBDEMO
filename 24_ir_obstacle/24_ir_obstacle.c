/**************************************
 * 文件名: 24_ir_obstacle.c
 * 版本: 1.0
 * 作者: 何友表
 * 说明: 红外壁障传感器实验
 *************************************/
#include <errno.h>
#include <stdio.h>
#include <wiringPi.h>

#define Obstacle_PIN 2

int dht11_dat[5] = {0, 0, 0, 0, 0};
void Obstacle_ISR(void) { printf("detected barrier !\n"); }
int main() {
  printf("barrier detect test program\n");
  if (wiringPiSetup() == -1) {
    fprintf(stderr, "wiringPi Setup failed:%s", strerror(errno));
    return 1;
  }
  if (wiringPiISR(Obstacle_PIN, INT_EDGE_FALLING, Obstacle_ISR) < 0) {
    printf("Ubable to set ISR for Obstacle: %s", strerror(errno));
    return 1;
  }
  pinMode(Obstacle_PIN, INPUT);
  while (1) {
    delay(100);
  }
  return 0;
}
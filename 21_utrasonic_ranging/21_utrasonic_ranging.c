/**************************************
 * 文件名: 21_utrasonic_ranging.c
 * 版本: 1.0
 * 作者: 何友表
 * 说明: 超声波传感器，使用超声波进行测距
 *************************************/
#include <stdio.h>
#include <sys/time.h>
#include <wiringPi.h>
typedef unsigned char uchar;
#define TRIG_SIG_PIN 0
#define ECHO_SIG_PIN 1
float measureDistance() {
  struct timeval ur_tv1, ur_tv2; // 定义起始和终止的时间结构体
  float ur_time1, ur_time2;
  float distance;
  digitalWrite(TRIG_SIG_PIN, LOW); // 起始信号
  delayMicroseconds(2);
  digitalWrite(TRIG_SIG_PIN, HIGH); // 超声波启动信号
  delayMicroseconds(10);
  digitalWrite(TRIG_SIG_PIN, LOW); // 设置为低电平
  while (!(digitalRead(ECHO_SIG_PIN) == 1))
    ; // 等待回传信号
  gettimeofday(&ur_tv1, NULL);
  while (!(digitalRead(ECHO_SIG_PIN) == 0))
    ;
  gettimeofday(&ur_tv2, NULL);
  ur_time1 = ur_tv1.tv_sec * 1000000 + ur_tv1.tv_usec;
  ur_time2 = ur_tv2.tv_sec * 1000000 + ur_tv2.tv_usec; // 计算微秒级别的时间
  distance = (ur_time2 - ur_time1) / 1000000.0 * 34000 / 2;
  return distance;
}
int main() {
  float distance = -1;
  if (wiringPiSetup() == -1) {
    printf("wiringPi Setup failed");
    return 1;
  }
  pinMode(ECHO_SIG_PIN, INPUT);
  pinMode(TRIG_SIG_PIN, OUTPUT);
  while (1) {
    distance = measureDistance();
    printf("distance is %0.2f cm\n", distance);
    delay(300);
  }
  return 0;
}
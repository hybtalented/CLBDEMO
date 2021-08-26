/**************************************
 * 文件名: 26_barometer.c
 * 版本: 1.0
 * 作者: 何友表
 * 说明: BMP180 气压传感器实验
 *************************************/
#include "bmp180.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#define LCDAddr 0x27

int main() {
  const char *i2c_device = "/dev/i2c-1"; // 总线类型
  int address = 0x77;
  void *bmp = bmp180_init(address, i2c_device);
  if (bmp != NULL) {
    int i;
    for (i = 0; i < 100; ++i) {
      float t = bmp180_temperature(bmp);
      long p = bmp180_pressure(bmp);
      float alt = bmp180_altitude(bmp);
      printf("temperature = %.2f, pressure = %1u, altitude = %.2f\n", t, p,
             alt);
      usleep(2 * 1000 * 1000); // 延时 2 s
    }
  }
}
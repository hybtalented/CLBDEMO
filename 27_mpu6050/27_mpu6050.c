/**************************************
 * 文件名: 27_mpu6050.c
 * 版本: 2.0
 * 作者: 何友表
 * 说明: MPU 6050 陀螺仪加速度传感器实验，
 * 测量加速度和角速度
 *************************************/
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#define MPU6050_ADDR 0x68
// MPU6050 寄存器地址
#define PWR_MGMT_1 0x6B
#define SMPLRT_DIV 0x19
#define CONFIG 0x1A
#define GYRO_CONFIG 0x1B
#define INT_ENABLE 0x38
#define ACCEL_XOUT_H 0x3B
#define ACCEL_YOUT_H 0x3D
#define ACCEL_ZOUT_H 0x3F
#define GYRO_XOUT_H 0x43
#define GYRO_YOUT_H 0x45
#define GYRO_ZOUT_H 0x47

int fd;
void MPU6050Init() {
  wiringPiI2CWriteReg8(fd, SMPLRT_DIV, 0x07); // 写入抽样速度
  wiringPiI2CWriteReg8(fd, PWR_MGMT_1, 0x01); // 写入电源管理
  wiringPiI2CWriteReg8(fd, CONFIG, 0);        // 写入配置寄存器
  wiringPiI2CWriteReg8(fd, GYRO_CONFIG, 24);  // 写入陀螺仪配置寄存器
  wiringPiI2CWriteReg8(fd, INT_ENABLE, 0x01); // 写入中断使能寄存器
}

short read_raw_data(int addr) {
  short high_byte, low_byte, value;
  high_byte = wiringPiI2CReadReg8(fd, addr);
  low_byte = wiringPiI2CReadReg8(fd, addr + 1);
  value = (high_byte << 8) | low_byte;
  return value;
}
// 延时函数
void ms_delay(int microsecond) {
  int i, j;
  for (i = 0; i <= microsecond; i++)
    for (j = 0; j < 1200; j++)
      ;
}
int main() {
  float Acc_x, Acc_y, Acc_z, Gyro_x, Gyro_y, Gyro_z, Ax = 0, Ay = 0, Az = 0,
                                                     Gx = 0, Gy = 0, Gz = 0;
  fd = wiringPiI2CSetup(MPU6050_ADDR);
  MPU6050Init();
  while (1) {
    Acc_x = read_raw_data(ACCEL_XOUT_H);
    Acc_y = read_raw_data(ACCEL_YOUT_H);
    Acc_z = read_raw_data(ACCEL_ZOUT_H);
    Gyro_x = read_raw_data(GYRO_XOUT_H);
    Gyro_y = read_raw_data(GYRO_YOUT_H);
    Gyro_z = read_raw_data(GYRO_ZOUT_H);
    // 原始值除以灵敏度因子
    Ax = Acc_x / 16384.0;
    Ay = Acc_y / 16384.0;
    Az = Acc_z / 16384.0;
    Gx = Gyro_x / 131.0;
    Gy = Gyro_y / 131.0;
    Gz = Gyro_z / 131.0;
    // 打印陀螺仪加速器数据
    printf("\n Gx=%.3f */s\tGy=%.3f * /s\tGz=%.3f * /s\tAx=%.3f g\t Ay=%.3f "
           "g\tAz=%.3f g\n",
           Gx, Gy, Gz, Ax, Ay, Az);
    delay(500);
  }
  return 0;
}
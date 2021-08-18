/**************************************
 * 文件名: 25_i2c_lcd1602.c
 * 版本: 1.0
 * 作者: 何友表
 * 说明: lCD 液晶显示屏实验
 *************************************/
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#define LCDAddr 0x27

int BLEN = 1;
int fd;
// LCD 液晶模块写入字
void write_word(int data) {
  int temp = data;
  if (BLEN == 1) {
    temp |= 0x08;
  } else {
    temp |= 0xF7;
  }
  wiringPiI2CWrite(fd, temp); // 设置IIC LCD1602 液晶模块地址
}
// LCD 发送命令
void send_command(int comm) {
  int lcd_buf;
  lcd_buf = comm & 0xF0;
  lcd_buf |= 0x04; // RS = 0. RW = 0, EN =1;
  write_word(lcd_buf);
  delay(2);
  lcd_buf &= 0xFB; // 使 EN = 0
  write_word(lcd_buf);
  lcd_buf = (comm & 0x0F) << 4;
  lcd_buf |= 0x04; // RS = 0, RW = 0, EN = 1
  write_word(lcd_buf);
  delay(2);
  lcd_buf &= 0xFB;
  write_word(lcd_buf);
}
// IIC LCD1602 发送数据
void send_data(int data) {
  int lcd_buf;
  // 首先发送 7-4 位
  lcd_buf = data & 0xF0;
  lcd_buf |= 0x05; // RS = 1, RW = 0, EN = 1
  write_word(lcd_buf);
  delay(2);
  lcd_buf &= 0xFB; // 使 EN = 0
  write_word(lcd_buf);
  // 其次发送3-0 位

  lcd_buf = (data & 0x0F) << 4;
  lcd_buf |= 0x05; // RS = 1, RW = 0, EN = 1
  write_word(lcd_buf);
  delay(2);
  lcd_buf &= 0xFB;
  write_word(lcd_buf);
}
void init() {
  send_command(0x33); // 初始化为8线模式
  delay(5);
  send_command(0x32); // 初始化为4行模式
  delay(5);
  send_command(0x28); // 2 行 & 5 * 7 个点位
  delay(5);
  send_command(0x0C); // 启用无光标显示
  delay(5);
  send_command(0x01); // 清除显示
  wiringPiI2CWrite(fd, 0x08);
}
void clear() { send_command(0x01); }
void write(int lcd_x, int lcd_y, char data[]) {
  int lcd_addr, lcd_i;
  int lcd_tmp;
  // 选择行和列
  if (lcd_x < 0)
    lcd_x = 0;
  if (lcd_x > 15)
    lcd_x = 15;
  if (lcd_y < 0)
    lcd_y = 0;
  if (lcd_y > 1)
    lcd_y = 1;
  // 移动光标
  lcd_addr = 0x80 + 0x40 * lcd_y + lcd_x;
  send_command(lcd_addr);
  lcd_tmp = strlen(data);
  for (lcd_i = 0; lcd_i < lcd_tmp; ++lcd_i) {
    send_data(data[lcd_i]);
  }
}
int main() {
  fd = wiringPiI2CSetup(LCDAddr);
  printf("lcd1602 test program %x\n", fd);
  init();
  int lcd_x = 0;
  while (1) {
    write(lcd_x, 0, "Hello");
    write(lcd_x + 4, 1, "world!");
    delay(1000);
    if (++lcd_x > 15) {
      lcd_x = 0;
    }
    clear();
  }
  return 0;
}
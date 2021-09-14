/**************************************
 * 文件名: 28_rtc_ds1302.c
 * 版本: 2.0
 * 作者: 何友表
 * 说明: DS1032 实时时钟模块实验
 *************************************/
#include <ds1302.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wiringPi.h>

#define RTC_SECONDS 0
#define RTC_MINUTES 1
#define RTC_HOURS 2
#define RTC_DATE 3
#define RTC_MONTH 4
#define RTC_DAY 5
#define RTC_YEAR 6
#define RTC_WP 7
#define RTC_TC 8
#define RTC_BM 31
static unsigned int masks[] = {0x7f, 0x7f, 0x3f, 0x3f, 0x1f, 0x07, 0xff};
// BCD 码转为十进制
static int bcdToD(unsigned int ds_byte, unsigned int ds_mask) {
  unsigned int ds_b1, ds_b2;
  ds_byte &= ds_mask;
  ds_b1 = ds_byte & 0x0f;
  ds_b2 = ((ds_byte >> 4) & 0x0f) * 10;
  return ds_b1 + ds_b2;
}
// 十进制转为 BCD
static unsigned int dToBcd(unsigned int ds_byte) {
  ds_byte %= 100;
  return ((ds_byte / 10) << 4) + (ds_byte % 10);
}
// 测试数据
static int ramTestValues[] = {0x00, 0xff, 0xaa, 0x55, 0x01, 0x02, 0x04, 0x08,
                              0x10, 0x20, 0x40, 0x80, 0x00, 0xf0, 0x0f, -1};
// 延时函数
static int ramTest() {
  int ds_addr, ds_got, ds_i = 0, ds_errors = 0, ds_testValue;
  printf("DS1032 RAM TEST");
  ds_testValue = ramTestValues[ds_i];
  while (ds_testValue != -1) {
    for (ds_addr = 0; ds_addr < 31; ++ds_addr)
      ds1302ramWrite(ds_addr, ds_testValue);
    for (ds_addr = 0; ds_addr < 31; ++ds_addr) {
      if ((ds_got = ds1302ramRead(ds_addr)) != ds_testValue) {
        printf("DS132 RAM faiure: Address:%2d, Expected: 0x%02X, Got: 0x%02X\n",
               ds_addr, ds_testValue, ds_got);
        ++ds_errors;
      }
    }
    ds_testValue = ramTestValues[++ds_i];
  }
  for (ds_addr = 0; ds_addr < 31; ++ds_addr) {
    ds1302ramWrite(ds_addr, ds_addr);
  }
  for (ds_addr = 0; ds_addr < 32; ++ds_addr) {
    if ((ds_got = ds1302ramRead(ds_addr)) != ds_addr) {
      printf("DS1302 RAM Failure: Address: %2d, Expected: 0x%02X, Got 0x%02X\n",
             ds_addr, ds_addr, ds_got);
      ++ds_errors;
    }
  }
  if (ds_errors == 0) {
    printf("--  DS1302 RAM TEST: \n");
  } else {
    printf("-- DS1302 RAM TEST FAILURE: %d errors.\n", ds_errors);
  }
  return 0;
}
static int setLinuxClock() {
  char ds_dateTime[20];
  char ds_command[64];
  int ds_clock[8];
  printf("Setting the linux clock from the DS1302...");
  fflush(stdout);
  ds1302clockRead(ds_clock);
  sprintf(ds_dateTime, "%02d%02d%02d%02d%02d%02d.%02d",
          bcdToD(ds_clock[RTC_MONTH], masks[RTC_MONTH]),
          bcdToD(ds_clock[RTC_DATE], masks[RTC_DATE]),
          bcdToD(ds_clock[RTC_HOURS], masks[RTC_HOURS]),
          bcdToD(ds_clock[RTC_MINUTES], masks[RTC_MINUTES]), 20,
          bcdToD(ds_clock[RTC_YEAR], masks[RTC_YEAR]),
          bcdToD(ds_clock[RTC_SECONDS], masks[RTC_SECONDS]));
  sprintf(ds_command, "/bin/date %s", ds_dateTime);
  system(ds_command);
  return 0;
}
static int setDSClock(void) {
  struct tm t;
  time_t now;
  int ds_clock[8];
  int ds_time = 0;
  int ds_date = 0;
  int ds_weekday = 0;
  printf("Setting the clock in the DS1302 from type in...");
  printf("\n\nEnter Date(YYYYMMDD):");
  scanf("%d", &ds_date);
  printf("Enter time(HHMMSS, 24-hour clock):");
  scanf("%d", &ds_time);
  printf("Enter Weekday(0 as sunday)");
  scanf("%d", &ds_weekday);
  ds_clock[0] = dToBcd(ds_time % 100);       // 秒
  ds_clock[1] = dToBcd(ds_time / 100 % 100); // 分
  ds_clock[2] = dToBcd(ds_time / 100 / 100); // 小时
  ds_clock[3] = dToBcd(ds_date % 100);       // 天
  ds_clock[4] = dToBcd(ds_date / 100 % 100); // 月 0 - 11
  ds_clock[5] = dToBcd(ds_weekday);          // 星期 0 表示星期天
  ds_clock[6] = dToBcd(ds_date / 100 / 100); // 年
  ds_clock[7] = 0;
  ds1302clockWrite(ds_clock);
  printf("OK\n");
  return 0;
}
const char *weekOfDay[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
int main(int argc, char *argv[]) {
  int i, ds_clock[8], ds_year, ds_month, ds_date, ds_hour, ds_minute, ds_second,
      ds_weekday;
  wiringPiSetup();
  ds1302setup(0, 1, 2);
  if (argc == 2) {
    if (strcmp(argv[1], "-s1c") == 0) { // 设置系统时间
      return setLinuxClock();
    } else if (strcmp(argv[1], "-sdsc") == 0) { // 设置 DS1302 时间
      return setDSClock();
    } else if (strcmp(argv[1], "-rtest") == 0) { // 获取测试时间
      return ramTest();
    } else {
      printf(
          "Usage: ds1302 [-s1c | -sdsc | -rtest]\n"); // 如果输入错误，弹出提示信息
      return EXIT_FAILURE;
    }
  }
  for (i = 0;; ++i) {
    printf("%5d", i);
    ds1302clockRead(ds_clock);
    ds_hour = bcdToD(ds_clock[RTC_HOURS], masks[RTC_HOURS]);
    ds_minute = bcdToD(ds_clock[RTC_MINUTES], masks[RTC_MINUTES]);
    ds_second = bcdToD(ds_clock[RTC_SECONDS], masks[RTC_SECONDS]);
    ds_date = bcdToD(ds_clock[RTC_DATE], masks[RTC_DATE]);
    ds_month = bcdToD(ds_clock[RTC_MONTH], masks[RTC_MONTH]);
    ds_year = bcdToD(ds_clock[RTC_YEAR], masks[RTC_YEAR]) + 2000;
    ds_weekday = bcdToD(ds_clock[RTC_DAY], masks[RTC_DAY]);
    printf(" %04d-%02d-%02d", ds_year, ds_month, ds_date);
    printf(" %02d:%02d:%02d", ds_hour, ds_minute, ds_second);
    if (ds_weekday >= 0 && ds_weekday < 7) {
      printf(" %s", weekOfDay[ds_weekday]);
    } else {
      printf("weekday %d error", ds_weekday);
    }
    printf("\n");
    delay(1000);
  }
  return 0;
}
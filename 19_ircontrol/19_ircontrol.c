/**************************************
 * 文件名: 19_ircontrol.c
 * 版本: 1.0
 * 作者: 何友表
 * 说明: 红外线遥控实验，使用红外线遥控控制 LED
 * 灯
 *************************************/
#include <errno.h>
#include <lirc/lirc_client.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wiringPi.h>

typedef unsigned char uchar;
#define LED_RED_PIN 0
#define LED_GREEN_PIN 1
#define LED_BLUE_PIN 2

uchar rgb_color[3] = {0xff, 0xff, 0xff}, rgb_Lv[3] = {0x00, 0x44, 0xff};
// LED 灯按键
char *ir_keymap[] = {" KEY_CHANNELDOWN ", " KEY_CHANNEL ",   " KEY_CHANNELUP ",
                     " KEY_PREVIOUS ",    " KEY_NEXT ",      " KEY_PLAYPAUSE ",
                     " KEY_VOLUMEDOWN ",  " KEY_VOLUMEUP ",  " KEY_EQUAL ",
                     " KEY_NUMERIC_0 ",   " BTN_0 ",         " BTN_1 ",
                     " KEY_NUMERIC_1 ",   " KEY_NUMERIC_2 ", " KEY_NUMERIC_3 ",
                     " KEY_NUMERIC_4 ",   " KEY_NUMERIC_5 ", " KEY_NUMERIC_6 ",
                     " KEY_NUMERIC_7 ",   " KEY_NUMERIC_8 ", " KEY_NUMERIC_9 "};
// RGB_LED 初始化， 驱动 LED 方式为 PWM 方式
void ledInit() {
  softPwmCreate(LED_RED_PIN, 0, 100);
  softPwmCreate(LED_GREEN_PIN, 0, 100);
  softPwmCreate(LED_BLUE_PIN, 0, 100);
}
void ledSetColor() {
  softPwmWrite(LED_RED_PIN, rgb_color[0]);
  softPwmWrite(LED_GREEN_PIN, rgb_color[1]);
  softPwmWrite(LED_BLUE_PIN, rgb_color[2]);
}
void controlColor(int i) {
  switch (i) {
  case 1:
    rgb_color[0] = rgb_Lv[0];
    break;
  case 2:
    rgb_color[0] = rgb_Lv[1];
    break;
  case 3:
    rgb_color[0] = rgb_Lv[2];
    break;
  case 4:
    rgb_color[1] = rgb_Lv[0];
    break;
  case 5:
    rgb_color[1] = rgb_Lv[1];
    break;
  case 6:
    rgb_color[1] = rgb_Lv[2];
    break;
  case 7:
    rgb_color[2] = rgb_Lv[0];
    break;
  case 8:
    rgb_color[2] = rgb_Lv[1];
    break;
  case 9:
    rgb_color[2] = rgb_Lv[2];
    break;
  default:
    rgb_color[0] = rgb_Lv[0];
    rgb_color[1] = rgb_Lv[0];
    rgb_color[2] = rgb_Lv[0];
  }
}
int key_scan(char *code) {
  int i;
  int num;
  for (i = 0; i < sizeof(ir_keymap) / sizeof(char *); ++i) {
    if (strstr(code, ir_keymap[i])) {
      num = i;
    }
  }
  return num + 1;
}
int main() {
  struct lirc_config *config;
  int buttonTimer = millis();
  char *key_code;
  int num;
  if (wiringPiSetup() == -1) {
    printf("setup wiringPi failed!");
    return 1;
  }
  if (lirc_init("lirc", 1) == -1) {
    exit(EXIT_FAILURE);
  }
  ledInit();
  ledSetColor();

  if (lirc_readconfig(NULL, &config, NULL) == 0) {
    while (lirc_nextcode(&key_code) == 0) {
      // 判断是否有按键按下
      if (key_code == NULL) {
        continue;
      }
      if (millis() - buttonTimer > 400) {
        //判断按键按下的事件
        num = key_scan(key_code);
        printf("key %s(%d) pressed\n", key_code, num);
        controlColor(num);
        ledSetColor();
      }
      free(key_code);
    }
    lirc_freeconfig(config);
  }
  lirc_deinit();
  // 退出红外遥控器监测
  exit(EXIT_SUCCESS);
  return 0;
}
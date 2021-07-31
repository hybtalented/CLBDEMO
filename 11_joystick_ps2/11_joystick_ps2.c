/**************************************
 * 文件名 11_joystick_ps2.c
 * 版本 1.0
 * 作者 何友表
 * PS2 操纵杆实验，x 方向表示上（高）下（低），
 * y 方向表示左（低）右（高）
 *************************************/
#include <math.h>
#include <pcf8591.h>
#include <stdio.h>
#include <wiringPi.h>

#define PCF_PIN 120
#define PS_X_PIN (PCF_PIN + 0)
#define PS_Y_PIN (PCF_PIN + 1)
#define PS_SW_PIN (PCF_PIN + 2)
#define SQUARE(x) ((x) * (x))
inline int abs(int x) { return x > 0 ? x : -x; }
char *xdirection_desc[] = {"下", "", "上"},
     *y_direction_desc[] = {"左", "", "右"};
int main() {
  int x_value, y_value, sw_value;
  int direction_x = -1, direction_y = -1, tmp_x, tmp_y;
  if (wiringPiSetup() == -1) {
    printf("wiringPi Setup failed");
    return 1;
  }
  if (pcf8591Setup(PCF_PIN, 0x48) == -1) {
    printf("wiringPi pcf8591 Setup PIN %d failed", PCF_PIN);
    return 1;
  }
  pinMode(PS_SW_PIN, INPUT);
  while (1) {
    x_value = analogRead(PS_X_PIN);
    y_value = analogRead(PS_Y_PIN);
    sw_value = analogRead(PS_SW_PIN);
    if (x_value - 125 < -10) {
      // 下
      tmp_x = 0;
    } else if (x_value - 125 > 10) {
      // 上
      tmp_x = 2;
    } else {
      tmp_x = 1;
    }
    if (y_value - 125 < -10) {
      // 下
      tmp_y = 0;
    } else if (y_value - 125 > 10) {
      // 上
      tmp_y = 2;
    } else {
      tmp_y = 1;
    }
    if (tmp_x != direction_x || tmp_y != direction_y) {
      direction_x = tmp_x;
      direction_y = tmp_y;
      printf("\n***********************\n");
      if (direction_x == 1 && direction_y == 1) {
        printf("方向: 静止");
      } else {
        printf("方向: %s%s", xdirection_desc[direction_x],
               y_direction_desc[direction_y]);
      }
      printf("\n***********************\n");
    }

    printf("x 方向速度: %f, y 方向速度: %f, 按键状态: %d\n",
           abs(x_value - 125) / 255.0, abs(y_value - 125) / 255.0, sw_value);
    delay(200);
  }
  return 0;
}
/**************************************
 * 文件名: 04_tilt_switch.c
 * 版本: 2.0
 * 作者: 何友表
 * 说明: 倾斜传感器实验, 未倾斜时显示红灯,否者显示绿灯
 *************************************/
#include<wiringPi.h>
#include<stdio.h>

typedef unsigned char uchar;
#define TILT_SWITCH_SIG_PIN 0
#define RED_PIN 1
#define GREEN_PIN 2

int main() {
    if(wiringPiSetup() == -1) {
        printf("wiringPi Setup failed");
        return 1;
    }
    pinMode(TILT_SWITCH_SIG_PIN, INPUT);
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    while(1) {
        if (0 == digitalRead(TILT_SWITCH_SIG_PIN)) {
            if(0 == digitalRead(TILT_SWITCH_SIG_PIN)) {
                // 发生倾斜
                digitalWrite(RED_PIN, LOW);
                digitalWrite(GREEN_PIN, HIGH);
            }
        
        } else if (1 == digitalRead(TILT_SWITCH_SIG_PIN)) {
            delay(10);
            if (1 == digitalRead(TILT_SWITCH_SIG_PIN)) {
                // 未发生倾斜
                digitalWrite(RED_PIN, HIGH);
                digitalWrite(GREEN_PIN, LOW);
            }
        }
    }
    return 0;
}

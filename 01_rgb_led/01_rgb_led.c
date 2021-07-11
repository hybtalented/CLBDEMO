/*****************************************
 * 文件名: 01_rgb_led.c
 * 版本: 2.0
 * author: 何友表
 * 说明: LED 三色实验 
 */
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>


#define uchar unsigned char 
#define LED_RED_PIN 0
#define LED_GREEN_PIN 1
#define LED_BLUE_PIN 2
// 关灯
void led_init() {
    softPwmCreate(LED_RED_PIN, 0, 100);
    softPwmCreate(LED_GREEN_PIN, 0, 100);
    softPwmCreate(LED_BLUE_PIN, 0, 100);
}
void led_set_color(uchar red, uchar green, uchar blue) {
    softPwmWrite(LED_RED_PIN, red);  
    softPwmWrite(LED_GREEN_PIN, green);
    softPwmWrite(LED_BLUE_PIN, blue);  
}


int main() {
    if(wiringPiSetup() == -1) {
        printf("setup wringPi failed");
        return -1;
    }
   led_init();
    while(1) {
        char c =  getchar();
        switch(c) {
            case 'a':
                // 红色
                led_set_color(0xff, 0x00, 0x00);
                break;
            case 's':
                // 绿色
                led_set_color(0x00, 0xff,0x00);
                break;
            case 'd':
                // 蓝色
                led_set_color(0x00, 0x00,0xff);
                break;
            case 'q':
                // 黄色
                led_set_color(0xff, 0xff,0x00);
                break;
            case 'w':
                // 
                led_set_color(0xff, 0x00,0xff);
                break;
            case 'e':
                // 
                led_set_color(0x00, 0xff,0x3e);
                break;
            case 'z':
                // 
                led_set_color(0x94, 0x00,0xd3);
                break;
            case 'x':
                // 
                led_set_color(0x00, 0x00,0x00);
                break;
            case 'c':
                // 
                led_set_color(0x66, 0xaa,0x23);
                break;
        }
    }
}


/**************************************
 * 文件名: 05_active_buzzer.c
 * 版本: 2.0
 * 作者: 何友表
 * 说明: 有源蜂鸣器实验, 发送SOS摩尔斯码
 *************************************/
#include<wiringPi.h>
#include<stdio.h>
typedef unsigned char uchar;
#define BUZZER_IO_PIN 0
#define DEVICE_ON_VALUE LOW
#define DEVICE_OFF_VALUE HIGH
#define INTERVAL 300 


void sendMorseCode(uchar* morse_arr, int arr_len);
int main() {
    if(wiringPiSetup() == -1) {
        printf("wiringPi Setup failed");
        return 1;
    }
    pinMode(BUZZER_IO_PIN, OUTPUT);
    uchar morse_arr[] = { 2, 2, 2, 0, 1, 1, 1, 0, 2, 2, 2, 3 };
    while(1) {
	sendMorseCode(morse_arr, sizeof(morse_arr) / sizeof(uchar));
    }
    return 0;
}
void sendMorseCode(uchar* morse_arr, int arr_len) {
    for(int i = 0; i < arr_len; ++i) {
        uchar time = morse_arr[i];
        switch(time) {
        // 字符间隔
        case 0:	
            digitalWrite(BUZZER_IO_PIN, DEVICE_OFF_VALUE);
            delay(3 * INTERVAL);
            break;
        // 滴
        case 1:
            digitalWrite(BUZZER_IO_PIN, DEVICE_ON_VALUE);
            delay(INTERVAL);
            break;
        // 嗒
        case 2:
            digitalWrite(BUZZER_IO_PIN, DEVICE_ON_VALUE);
            delay(3 * INTERVAL);
            break;
        // 单词间隔
        case 3: 
            digitalWrite(BUZZER_IO_PIN, DEVICE_OFF_VALUE);
            delay(7 * INTERVAL);
            break;
	default:
            break;
        }
        digitalWrite(BUZZER_IO_PIN, DEVICE_OFF_VALUE);
        delay(INTERVAL);

    }
}

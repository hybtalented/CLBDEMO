/**************************************
 * 文件名: 03_laser.c
 * 版本: 2.0
 * 作者: 何友表
 * 说明: 激光传感器实验, 发送SOS摩尔斯码
 *************************************/
#include<wiringPi.h>
#include<stdio.h>

typedef unsigned char uchar;
#define LASER_SIG_PIN 0
#define INTERVAL 300

void sendMorseCode(uchar* morse_arr, int arr_len);
int main() {
    if(wiringPiSetup() == -1) {
        printf("wiringPi Setup failed");
        return 1;
    }
    pinMode(LASER_SIG_PIN, OUTPUT);
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
            digitalWrite(LASER_SIG_PIN, LOW);
            delay(3 * INTERVAL);
            break;
        // 滴
        case 1:
            digitalWrite(LASER_SIG_PIN, HIGH);
            delay(INTERVAL);
            break;
        // 嗒
        case 2:
            digitalWrite(LASER_SIG_PIN, HIGH);
            delay(3 * INTERVAL);
            break;
        // 单词间隔
        case 3: 
            digitalWrite(LASER_SIG_PIN, LOW);
            delay(7 * INTERVAL);
            break;
	default:
            break;
        }
        digitalWrite(LASER_SIG_PIN, LOW);
        delay(INTERVAL);

    }
}

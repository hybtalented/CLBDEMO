/**************************************
 * 文件名: 02_relay.c
 * 版本: 2.0
 * 作者: 何友表
 * 说明: 继电器模块实验
 *************************************/
#include<wiringPi.h>
#include<stdio.h>


#define RELAY_SIG_PIN 0
int main() {
    if(wiringPiSetup() == -1) {
        printf("wiringPi Setup failed");
        return 1;
    }
    while(1) {
	char c = getchar();
        switch(c) {
            case 'o':
                digitalWrite(RELAY_SIG_PIN, HIGH);
                break;
            case 'f':
                digitalWrite(RELAY_SIG_PIN, LOW);
                break;
            default:
                break;
        }
    }
    return 0;
}

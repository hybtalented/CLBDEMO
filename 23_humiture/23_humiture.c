/**************************************
 * 文件名: 23_humiture.c
 * 版本: 1.0
 * 作者: 何友表
 * 说明: 湿度传感器实验，检测环境温度和湿度
 *************************************/
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <wiringPi.h>

#define MAX_TIMINGS 85
#define DHTPIN 2

int dht11_dat[5] = {0, 0, 0, 0, 0};

void read_dht11_dat() {
  uint8_t dht_last_state = HIGH, // 等待高电平
      counter = 0, j = 0, i;
  float f; // 华氏温度
  for (i = 0; i < sizeof(dht11_dat) / sizeof(dht11_dat[0]); ++i) {
    dht11_dat[i] = 0;
  }
  pinMode(DHTPIN, OUTPUT);
  digitalWrite(DHTPIN, LOW); // 传感器输出低电平
  delay(18);
  // 18毫秒后，上拉40毫秒
  digitalWrite(DHTPIN, HIGH);
  delayMicroseconds(40);
  pinMode(DHTPIN, INPUT);
  // 等待 85 毫秒的高电平后进行数据接受
  for (i = 0; i < MAX_TIMINGS; ++i) {
    counter = 0;
    while (digitalRead(DHTPIN) == dht_last_state) { // 等待高电平结束
      counter++;
      delayMicroseconds(1);
      if (counter == 255) { // 如果等待时间过长，则退出
        break;
      }
    }

    dht_last_state = digitalRead(DHTPIN);
    if (counter == 255) {
      break; // 如果等待事件过长，则退出
    }
    // 忽略前三个数据
    if ((i >= 4) && (i % 2 == 0)) {
      dht11_dat[j / 8] <<= 1;
      if (counter > 16) {
        dht11_dat[j / 8] |= 1;
      }
      j++;
    }
  }

  if (j >= 40 && (dht11_dat[4] ==
                  ((dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) &
                   0xff))) {         // 校验数据
    f = dht11_dat[2] * 9. / 5. + 32; // 计算温度值
    printf("Humidity = %d.%d %% Temperature  = %d.%d *C （%.1f *F)\n",
           dht11_dat[0], dht11_dat[1], dht11_dat[2], dht11_dat[3], f);
  }
}
int main() {
  printf("DHT11 Temperature test program\n");
  if (wiringPiSetup() == -1) {
    fprintf(stderr, "wiringPi Setup failed:%s", strerror(errno));
    return 1;
  }

  while (1) {
    read_dht11_dat();
    delay(1000);
  }
  return 0;
}
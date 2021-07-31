/**************************************
 * 文件名: 06_passive_buzzer.c
 * 版本: 2.0
 * 作者: 何友表
 * 说明: 无源蜂鸣器实验， 播放歌曲
 *************************************/

#include <softTone.h>
#include <stdio.h>
#include <wiringPi.h>

// 低 C 音符频率定义
#define Tone_CL1 131
#define Tone_CL2 147
#define Tone_CL3 165
#define Tone_CL4 175
#define Tone_CL5 196
#define Tone_CL6 221
#define Tone_CL7 248
// 中 C 音符频率定义
#define Tone_CM1 262
#define Tone_CM2 294
#define Tone_CM3 330
#define Tone_CM4 350
#define Tone_CM5 393
#define Tone_CM6 441
#define Tone_CM7 495
// 高 C 音符频率定义
#define Tone_CH1 525
#define Tone_CH2 589
#define Tone_CH3 661
#define Tone_CH4 700
#define Tone_CH5 786
#define Tone_CH6 882
#define Tone_CH7 990

#define BUZZER_IO_PIN 0
#define INTERVAL 500
const int tone_song1[] = {
    Tone_CM3, Tone_CM5, Tone_CM6, Tone_CM3, Tone_CM2, Tone_CM3, Tone_CM5,
    Tone_CM6, Tone_CH1, Tone_CM6, Tone_CM5, Tone_CM1, Tone_CM3, Tone_CM2,
    Tone_CM2, Tone_CM3, Tone_CM5, Tone_CM2, Tone_CM3, Tone_CM3, Tone_CL6,
    Tone_CL6, Tone_CL6, Tone_CM1, Tone_CM2, Tone_CM3, Tone_CM2, Tone_CL7,
    Tone_CL6, Tone_CM1, Tone_CL5};
const int beat_song1[] = {1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 3,
                          1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 3};
const int tone_song2[] = {Tone_CM1, Tone_CM1, Tone_CM1, Tone_CL5, Tone_CM3,
                          Tone_CM3, Tone_CM3, Tone_CM1, Tone_CM1, Tone_CM3,
                          Tone_CM5, Tone_CM5, Tone_CM4, Tone_CM3, Tone_CM2,
                          Tone_CM2, Tone_CM3, Tone_CM4, Tone_CM4, Tone_CM3,
                          Tone_CM2, Tone_CM3, Tone_CM1, Tone_CM1, Tone_CM3,
                          Tone_CM2, Tone_CL5, Tone_CL7, Tone_CM2, Tone_CM1};
const int beat_song2[] = {1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 3,
                          1, 1, 1, 2, 1, 1, 1, 3, 1, 1, 1, 3, 3, 2, 3};
void playSong(const int *tone_arr, const int *beat_arr, const int arr_len);
int main() {
  if (wiringPiSetup() == -1) {
    printf("wiringPi Setup failed");
    return 1;
  }
  if (softToneCreate(BUZZER_IO_PIN) == -1) {
    printf("softTone Setup failed");
    return 1;
  }
  while (1) {
    char ch = getchar();
    switch (ch) {
    case 'a':
      playSong(tone_song1, beat_song1, sizeof(tone_song1) / sizeof(int));
      break;
    case 'b':
      playSong(tone_song2, beat_song2, sizeof(tone_song2) / sizeof(int));
      break;
    default:
      break;
    }
  }
  return 0;
}
void playSong(const int *tone_arr, const int *beat_arr, const int arr_len) {
  for (int i = 0; i < arr_len; ++i) {
    softToneWrite(BUZZER_IO_PIN, tone_arr[i]);
    delay(beat_arr[i] * INTERVAL);
  }
  softToneStop(BUZZER_IO_PIN);
}

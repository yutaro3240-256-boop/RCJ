#include "forLib.h"

Color S9706;

void forLib::begin(){
  uint32_t COLOR_pin[2][4] = { { PD8, PD9, PD10, PD11 }, { PA9, PA10, PA11, PA12 } };  //[カラセンの番号],[PIN]
  S9706.begin(COLOR_pin[0][GATE_PIN], COLOR_pin[0][CK_PIN], COLOR_pin[0][RANGE_PIN], COLOR_pin[0][DOUT_PIN]);
  S9706.begin(COLOR_pin[1][GATE_PIN], COLOR_pin[1][CK_PIN], COLOR_pin[1][RANGE_PIN], COLOR_pin[1][DOUT_PIN]);
  for (int i = 0; i < 21; i++) {  //フォトリフレクタ設定
    pinMode(Photo[i], INPUT);
  }
  for (int i = 0; i < 4; i++) {  //LED設定
    pinMode(LED[i], OUTPUT);
  }
  pinMode(G_BOOT, OUTPUT);//ジャイロ設定
  pinMode(PhotoLED, OUTPUT);//フォトリフレクタLED設定
  digitalWrite(PhotoLED, HIGH);
}

void forLib::LEDstate(int pin, int state){
    digitalWrite(LED[pin], state);
}

int forLib::Photoformula(){
  int sum = 0;
  for (int i = 0; i < 20; i++) {
    sum += analogRead(Photo[i]) * Photogain[i];
  }
  return sum;
}



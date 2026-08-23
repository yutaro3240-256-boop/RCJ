#include "forLib.h"

Color S9706;
Adafruit_NeoPixel pixels(4,PB13,NEO_GRB + NEO_KHZ800);
VL53L1X MyToF;
HLSCL hlscl;
HardwareSerial motor(PE0, PE1);
HardwareSerial MySerial2(PG0, PG1);
TwoWire ToF_Wire(MULTI_SDA, MULTI_SCA);
TwoWire Wire3(PC10,PC11);
BNO08x myIMU;

void forLib::begin(){

  uint32_t COLOR_pin[2][4] = { { PD8, PD9, PD10, PD11 }, { PA9, PA10, PA11, PA12 } };  //[カラセンの番号],[PIN]
  S9706.begin(COLOR_pin[0][GATE_PIN], COLOR_pin[0][CK_PIN], COLOR_pin[0][RANGE_PIN], COLOR_pin[0][DOUT_PIN]);
  S9706.begin(COLOR_pin[1][GATE_PIN], COLOR_pin[1][CK_PIN], COLOR_pin[1][RANGE_PIN], COLOR_pin[1][DOUT_PIN]);
  motor.begin(1000000);  //mega2560
  MySerial2.begin(9600);
  hlscl.pSerial = &motor;
  ToF_Wire.begin(PB7, PB8);
  ToF_Wire.setClock(400000);
  Wire3.begin();
  
  hlscl.WheelMode(1);  //サーボID1を定速モードに切り替える
  hlscl.WheelMode(2);  //サーボID2を定速モードに切り替える

  MyToF.setBus(&Wire3);
  for (uint8_t t = 0; t < 8; t++) { //ToF設定
    this->ToFSelect(t);
    MyToF.init();
    MyToF.setDistanceMode(VL53L1X::Long);
    MyToF.setMeasurementTimingBudget(50000);
    MyToF.startContinuous(50);
  }

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

void forLib::ToFSelect(uint8_t _pin){
  if (_pin > 7) return;
  ToF_Wire.beginTransmission(TCAADDR);
  ToF_Wire.write(1 << _pin);
  ToF_Wire.endTransmission();  // Fixed typo
  return;
}

double forLib::Photoformula(){
  int sum = 0;
  for (int i = 2; i <= 17; i++) {
    sum += analogRead(Photo[i]) * Photogain[i];
  }
  return sum;
}



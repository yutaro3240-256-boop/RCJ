#include "forLib.h"

Color S9706;
Adafruit_NeoPixel pixels(4,PB13,NEO_GRB + NEO_KHZ800);
VL53L1X MyToF;
HLSCL hlscl;
HardwareSerial motor(PE0, PE1);
HardwareSerial MySerial2(PG0, PG1);
TwoWire ToF_Wire(MULTI_SDA, MULTI_SCA);
TwoWire IMU_Wire(PC10,PC11);
BNO08x myIMU;
byte ID[2] = { 1, 2 };
s16 Speed[2]={0,0};
byte ACC[2] = { 0, 0 };
u16 Torque[2] = { 500, 500 };

void forLib::begin(){
  
  uint32_t COLOR_pin[2][4] = { { PD8, PD9, PD10, PD11 }, { PG9, PG11, PG10, PD7 } };  //[カラセンの番号],[PIN]
  S9706.begin(COLOR_pin[0][GATE_PIN], COLOR_pin[0][CK_PIN], COLOR_pin[0][RANGE_PIN], COLOR_pin[0][DOUT_PIN]);
  S9706.begin(COLOR_pin[1][GATE_PIN], COLOR_pin[1][CK_PIN], COLOR_pin[1][RANGE_PIN], COLOR_pin[1][DOUT_PIN]);
  motor.begin(1000000);  //mega2560
  MySerial2.begin(9600);
  hlscl.pSerial = &motor;
  ToF_Wire.begin();
  ToF_Wire.setClock(400000);
  IMU_Wire.begin();
  IMU_Wire.setClock(100000);
  
  hlscl.WheelMode(1);  //サーボID1を定速モードに切り替える
  hlscl.WheelMode(2);  //サーボID2を定速モードに切り替える

  MyToF.setBus(&ToF_Wire);
  for (uint8_t t = 0; t < 8; t++) { //ToF設定
    this->ToFSelect(t);
    MyToF.init();
    MyToF.setDistanceMode(VL53L1X::Long);
    MyToF.setMeasurementTimingBudget(50000);
    MyToF.startContinuous(50);
  }
  pinMode(G_BOOT, OUTPUT);//ジャイロ設定
  digitalWrite(G_BOOT,HIGH);
  if (myIMU.begin(BNO08X_ADDR, IMU_Wire, G_INIT, G_RST) == false) {
    this->LEDstate(A,forLib::ON);
  }
  myIMU.enableRotationVector(50);
  delay(1000);

  pixels.begin();

  for (int i = 0; i < 21; i++) {  //フォトリフレクタ設定
    pinMode(Photo[i], INPUT_ANALOG);
  }
  for (int i = 0; i < 4; i++) {  //LED設定
    pinMode(LED[i], OUTPUT);
  }

  pinMode(PhotoLED, OUTPUT);//フォトリフレクタLED設定
  digitalWrite(PhotoLED, HIGH);

}

void forLib::LEDstate(forLib::_LED pin, forLib::_STATE state){
  GPIOD->BSRR=pin<<state;
}

void forLib::ToFSelect(uint8_t _pin){
  if (_pin > 7) return;
  ToF_Wire.beginTransmission(TCAADDR);
  ToF_Wire.write(1 << _pin);
  ToF_Wire.endTransmission();  // Fixed typo
  return;
}

void forLib::turn(s16 _speed, long t){
  /*s16 _Speed[2]={_speed,_speed};
  hlscl.SyncWriteSpe(ID, 2, _Speed, ACC, Torque);
  delay(t);
  this->stop();*/
}

void forLib::stop(){
  s16 _Speed[2]={0,0};
  hlscl.SyncWriteSpe(ID, 2, _Speed, ACC, Torque);
}

double forLib::Photoformula(){
  double sum = 0;
  for (int i = 2; i <= 17; i++) {
    double p= analogRead(Photo[i]) * Photogain[i];
    sum += p;
  }
  return sum;
}



#include <SCServo.h>

HLSCL hlscl;

void setup()
{
  //Serial1.begin(1000000, SERIAL_8N1, 18, 17);//esp32-s3
  Serial1.begin(1000000);//mega2560
  hlscl.pSerial = &Serial1;
  delay(1000);
  hlscl.EleMode(1);//サーボID1をモーター定力モードに切り替える
}

void loop()
{
  //サーボモーター(ID1)は最大トルク電流T=300×6.5=1950mAで正方向に回転する
  hlscl.WriteEle(1, 300);
  delay(5000);
  
  //サーボモーター(ID1)はトルク0で回転を停止する
  hlscl.WriteEle(1, 0);
  delay(2000);
  
  //サーボモーター(ID1)は最大トルク電流T=300×6.5=1950mAで逆回転する
  hlscl.WriteEle(1, -300);
  delay(5000);
  
  //サーボ(ID1)はトルク0で回転を停止する
  hlscl.WriteEle(1, 0);
  delay(2000);
}

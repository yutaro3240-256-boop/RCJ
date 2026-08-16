#include <SCServo.h>

HLSCL hlscl;

void setup()
{
  //Serial1.begin(1000000, SERIAL_8N1, 18, 17);//esp32-s3
  Serial.begin(1000000);//mega2560
  hlscl.pSerial = &Serial;
  delay(1000);
  hlscl.WheelMode(1);//サーボID1をモーター定速モードに切り替える
}

void loop()
{
  //サーボモーター(ID1/ID2)は加速度A=50×8.7deg/s²で最高速度V=60×0.732=43.92rpmまで加速し、
  //その後一定速度で正方向に回転を維持する。最大トルク電流T=500×6.5=3250mA
  hlscl.WriteSpe(1, 60, 50, 500);
  delay(5000);
  
  //サーボモーター(ID1/ID2)は加速度A=50×8.7度/秒²で減速し、速度0で回転を停止する
  hlscl.WriteSpe(1, 0, 50, 500);
  delay(2000);
  
  //サーボモーター(ID1/ID2)は加速度A=50×8.7deg/s²で最高速度V=-60×0.732=-43.92rpmまで加速し、
  //その後一定速度で逆回転を維持する。最大トルク電流T=500×6.5=3250mA
  hlscl.WriteSpe(1, -60, 50, 500);
  delay(5000);
  
  //サーボモーター(ID1/ID2)は加速度A=50×8.7度/秒²で減速し、速度0で回転を停止する。
  hlscl.WriteSpe(1, 0, 50, 500);
  delay(2000);
}

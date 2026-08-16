#include <SCServo.h>
HLSCL hlscl;

byte ID[2];
s16 Speed[2];
byte ACC[2];
u16 Torque[2];

void setup()
{
  //Serial1.begin(1000000, SERIAL_8N1, 18, 17);//esp32-s3
  Serial1.begin(1000000);//mega2560
  hlscl.pSerial = &Serial1;
  delay(1000);
  hlscl.WheelMode(1);//サーボID1を定速モードに切り替える
  hlscl.WheelMode(2);//サーボID2を定速モードに切り替える
  ID[0] = 1;//サーボID1
  ID[1] = 2;//サーボID2
  ACC[0] = 50;//加速度A=50*8.7deg/s^2
  ACC[1] = 50;//加速度A=50*8.7deg/s^2
  Torque[0] = 500;//最大トルク電流T=500*6.5=3250mA
  Torque[1] = 500;//最大トルク電流T=500*6.5=3250mA
}

void loop()
{
  //サーボモーター(ID1/ID2)は加速度A=50×8.7deg/s²で最高速度V=60×0.732=43.92rpmまで加速し、
  //その後定速運転を維持する。最大トルク電流T=500×6.5=3250mA
  Speed[0] = 60;
  Speed[1] = 60;
  hlscl.SyncWriteSpe(ID, 2, Speed, ACC, Torque);
  delay(5000);

  //サーボモーター(ID1/ID2)は加速度A=50×8.7度/秒²で減速し、速度0で停止する。
  Speed[0] = 0;
  Speed[1] = 0;
  hlscl.SyncWriteSpe(ID, 2, Speed, ACC, Torque);
  delay(2000);
  
  //サーボモーター(ID1/ID2)は加速度A=50×8.7deg/s²で最高速度V=-60×0.732=-43.92rpmまで加速し、
  //その後定速運転を維持する。最大トルク電流T=500×6.5=3250mA
  Speed[0] = -60;
  Speed[1] = -60;
  hlscl.SyncWriteSpe(ID, 2, Speed, ACC, Torque);
  delay(5000);

  //サーボモーター(ID1/ID2)は加速度A=50×8.7度/秒²で減速し、速度0で停止する。
  Speed[0] = 0;
  Speed[1] = 0;
  hlscl.SyncWriteSpe(ID, 2, Speed, ACC, Torque);
  delay(2000);
}

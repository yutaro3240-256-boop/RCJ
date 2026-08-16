// ID1,ID2のサーボ角度を個別に制御する

#include <SCServo.h>

HLSCL hlscl;

void setup()
{
  //Serial1.begin(1000000, SERIAL_8N1, 18, 17);//esp32-s3
  Serial1.begin(1000000);//mega2560
  hlscl.pSerial = &Serial1;
  delay(1000);
  hlscl.ServoMode(1); //ID1のサーボモータをサーボモードに設定する
  hlscl.ServoMode(2); //ID2のサーボモータをサーボモードに設定する
}

void loop()
{
  //サーボモーター(ID1/ID2)は最高速度V=60×0.732=43.92rpm、加速度A=50×8.7deg/s^2、
  //最大トルク電流T=3500×6.5=3250mAで動作し、P1=4095の位置まで移動する。
  hlscl.RegWritePosEx(1, 4095, 60, 50, 500);
  hlscl.RegWritePosEx(2, 4095, 60, 50, 500);
  hlscl.RegWriteAction();
  delay((4095-0)*1000/(60*50) + (60*50)*10/(50) + 50);//[(P1-P0)/(V*50)]*1000+[(V*50)/(A*100)]*1000 + 50(誤差)

  //サーボモーター(ID1/ID2)は最高速度V=60×0.732=43.92rpm、加速度A=50×8.7deg/s^2、
  //最大トルク電流T=500×6.5=3250mAで動作し、P1=4095の位置まで移動する。
  hlscl.RegWritePosEx(1, 0, 60, 50, 500);
  hlscl.RegWritePosEx(2, 0, 60, 50, 500);
  hlscl.RegWriteAction();
  delay((4095-0)*1000/(60*50) + (60*50)*10/(50) + 50);//[(P1-P0)/(V*50)]*1000+[(V*50)/(A*100)]*1000 + 50(誤差)
}

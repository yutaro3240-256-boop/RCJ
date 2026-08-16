/*
サーボパラメータプログラミング
*/

#include <SCServo.h>

int LEDpin = 13;
HLSCL hlscl;

void setup()
{
  pinMode(LEDpin, OUTPUT);
  //Serial1.begin(1000000, SERIAL_8N1, 18, 17);//esp32-s3
  Serial1.begin(1000000);//mega2560
  hlscl.pSerial = &Serial1;
  delay(1000);
  digitalWrite(LEDpin, LOW);
  hlscl.unLockEprom(1);//EPROM保存機能を有効にする
  hlscl.writeByte(1, HLSCL_ID, 2);//ID
  hlscl.LockEprom(2);//EPROM保存機能を無効にする
  digitalWrite(LEDpin, HIGH);
}

void loop()
{

}

/*
同期読み取り指令、ID1とID2の2つのサーボの位置と速度情報を読み戻す
*/

#include <SCServo.h>

HLSCL hlscl;

uint8_t ID[] = {1, 2};  //ID1とID2のサーボを指定
uint8_t rxPacket[4];
int16_t Position;
int16_t Speed;

void setup()
{
  Serial.begin(115200);
  //Serial1.begin(1000000, SERIAL_8N1, 18, 17);//esp32-s3
  Serial1.begin(1000000);//mega2560
  hlscl.pSerial = &Serial1;
  hlscl.syncReadBegin(sizeof(ID), sizeof(rxPacket), 5);//10*10*2=200us<5ms
  delay(1000);
}

void loop()
{  
  hlscl.syncReadPacketTx(ID, sizeof(ID), HLSCL_PRESENT_POSITION_L, sizeof(rxPacket));//同期読み取り命令パケット送信
  for(uint8_t i=0; i<sizeof(ID); i++){
    //ID[i]同期読み取り応答パケットを受信
    if(!hlscl.syncReadPacketRx(ID[i], rxPacket)){
     Serial.print("ID:");
     Serial.println(ID[i]);
     Serial.println("sync read error!");
     continue;//受信デコード失敗
    }
    Position = hlscl.syncReadRxPacketToWrod(15);//2バイトをデコードする。bit15は方向ビットであり、パラメータ=0は方向ビットなしを示す。
    Speed = hlscl.syncReadRxPacketToWrod(15);//2バイトをデコードする。bit15は方向ビットであり、パラメータ=0は方向ビットなしを示す。
    Serial.print("ID:");
    Serial.println(ID[i]);
    Serial.print("Position:");
    Serial.println(Position);
    Serial.print("Speed:");
    Serial.println(Speed);
  }
  delay(10);
}

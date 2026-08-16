/*
全サーボフィードバックパラメータを読み戻す：位置、速度、負荷、電圧、温度、動作状態、電流；
FeedBack関数はサーボパラメータをバッファに読み戻し、
Readxxx(-1)関数はバッファ内の対応するサーボ状態を返す；
関数Readxxx(ID)において、ID=-1の場合FeedBackバッファのパラメータを返す；
ID>=0の場合、読み取り命令により直接指定IDのサーボ状態を返すため、
FeedBack関数の呼び出しは不要である。
*/

#include <SCServo.h>

HLSCL hlscl;
int LEDpin = 13;

void setup()
{
  pinMode(LEDpin,OUTPUT);
  digitalWrite(LEDpin, HIGH);
  Serial1.begin(1000000);//mega2560
  //Serial1.begin(1000000, SERIAL_8N1, 18, 17);//esp32-s32
  Serial.begin(115200);
  hlscl.pSerial = &Serial1;
  delay(1000);
}

void loop()
{
  int Pos;
  int Speed;
  int Load;
  int Voltage;
  int Temper;
  int Move;
  int Current;
  hlscl.FeedBack(1);
  if(!hlscl.getLastError()){
    digitalWrite(LEDpin, LOW);
    Pos = hlscl.ReadPos(-1);
    Speed = hlscl.ReadSpeed(-1);
    Load = hlscl.ReadLoad(-1);
    Voltage = hlscl.ReadVoltage(-1);
    Temper = hlscl.ReadTemper(-1);
    Move = hlscl.ReadMove(-1);
    Current = hlscl.ReadCurrent(-1);
    Serial.print("Position:");
    Serial.println(Pos);
    Serial.print("Speed:");
    Serial.println(Speed);
    Serial.print("Load:");
    Serial.println(Load);
    Serial.print("Voltage:");
    Serial.println(Voltage);
    Serial.print("Temper:");
    Serial.println(Temper);
    Serial.print("Move:");
    Serial.println(Move);
    Serial.print("Current:");
    Serial.println(Current);
    delay(10);
  }else{
    digitalWrite(LEDpin, HIGH);
    Serial.println("FeedBack err");
    delay(500);
  }
  
  Pos = hlscl.ReadPos(1);
  if(!hlscl.getLastError()){
    digitalWrite(LEDpin, LOW);
    Serial.print("Servo position:");
    Serial.println(Pos, DEC);
    delay(10);
  }else{
    Serial.println("read position err");
    digitalWrite(LEDpin, HIGH);
    delay(500);
  }
  
  Voltage = hlscl.ReadVoltage(1);
  if(!hlscl.getLastError()){
    digitalWrite(LEDpin, LOW);
    Serial.print("Servo Voltage:");
    Serial.println(Voltage, DEC);
    delay(10);
  }else{
    Serial.println("read Voltage err");
    digitalWrite(LEDpin, HIGH);
    delay(500);
  }
  
  Temper = hlscl.ReadTemper(1);
  if(!hlscl.getLastError()){
    digitalWrite(LEDpin, LOW);
    Serial.print("Servo temperature:");
    Serial.println(Temper, DEC);
    delay(10);
  }else{
    Serial.println("read temperature err");
    digitalWrite(LEDpin, HIGH);
    delay(500);    
  }

  Speed = hlscl.ReadSpeed(1);
  if(!hlscl.getLastError()){
    digitalWrite(LEDpin, LOW);
    Serial.print("Servo Speed:");
    Serial.println(Speed, DEC);
    delay(10);
  }else{
    Serial.println("read Speed err");
    digitalWrite(LEDpin, HIGH);
    delay(500);    
  }
  
  Load = hlscl.ReadLoad(1);
  if(!hlscl.getLastError()){
    digitalWrite(LEDpin, LOW);
    Serial.print("Servo Load:");
    Serial.println(Load, DEC);
    delay(10);
  }else{
    Serial.println("read Load err");
    digitalWrite(LEDpin, HIGH);
    delay(500);    
  }
  
  Current = hlscl.ReadCurrent(1);
  if(!hlscl.getLastError()){
    digitalWrite(LEDpin, LOW);
    Serial.print("Servo Current:");
    Serial.println(Current, DEC);
    delay(10);
  }else{
    Serial.println("read Current err");
    digitalWrite(LEDpin, HIGH);
    delay(500);    
  }

  Move = hlscl.ReadMove(1);
  if(!hlscl.getLastError()){
    digitalWrite(LEDpin, LOW);
    Serial.print("Servo Move:");
    Serial.println(Move, DEC);
    delay(10);
  }else{
    Serial.println("read Move err");
    digitalWrite(LEDpin, HIGH);
    delay(500);    
  }
  Serial.println();
}

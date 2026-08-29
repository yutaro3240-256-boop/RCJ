#include <Arduino.h>
#include <forlib.h>
#include <Color.h>
#include <HLSCL.h>
#include <Wire.h>
#include <VL53L1X.h>
#include <Adafruit_NeoPixel.h>

#define velocity 40
#define ToFfront 2
#define ToFleft 2

forLib myrobot;

void setReports();
double D_zure=0;
void setup() {
  myrobot.begin();
  hlscl.SyncWriteSpe(ID, 2, Speed, ACC, Torque);
  delay(1000);
  myrobot.ToFSelect(ToFfront);
  //myrobot.LEDstate(0,HIGH);
  digitalWrite(PhotoLED, HIGH);
  setReports();
  S9706.setcompareRange_ratio(100);
  pixels.clear();
  for(int k=0; k<=3; k++){
      pixels.setPixelColor(k, pixels.Color(255, 255, 5));
    }
  pixels.show();
  delay(100);
  
}

void setReports(void) {
  if (myIMU.enableRotationVector() == true) {
    digitalWrite(LED[0], HIGH);
  }

  delay(100);
  digitalWrite(LED[0], LOW);
  
}

void loop() {
  /*S9706.update();
  if(S9706.available()){
    S9706.finishall();
    for(int i=0; i<2; i++){
      RGB rgb=S9706.get(i);
      MySerial2.print(i);
      MySerial2.print("::");
      MySerial2.print(rgb.r);
      MySerial2.print(":");
      MySerial2.print(rgb.g);
      MySerial2.print(":");
      MySerial2.print(rgb.b);
      MySerial2.println("======");
    }
    S9706.startall();
  }*/

  double p = myrobot.Photoformula();
  double d = p-D_zure;
  s16 TempS[2];
  double err = p*0.3+d*1;            
  TempS[0] = s16(err + velocity);
  TempS[1] = s16(err - velocity);
  hlscl.SyncWriteSpe(ID, 2, TempS, ACC, Torque);
  D_zure = p;

  if(analogRead(Photo[0])>700||analogRead(Photo[1])>700||analogRead(Photo[18])>700||analogRead(Photo[19])>700){
    myrobot.stop();

    int black=0;
    if(analogRead(Photo[0])>700||analogRead(Photo[1])>700){
      black+=1;
    }
    if(analogRead(Photo[18])>700||analogRead(Photo[19])>700){
      black+=2;
    }
    delay(100);
    Speed[0]=-40;
    Speed[1]=40;
    hlscl.SyncWriteSpe(ID, 2, Speed, ACC, Torque);
    delay(250);
    myrobot.stop();
    delay(500);
    int check=0;
    for(int i=0; i<2; i++){
      RGB rgb=S9706.get(i,true);
      if(rgb.r<4000&&rgb.g>3900){
        check+=i+1;
      }
    }
    MySerial2.println(check);
    for(int i=0; i<check; i++){
      myrobot.LEDstate(forLib::D,forLib::ON);
      delay(100);
      myrobot.LEDstate(forLib::D,forLib::OFF);
      delay(100);
    }
    for(int i=0; i<black; i++){
      myrobot.LEDstate(forLib::B,forLib::ON);
      delay(100);
      myrobot.LEDstate(forLib::B,forLib::OFF);
      delay(100);
    }
    myrobot.LEDstate(forLib::A,forLib::ON);
    switch (check)
    {
    case 1:
      Speed[0]=40;
      Speed[1]=-40;
      hlscl.SyncWriteSpe(ID, 2, Speed, ACC, Torque);
      delay(500);
      Speed[0]=80;
      Speed[1]=50;
      hlscl.SyncWriteSpe(ID, 2, Speed, ACC, Torque);
      delay(1000);
      while(analogRead(Photo[10])<600);
      myrobot.stop();
      break;
    case 2:
      Speed[0]=40;
      Speed[1]=-40;
      hlscl.SyncWriteSpe(ID, 2, Speed, ACC, Torque);
      delay(500);
      Speed[0]=-50;
      Speed[1]=-80;
      hlscl.SyncWriteSpe(ID, 2, Speed, ACC, Torque);
      delay(1000);
      while(analogRead(Photo[9])<600);
      myrobot.stop();
      break;
    case 3:
      
      break;
    default:
      switch (black)
      {
        case 1:
        Speed[0]=40;
        Speed[1]=-40;
        hlscl.SyncWriteSpe(ID, 2, Speed, ACC, Torque);
        delay(700);
        myrobot.stop();
        Speed[0]=80;
        Speed[1]=50;
        delay(500);
        
        hlscl.SyncWriteSpe(ID, 2, Speed, ACC, Torque);
        while(analogRead(Photo[10])<650);
        
        myrobot.stop();
        break;
      case 2:
        Speed[0]=40;
        Speed[1]=-40;
        hlscl.SyncWriteSpe(ID, 2, Speed, ACC, Torque);
        delay(600);

        Speed[0]=-50;
        Speed[1]=-80;
        hlscl.SyncWriteSpe(ID, 2, Speed, ACC, Torque);
        while(analogRead(Photo[9])<600);
        myrobot.stop();

        break;
      case 3:
        Speed[0]=40;
        Speed[1]=-40;
        hlscl.SyncWriteSpe(ID, 2, Speed, ACC, Torque);
        delay(600);
        myrobot.stop();
        break;

      default:
        break;
      }
      break;
    }
    myrobot.LEDstate(forLib::A,forLib::OFF);
  }

  if(MyToF.dataReady()==true){
    uint16_t l=0;
    l=MyToF.read(false);
    if(l<100){
      myrobot.stop();
      myrobot.ToFSelect(ToFleft);
      while(analogRead(Photo[10])<650){

        while (MyToF.dataReady()==true);
        l=MyToF.read(false);

        if(l<100){
          s16 _Speed[2]={60,-50};
          hlscl.SyncWriteSpe(ID, 2, _Speed, ACC, Torque);
          myrobot.LEDstate(forLib::A,forLib::ON);
        }else{
          s16 _Speed[2]={5,-50};
          hlscl.SyncWriteSpe(ID, 2, _Speed, ACC, Torque);
          myrobot.LEDstate(forLib::A,forLib::OFF);
        }
      }
    }
    
  }
  //myrobot.turn(30,2500);
  //delay(1000);
  
  /*if (myIMU.wasReset()) {
    setReports();
  }

  // Has a new event come in on the Sensor Hub Bus?
  if (myIMU.getSensorEvent() == true) {

    // is it the correct sensor data we want?
    if (myIMU.getSensorEventID() == SENSOR_REPORTID_ROTATION_VECTOR) {

      float roll = (myIMU.getRoll()) * 180.0 / PI;    // Convert roll to degrees
      float pitch = (myIMU.getPitch()) * 180.0 / PI;  // Convert pitch to degrees
      float yaw = (myIMU.getYaw()) * 180.0 / PI;      // Convert yaw / heading to degrees
      if (yaw >= 100) {
        digitalWrite(LED[1], HIGH);
      }else{
        digitalWrite(LED[1], LOW);
      }
    }
  }*/
}
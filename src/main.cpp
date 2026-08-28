#include <Arduino.h>
#include <forlib.h>
#include <Color.h>
#include <HLSCL.h>
#include <Wire.h>
#include <VL53L1X.h>
#include <Adafruit_NeoPixel.h>

#define velocity 40
#define ToFadd 2

forLib myrobot;

void setReports();

void setup() {
  myrobot.begin();
  hlscl.SyncWriteSpe(ID, 2, Speed, ACC, Torque);
  delay(1000);
  myrobot.ToFSelect(ToFadd);
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
  /*int _R_,_G_,_B_;
  S9706.out_ratio(_R_,_G_,_B_,0,true);
  if(S9706.compare_ratio(25,50,25,0,false)){
    myrobot.LEDstate(forLib::B,forLib::ON);
  }else{
    myrobot.LEDstate(forLib::B,forLib::OFF);
  }
  if(S9706.compare_ratio(25,50,25,0,true)){
    myrobot.LEDstate(forLib::B,forLib::ON);
  }else{
    myrobot.LEDstate(forLib::B,forLib::OFF);
  }*/


  double p = myrobot.Photoformula()*0.5;
  s16 TempS[2];
  TempS[0] = s16(p + 40);
  TempS[1] = s16(p - 40);
  /*MySerial2.print(p);
  MySerial2.print(":");
  MySerial2.print(TempS[0]);
  MySerial2.print(":");
  MySerial2.println(TempS[1]);
  delay(500);*/
  hlscl.SyncWriteSpe(ID, 2, TempS, ACC, Torque);

  /*uint16_t l=0;
  if(MyToF.dataReady()==true){
    l=MyToF.read(false);
    if(l<100){
      s16 _Speed[2]={60,-50};
      hlscl.SyncWriteSpe(ID, 2, _Speed, ACC, Torque);
      myrobot.LEDstate(1,HIGH);
    }else{
      s16 _Speed[2]={5,-50};
      hlscl.SyncWriteSpe(ID, 2, _Speed, ACC, Torque);
      myrobot.LEDstate(1,LOW);
    }
  }*/
  //myrobot.turn(30,2500);
  //delay(1000);
  

  //if(analogRead(Photo[0])>500||analogRead(Photo[1])>500||analogRead(Photo[18])>500||analogRead(Photo[19])>500){
    //myrobot.stop();
  //}
  
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
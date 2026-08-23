#include <Arduino.h>
#include <forlib.h>
#include <Color.h>
#include <HLSCL.h>
#include <Wire.h>
#include <VL53L1X.h>

#define BNO08X_ADDR 0x4B

const float gain[20] = { 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, -2, -3, 0, 0, 0, 0, 0, 0, 0, 0 };
//
//BNO08x myIMU;
//
forLib myrobot;
float D=0;

void setup() {
  myrobot.begin();
  //Wire.setClock(400000);
  /*if (myIMU.begin(BNO08X_ADDR, Wire, PC8, PC7) == false) {
    digitalWrite(LED[3],HIGH);
  }
  myIMU.enableRotationVector(50);
  delay(1000);*/

}

/*void setReports(void) {
  if (myIMU.enableRotationVector() == true) {
    digitalWrite(LED[2], HIGH);
  }
}*/

void loop() {
  double p = myrobot.Photoformula()*0.5;
  Speed[0] = 40 + p;
  Speed[1] = -40 + p;
  hlscl.SyncWriteSpe(ID, 2, Speed, ACC, Torque);

  
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
      if (roll >= 180) {
        digitalWrite(LED[1], HIGH);
      }
    }
  }*/
}
/*int readColor(int colorselect) {
  int result = 0;
  for (int i = 0; i < 12; i++) {
    digitalWrite(Color[colorselect][CK], HIGH);
    delayMicroseconds(1);
    result |= (digitalRead(Color[colorselect][DOUT]) << i);
    digitalWrite(Color[colorselect][CK], LOW);
    delayMicroseconds(1);
  }
  delayMicroseconds(3);
  return result;
}*/
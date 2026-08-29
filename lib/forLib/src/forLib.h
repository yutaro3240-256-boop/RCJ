#ifndef forLib_H  // 二重読み込み防止（インクルードガード）
#define forLib_H
#include <Color.h>
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <VL53L1X.h>
#include <HLSCL.h>
#include <SparkFun_BNO08x_Arduino_Library.h>


#define G_BOOT PC6 
#define G_RST  PC7 
#define G_INIT  PC8 
#define MULTI_SDA  PB7 
#define MULTI_SCA  PB8 
#define TCA9548A_ADDR  0x70 
#define TG  50 
#define PhotoLED PB12 
#define Lo 0
#define TCAADDR 0x70
#define BNO08X_ADDR 0x4A

static constexpr int Photo[21] = { PF12, PF11, PB1, PB0, PC5, PC4, PA7, PA6, PA5, PA4, PA3, PA2, PA1, PA0, PC1, PC0, PF10, PF9, PF8, PF7, PE9 };//フォトリフレクタ
static constexpr double Photogain[20] = { 0, 0, 0.8, 0.7, 0.6, 0.5, 0.4 ,0.3 ,0.2 , 0.1, -0.1, -0.2, -0.3, -0.4, -0.5, -0.6, -0.67, -0.75, 0, 0 };
static constexpr int LED[4] = { PD12, PD13, PD14, PD15 };

extern byte ID[2];
extern s16 Speed[2];
extern byte ACC[2];
extern u16 Torque[2];

extern Color S9706;
extern Adafruit_NeoPixel pixels;
extern VL53L1X MyToF;
extern HLSCL hlscl;
extern HardwareSerial motor;
extern HardwareSerial MySerial2;
extern TwoWire ToF_Wire;
extern TwoWire Wire3;
extern BNO08x myIMU;


class forLib {
  public:
    enum _LED{
      A=GPIO_PIN_12,
      B=GPIO_PIN_13,
      C=GPIO_PIN_14,
      D=GPIO_PIN_15
    };
    enum _STATE{
      ON=0,
      OFF=16
    };
    void begin();
    void LEDstate(forLib::_LED pin, _STATE state);
    void ToFSelect(uint8_t _pin);
    void turn(s16 _speed,long t);
    void stop();
    double Photoformula();
    
  private:
  
};


#endif
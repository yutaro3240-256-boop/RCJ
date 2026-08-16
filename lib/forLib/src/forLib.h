#ifndef forLib_H  // 二重読み込み防止（インクルードガード）
#define forLib_H
#include <Color.h>
#include <Arduino.h>

 #define G_BOOT PC6 
 #define G_RST  PC7 
 #define G_INIT  PC8 
 #define MULTI_SDA  PB7 
 #define MULTI_SCA  PB8 
 #define TCA9548A_ADDR  0x70 
 #define TG  50 
 #define PhotoLED PB12 
 #define Lo 0
 static constexpr int Photo[21] = { PF12, PF11, PB1, PB0, PC5, PC4, PA7, PA6, PA5, PA4, PA3, PA2, PA1, PA0, PC1, PC0, PF10, PF9, PF8, PF7, PE9 };//フォトリフレクタ
 static constexpr float Photogain[20] = { 10, 9, 8, 7, 6, 5, 4,0.3,0.2, 0.1, -0.1, -0.2, -0.3, -4, -5, -6, -7, -8, -9, -10 };
 static constexpr int LED[4] = { PD12, PD13, PD14, PD15 };
extern Color S9706;
class forLib {
  public:
    void begin();
    void LEDstate(int pin, int state);

    int Photoformula();

  private:
  
};


#endif
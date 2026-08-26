#ifndef Color_H  // 二重読み込み防止（include guard）
#define Color_H
#include <Arduino.h>

#ifndef maxsensors
#define maxsensors 4
#endif

enum class State{
    IDLE,
    MEASURING,
    COMPLETE
};

enum class Color_name{
   RED,
   BLUE,
   GREEN,
   YELLOW,
   WHITE,
   BLACK
};

struct Sensor {
    uint8_t gate;
    uint8_t ck;
    uint8_t range;
    uint8_t dout;

    uint16_t R;
    uint16_t G;
    uint16_t B;
};

struct RGB{
   uint16_t r=0;
   uint16_t g=0;
   uint16_t b=0;
};

typedef enum {
   GATE_PIN,
   CK_PIN,
   RANGE_PIN,
   DOUT_PIN
}PINSTATE;

 class Color{
   public:

      bool begin(
         uint8_t _gate,
         uint8_t _ck,
         uint8_t _range,
         uint8_t _dout);
      
      bool erase(int _ID=0);
      bool eraseall();
      void setIntegrationTime(uint16_t t);

      bool read(int _ID=0);
      bool read_average(int count,int _ID=0);
      void readall();
      void read_averageall(int count);

      bool out(int &_R_,int &_G_,int &_B_,int _ID=0,bool _read=false);
      bool out_ratio(int &_R_,int &_G_,int &_B_,int _ID=0,bool _read=false);
      
      bool compare(int _R_,int _G_,int _B_,int _ID=0,bool _read=false);
      void setcompareRange(uint8_t _range_);
      bool compare_ratio(int _R_,int _G_,int _B_,int _ID=0,bool _read=false);
      void setcompareRange_ratio(uint8_t _range_);

      RGB get(uint8_t _ID=0, bool _read=false);
      RGB get_average(int count,uint8_t _ID=0);
      void getall(RGB _rgb[],bool _read=false);
      void get_averageall(int count,RGB _rgb[]);

      bool getcompare(RGB _rgb,uint8_t _ID=0,bool _read=false);
      

      uint8_t sensorCount();

      uint16_t getBrightness(int _ID=0,bool _read=false);

      bool startall();
      void update();
      bool available();
      bool finishall();

   private:

      void set(int _ID);
      void setall();
      
      uint16_t readADC(int _ID);
      
      bool compared(uint16_t _compared,uint16_t _compare,uint16_t _range);

      uint16_t _TG=50;
      uint8_t _comparerange=20;
      uint8_t _comparerange_ratio=10;

      uint8_t ID=0;

      struct RGB_average{
         uint32_t r=0;
         uint32_t g=0;
         uint32_t b=0;
      };

      Sensor sensors[maxsensors];
      State state=State::IDLE;
      uint32_t startTime=0;
 };

#endif
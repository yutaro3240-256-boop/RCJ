#include "Color.h"

bool Color::begin(uint8_t _gate,uint8_t _ck,uint8_t _range,uint8_t _dout){  //カラセン設定
    
    if(ID>=maxsensors){
        return false;
    }
    if(state!=State::IDLE){
        return false;
    }
    sensors[ID].gate=_gate;
    sensors[ID].ck=_ck;
    sensors[ID].range=_range;
    sensors[ID].dout=_dout;

    pinMode(sensors[ID].ck, OUTPUT);
    pinMode(sensors[ID].gate, OUTPUT);
    pinMode(sensors[ID].range, OUTPUT);
    pinMode(sensors[ID].dout, INPUT);
    
    ID++;
    return true;
}

bool Color::erase(int _ID){
    
    if(_ID>ID){
        return false;
    }

    if(state!=State::IDLE){
        return false;
    }

    for(int i=_ID; i<ID; i++){
       
        sensors[i].gate=sensors[i+1].gate;
        sensors[i].ck=sensors[i+1].ck;
        sensors[i].dout=sensors[i+1].dout;
        sensors[i].range=sensors[i+1].range;
    
        sensors[i].R=sensors[i+1].R;
        sensors[i].G=sensors[i+1].G;
        sensors[i].B=sensors[i+1].B;

    }
    sensors[ID-1].gate=0;
    sensors[ID-1].ck=0;
    sensors[ID-1].dout=0;
    sensors[ID-1].range=0;
    
    sensors[ID-1].R=0;
    sensors[ID-1].G=0;
    sensors[ID-1].B=0;

    ID--;
    return true;

}

bool Color::eraseall(){
    
    if(ID==0){
        return false;
    }

    if(state!=State::IDLE){
        return false;
    }

    for(int i=0; i<ID; i++){
        sensors[i].gate=0;
        sensors[i].ck=0;
        sensors[i].dout=0;
        sensors[i].range=0;
    
        sensors[i].R=0;
        sensors[i].G=0;
        sensors[i].B=0;
    }
    ID=0;
    return true;
}

void Color::setIntegrationTime(uint16_t t){
    if(state!=State::IDLE){
        return;
    }
    _TG=t;
}

void Color::set(int _ID){
    if(_ID >= ID){
        return;
    }
    
    if(state!=State::IDLE){
        return;
    }
    digitalWrite(sensors[_ID].gate, LOW);
    digitalWrite(sensors[_ID].ck, LOW);
    delayMicroseconds(2000);

    // 感度設定
    digitalWrite(sensors[_ID].range, HIGH);

    // 光量の積算を開始
    digitalWrite(sensors[_ID].gate, HIGH);
  
    delay(_TG + 1); // 積分時間だけ待つ

    // 光量の積算を終了
    digitalWrite(sensors[_ID].gate, LOW);
    delayMicroseconds(4); 
}

void Color::setall(){

    if(state!=State::IDLE){
        return;
    }

    for(int i=0; i<ID; i++){
        digitalWrite(sensors[i].gate, LOW);
        digitalWrite(sensors[i].ck, LOW);
    }
    delayMicroseconds(2000);

    for(int i=0; i<ID; i++){
        // 感度設定
        digitalWrite(sensors[i].range, HIGH);

        // 光量の積算を開始
        digitalWrite(sensors[i].gate, HIGH);
    }
    delay(_TG + 1); // 積分時間だけ待つ

    // 光量の積算を終了
    for(int i=0; i<ID; i++){
        digitalWrite(sensors[i].gate, LOW);
    }
    
    delayMicroseconds(4); 
    
}

uint16_t Color::readADC(int _ID){
    if(_ID >= ID){
        return 0;
    }
    u_int16_t result = 0;
    
    for (int i = 0; i < 12; i++) {
        digitalWrite(sensors[_ID].ck, HIGH);
        delayMicroseconds(1);
        result |= (digitalRead(sensors[_ID].dout) << i);
        digitalWrite(sensors[_ID].ck, LOW);
        delayMicroseconds(1);
    }
    
    delayMicroseconds(3);
    return result;
}

bool Color::read(int _ID){
    if(state!=State::IDLE){
        return false;
    }
    if(_ID >= ID){
        return false;
    }
    this->set(_ID);

    sensors[_ID].R=this->readADC(_ID);
    sensors[_ID].G=this->readADC(_ID);
    sensors[_ID].B=this->readADC(_ID);

    digitalWrite(sensors[_ID].gate, HIGH);
    return true;
}

bool Color::read_average(int count,int _ID){
    if(state!=State::IDLE){
        return false;
    }
    if(count==0){
        return false;
    }
    if(_ID >= ID){
        return false;
    }
    RGB_average s_rgb;
    
    for(int i=0; i<count; i++){
        RGB _rgb=get(_ID,true);
        
        s_rgb.r+=_rgb.r;
        s_rgb.g+=_rgb.g;
        s_rgb.b+=_rgb.b;
        
    }
    
    sensors[_ID].R=s_rgb.r/count;
    sensors[_ID].G=s_rgb.g/count;
    sensors[_ID].B=s_rgb.b/count;
    return true;
}

void Color::readall(){
    if(state!=State::IDLE){
        return;
    }
    this->setall();
    
    for(int i = 0; i < ID; i++){

        sensors[i].R=this->readADC(i);
        sensors[i].G=this->readADC(i);
        sensors[i].B=this->readADC(i);

        digitalWrite(sensors[i].gate, HIGH);
    }
}

void Color::read_averageall(int count){
    if(state!=State::IDLE){
        return;
    }
    if(count==0){
        return;
    }

    RGB_average s_rgb[maxsensors];
    
    for(int i=0; i<count; i++){
        this->readall();
        for (int j = 0; j < ID; j++){
            s_rgb[j].r += sensors[j].R;
            s_rgb[j].g += sensors[j].G;
            s_rgb[j].b += sensors[j].B;
        }
    }

    for (int i = 0; i < ID; i++){
        sensors[i].R=s_rgb[i].r/count;
        sensors[i].G=s_rgb[i].g/count;
        sensors[i].B=s_rgb[i].b/count;
    }
}

bool Color::out(int &_R_,int &_G_,int &_B_,int _ID,bool _read){
    if(_ID >= ID){
        return false;
    }
    if(_read){
        this->read(_ID);
    }
    
    _R_=sensors[_ID].R;
    _G_=sensors[_ID].G;
    _B_=sensors[_ID].B;
    return true;
}

bool Color::compare(int _R_,int _G_,int _B_,int _ID,bool _read){
    if(_ID >= ID){
        return false;
    }
    RGB rgb=this->get(_ID,_read);

    if(this->compared(rgb.r,_R_,_comparerange)&&this->compared(rgb.b,_B_,_comparerange)&&this->compared(rgb.g,_G_,_comparerange)){
        return true;
    }else{
        return false;
    }
}

void Color::setcompareRange(uint8_t _range_){
    _comparerange=_range_;
}

bool Color::out_ratio(int &_R_,int &_G_,int &_B_,int _ID, bool _read){
    if(_ID >= ID){
        return false;
    }
    uint16_t sum=this->getBrightness(_ID, _read);
    if(sum == 0){
    _R_ = _G_ = _B_ = 0;
    return false;
    }
    _R_=sensors[_ID].R*100/sum;
    _G_=sensors[_ID].G*100/sum;
    _B_=sensors[_ID].B*100/sum;
    return true;
}

bool Color::compare_ratio(int _R_,int _G_,int _B_,int _ID,bool _read){
    if(_ID > ID){
        return false;
    }
    int r_R,r_G,r_B;

    this->out_ratio(r_R,r_G,r_B,_ID,_read);
    
    if(this->compared(r_R,_R_,_comparerange_ratio)&&this->compared(r_B,_B_,_comparerange_ratio)&&this->compared(r_B,_B_,_comparerange_ratio)){
        return true;
    }else{
        return false;
    }
}

void Color::setcompareRange_ratio(uint8_t _range_){
    _comparerange_ratio=_range_;
}

uint16_t Color::getBrightness(int _ID, bool _read){
    if(_ID >= ID){
        return 0;
    }
    if(_read){
        this->read(_ID);
    }
    return sensors[_ID].R+sensors[_ID].G+sensors[_ID].B;
}

RGB Color::get(uint8_t _ID, bool _read){
    if(_ID >= ID){
        return {0, 0, 0};
    }
    if(_read){
        this->read(_ID);
    }
    return {
        sensors[_ID].R,
        sensors[_ID].G,
        sensors[_ID].B
    };
}

RGB Color::get_average(int count,uint8_t _ID){
    if(_ID >= ID){
        return {0, 0, 0};
    }
    this->read_average(count,_ID);
    return get(_ID);
}

void Color::getall(RGB _rgb[], bool _read){
    for(int i=0;i<ID;i++){
        _rgb[i]=get(i,_read);
    }
}

void Color::get_averageall(int count,RGB _rgb[]){
    for(int i=0;i<ID;i++){
        _rgb[i]=get_average(count,i);
    }
}

bool Color::getcompare(RGB _rgb,u_int8_t _ID,bool _read){
    return this->compare(_rgb.r,_rgb.g,_rgb.b,_ID,_read);
}

uint8_t Color::sensorCount(){
    return ID;
}

bool Color::startall(){
    if(state!=State::IDLE){
        return false;
    }
    state=State::MEASURING;
    for(int i=0; i<ID; i++){
        digitalWrite(sensors[i].gate, LOW);
        digitalWrite(sensors[i].ck, LOW);
    }
    delayMicroseconds(2000);

    for(int i=0; i<ID; i++){
        // 感度設定
        digitalWrite(sensors[i].range, HIGH);

        // 光量の積算を開始
        digitalWrite(sensors[i].gate, HIGH);
    }
    startTime=millis();
    return true;
}

void Color::update(){
    
    switch(state){
    case State::IDLE:
        break;

    case State::MEASURING:
        if(millis()-startTime>=_TG){
            state = State::COMPLETE;
            for(int i=0; i<ID; i++){
                // 光量の積算を終了
                digitalWrite(sensors[i].gate, LOW);
            }
            delayMicroseconds(4); 
        }
        break;

    case State::COMPLETE:
        break;
    }
}

bool Color::available(){
    return state==State::COMPLETE;
}

bool Color::finishall(){
    if(state!=State::COMPLETE){
        return false;
    }
    for(int i = 0; i < ID; i++){

        sensors[i].R=this->readADC(i);
        sensors[i].G=this->readADC(i);
        sensors[i].B=this->readADC(i);

        digitalWrite(sensors[i].gate, HIGH);
    }
    state = State::IDLE;
    return true;
}

bool Color::compared(uint8_t _compared,uint8_t _compare,uint8_t _range){
    return _compared*-1>=_compare-_range&&_compared<=_compare-_range;
}
/*
 * HLSCL.h
 * HLSシリーズシリアルサーボアプリケーション層プログラム
 * 日期: 2024.11.21
 * 作者: txl
 */

#ifndef _HLSCL_H
#define _HLSCL_H

//メモリテーブル定義
//-------EPROM(読み取り専用)--------
#define HLSCL_MODEL_L 3
#define HLSCL_MODEL_H 4

//-------EPROM(読み書き)--------
#define HLSCL_ID 5
#define HLSCL_BAUD_RATE 6
#define HLSCL_SECOND_ID 7
#define HLSCL_MIN_ANGLE_LIMIT_L 9
#define HLSCL_MIN_ANGLE_LIMIT_H 10
#define HLSCL_MAX_ANGLE_LIMIT_L 11
#define HLSCL_MAX_ANGLE_LIMIT_H 12
#define HLSCL_CW_DEAD 26
#define HLSCL_CCW_DEAD 27
#define HLSCL_OFS_L 31
#define HLSCL_OFS_H 32
#define HLSCL_MODE 33

//-------SRAM(読み書き)--------
#define HLSCL_TORQUE_ENABLE 40
#define HLSCL_ACC 41
#define HLSCL_GOAL_POSITION_L 42
#define HLSCL_GOAL_POSITION_H 43
#define HLSCL_GOAL_TORQUE_L 44
#define HLSCL_GOAL_TORQUE_H 45
#define HLSCL_GOAL_SPEED_L 46
#define HLSCL_GOAL_SPEED_H 47
#define HLSCL_TORQUE_LIMIT_L 48
#define HLSCL_TORQUE_LIMIT_H 49
#define HLSCL_LOCK 55

//-------SRAM(読み取り専用)--------aaa
#define HLSCL_PRESENT_POSITION_L 56
#define HLSCL_PRESENT_POSITION_H 57
#define HLSCL_PRESENT_SPEED_L 58
#define HLSCL_PRESENT_SPEED_H 59
#define HLSCL_PRESENT_LOAD_L 60
#define HLSCL_PRESENT_LOAD_H 61
#define HLSCL_PRESENT_VOLTAGE 62
#define HLSCL_PRESENT_TEMPERATURE 63
#define HLSCL_MOVING 66
#define HLSCL_PRESENT_CURRENT_L 69
#define HLSCL_PRESENT_CURRENT_H 70


#include "SCSerial.h"

class HLSCL : public SCSerial
{
public:
	HLSCL();
	HLSCL(u8 End);
	HLSCL(u8 End, u8 Level);
	int WritePosEx(u8 ID, s16 Position, u16 Speed, u8 ACC = 0, u16 Torque = 0);//単一サーボの位置指令を通常書き込み
	int RegWritePosEx(u8 ID, s16 Position, u16 Speed, u8 ACC = 0, u16 Torque = 0);//単一サーボの位置指令を非同期で書き込む（RegWriteActionが有効）
	void SyncWritePosEx(u8 ID[], u8 IDN, s16 Position[], u16 Speed[], u8 ACC[], u16 Torque[]);//複数サーボの位置指令を同期で書き込む
	void SyncWriteSpe(u8 ID[], u8 IDN, s16 Speed[], u8 ACC[], u16 Torque[]);//複数サーボの速度指令を同期で書き込む
	int ServoMode(u8 ID);//Servoモードに設定
	int WheelMode(u8 ID);//定速モードに設定
	int EleMode(u8 ID);//定トルクモードに設定
	int WriteSpe(u8 ID, s16 Speed, u8 ACC = 0, u16 Torque = 0);//定速モード制御指令
	int WriteEle(u8 ID, s16 Torque);//定トルクモード制御指令
	int EnableTorque(u8 ID, u8 Enable);//トルク制御指令
	int unLockEprom(u8 ID);//epromロック解除
	int LockEprom(u8 ID);//epromロック
	int CalibrationOfs(u8 ID);//中立位置キャリブレーション
	int FeedBack(int ID);//サーボフィードバック情報
	int ReadPos(int ID);//位置読み取り
	int ReadSpeed(int ID);//速度読み取り
	int ReadLoad(int ID);//モーター出力電圧パーセンテージ読み取り(0～1000)
	int ReadVoltage(int ID);//電圧読み取り
	int ReadTemper(int ID);//温度読み取り
	int ReadMove(int ID);//動作状態読み取り
	int ReadCurrent(int ID);//電流読み取り
private:
	u8 Mem[HLSCL_PRESENT_CURRENT_H-HLSCL_PRESENT_POSITION_L+1];
};

#endif
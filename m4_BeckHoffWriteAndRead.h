#pragma once

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <sstream>
// ADS headers
#include "C:\TwinCAT\AdsApi\TcAdsDll\Include\TcAdsDef.h"
#include "C:\TwinCAT\AdsApi\TcAdsDll\Include\TcAdsApi.h"
using namespace std;

class m4_BeckHoffWriteAndRead
{
public:
	m4_BeckHoffWriteAndRead();
	~m4_BeckHoffWriteAndRead();

	void m4_BeckHoffInit();		//倍福初始化
	void m4_BeckHoff_ReadFangWei();		//读方位轴位置PLC变量，变量读写
	void m4_BeckHoff_WriteFangWei();	//写方位轴位置PLC变量，变量读写
	void m4_BeckHoff_ReadFuYang();		//读俯仰轴位置PLC变量，变量读写
	void m4_BeckHoff_WriteFuYang();		//写俯仰轴P位置LC变量，变量读写
	void m4_BeckHoff_FangWeiEnable();	//方位轴使能，变量读写
	void m4_BeckHoff_FuYangEnable();	//俯仰轴使能，变量读写
	void m4_BeckHoff_AxisMove();		//方位轴俯仰轴运动，变量读写
	void m4_BeckHoff_FileOpen();		//打开文件，变量读写
	void m4_BeckHoff_FileClose();		//关闭文件，变量读写
	void m4_BeckHoff_MoveToZero();		//回零位，变量读写
	void m4_BeckHoff_EncodeSetZero();	//码盘标零位
	void m4_BeckHoff_FuYangVelocity();	//俯仰轴速度
	void m4_BeckHoff_FangWeiVelocity();	//方位轴速度
	void m4_BeckHoff_MoveStop();		//方位轴俯仰轴运动停止
	/*
	void m4_BeckHoff_FangWeiVelocityControl();	//方位速度控制，速度指令，变量读写
	void m4_BeckHoff_FuYangVelocityControl();	//俯仰速度控制，速度指令，变量读写
	void m4_BeckHoff_FangWeiDirection();	//方位速度控制，方向，变量读写
	void m4_BeckHoff_FuYangDirection();		//俯仰速度控制，方向，变量读写
	void m4_BeckHoff_VelocityMove();	//速度控制，运动指令，变量读写
	*/
	/*
	void m4_BeckHoff_ReadFangWeiVelocity();	//读方位轴速度
	void m4_BeckHoff_ReadFuYangVelocity();	//读俯仰轴速度
	*/
	void m4_BeckHoff_ArrayRead();	//读俯仰轴速度
	void m4_BeckHoff_WriteArray();

	// 功能函数
	void m4_BeckHoff_Function_MoveToZero();		//回零位
	void m4_BeckHoff_Function_EncodeSetZero();	//码盘标零位
	void m4_BeckHoff_Function_AxisMove();		//方位轴俯仰轴运动
	void m4_BeckHoff_Function_MoveStop();		//方位轴俯仰轴运动停止
	void m4_BeckHoff_Function_VelocityControlMove();	//速度控制的运动停止

public:
	long     nErr, nPort;
	AmsAddr  Addr;
	PAmsAddr pAddr = &Addr;
	//DWORD    dwData, dwData1;
	FLOAT m4_FangWeiWrite, m4_FangWeiRead, m4_FuYangWrite, m4_FuYangRead, m4_FuYangVelocity, m4_FangWeiVelocity,
		m4_VelocityFYC, m4_VelocityFWC, m4_FangWeiReadVelocity, m4_FuYangReadVelocity;
	ULONG m4_FWEnable, m4_FYEable,m4_AxisMove,m4_FileOpen,m4_FileClose,m4_MoveToZero,m4_EncodeSetZero,m4_MoveStop,
		m4_DirectionFY_PN, m4_DirectionFW_PN, m4_VelocityMove;

	FLOAT m4_Array[5];
	FLOAT m4_ArrayRead[4];//读数据
};



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

	void m4_BeckHoffInit();		//������ʼ��
	void m4_BeckHoff_ReadFangWei();		//����λ��λ��PLC������������д
	void m4_BeckHoff_WriteFangWei();	//д��λ��λ��PLC������������д
	void m4_BeckHoff_ReadFuYang();		//��������λ��PLC������������д
	void m4_BeckHoff_WriteFuYang();		//д������Pλ��LC������������д
	void m4_BeckHoff_FangWeiEnable();	//��λ��ʹ�ܣ�������д
	void m4_BeckHoff_FuYangEnable();	//������ʹ�ܣ�������д
	void m4_BeckHoff_AxisMove();		//��λ�ḩ�����˶���������д
	void m4_BeckHoff_FileOpen();		//���ļ���������д
	void m4_BeckHoff_FileClose();		//�ر��ļ���������д
	void m4_BeckHoff_MoveToZero();		//����λ��������д
	void m4_BeckHoff_EncodeSetZero();	//���̱���λ
	void m4_BeckHoff_FuYangVelocity();	//�������ٶ�
	void m4_BeckHoff_FangWeiVelocity();	//��λ���ٶ�
	void m4_BeckHoff_MoveStop();		//��λ�ḩ�����˶�ֹͣ
	/*
	void m4_BeckHoff_FangWeiVelocityControl();	//��λ�ٶȿ��ƣ��ٶ�ָ�������д
	void m4_BeckHoff_FuYangVelocityControl();	//�����ٶȿ��ƣ��ٶ�ָ�������д
	void m4_BeckHoff_FangWeiDirection();	//��λ�ٶȿ��ƣ����򣬱�����д
	void m4_BeckHoff_FuYangDirection();		//�����ٶȿ��ƣ����򣬱�����д
	void m4_BeckHoff_VelocityMove();	//�ٶȿ��ƣ��˶�ָ�������д
	*/
	/*
	void m4_BeckHoff_ReadFangWeiVelocity();	//����λ���ٶ�
	void m4_BeckHoff_ReadFuYangVelocity();	//���������ٶ�
	*/
	void m4_BeckHoff_ArrayRead();	//���������ٶ�
	void m4_BeckHoff_WriteArray();

	// ���ܺ���
	void m4_BeckHoff_Function_MoveToZero();		//����λ
	void m4_BeckHoff_Function_EncodeSetZero();	//���̱���λ
	void m4_BeckHoff_Function_AxisMove();		//��λ�ḩ�����˶�
	void m4_BeckHoff_Function_MoveStop();		//��λ�ḩ�����˶�ֹͣ
	void m4_BeckHoff_Function_VelocityControlMove();	//�ٶȿ��Ƶ��˶�ֹͣ

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
	FLOAT m4_ArrayRead[4];//������
};



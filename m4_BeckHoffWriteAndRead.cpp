#include "m4_BeckHoffWriteAndRead.h"


m4_BeckHoffWriteAndRead::m4_BeckHoffWriteAndRead()
{
}


m4_BeckHoffWriteAndRead::~m4_BeckHoffWriteAndRead()
{
	nErr = AdsPortClose();
	if (nErr) cerr << "Error: AdsPortClose: " << nErr << '\n';
}


void m4_BeckHoffWriteAndRead::m4_BeckHoffInit()
{
	// Open communication port on the ADS router
	nPort = AdsPortOpen();

	pAddr->netId.b[0] = 5;
	pAddr->netId.b[1] = 50;
	pAddr->netId.b[2] = 68;
	pAddr->netId.b[3] = 82;
	pAddr->netId.b[4] = 1;
	pAddr->netId.b[5] = 1;

	//nErr = AdsGetLocalAddress(pAddr);
	//if (nErr)
	//{
	//	qDebug() << "Error: AdsGetLocalAddress: " << nErr << '\n';
	//}
	//	

	// TwinCAT2 PLC1 = 801
	pAddr->port = 851;
	m4_FWEnable = 0;
	m4_FYEable = 0;
	m4_AxisMove = 0;
	m4_FileOpen = 0;
	m4_FileClose = 0;
	m4_MoveToZero = 0;
	m4_EncodeSetZero = 0;
	m4_MoveStop = 0;

	//m4_DirectionFY_PN = 1;
	//m4_DirectionFW_PN = 1;
	//m4_VelocityFYC = 0.0;
	//m4_VelocityFWC = 0.0;
	//m4_VelocityMove = 0;
	m4_Array[0] = 1;	//m4_DirectionFY_PN
	m4_Array[1] = 1;	//m4_DirectionFW_PN
	m4_Array[2] = 0.0;	//m4_VelocityFYC
	m4_Array[3] = 0.0;	//m4_VelocityFWC
	m4_Array[4] = 1;	//m4_VelocityMove
	cout << "BeckHoff init....." << endl;
}

void m4_BeckHoffWriteAndRead::m4_BeckHoff_WriteArray()
{
	// Write value to MD14
	nErr = AdsSyncWriteReq(pAddr, 0x4020, 0x38, 0x14, &m4_Array);
	if (nErr) cerr << "Error: AdsSyncWriteReq: " << nErr << '\n';
}


void m4_BeckHoffWriteAndRead::m4_BeckHoff_ArrayRead()
{
	// Read value to MD19
	nErr = AdsSyncReadReq(pAddr, 0x4020, 0x4c, 0x10, &m4_ArrayRead);
	if (nErr) cerr << "Error: AdsSyncReadReq: " << nErr << '\n';
}

/*
void m4_BeckHoffWriteAndRead::m4_BeckHoff_ReadFangWeiVelocity()	//读方位轴速度
{
	// Read value to MD19
	nErr = AdsSyncReadReq(pAddr, 0x4020, 0x4c, 0x4, &m4_FangWeiReadVelocity);
	if (nErr) cerr << "Error: AdsSyncReadReq: " << nErr << '\n';
}

void m4_BeckHoffWriteAndRead::m4_BeckHoff_ReadFuYangVelocity()	//读俯仰轴速度
{
	// Read value to MD20
	nErr = AdsSyncReadReq(pAddr, 0x4020, 0x50, 0x4, &m4_FuYangReadVelocity);
	if (nErr) cerr << "Error: AdsSyncReadReq: " << nErr << '\n';
}
*/

void m4_BeckHoffWriteAndRead::m4_BeckHoff_ReadFangWei()
{
	// Read value to MD2
	nErr = AdsSyncReadReq(pAddr, 0x4020, 0x8, 0x4, &m4_FangWeiRead);
	if (nErr) cerr << "Error: AdsSyncReadReq: " << nErr << '\n';
}

void m4_BeckHoffWriteAndRead::m4_BeckHoff_WriteFangWei()
{
	// Write value to MD0
	nErr = AdsSyncWriteReq(pAddr, 0x4020, 0x0, 0x4, &m4_FangWeiWrite);
	if (nErr) cerr << "Error: AdsSyncWriteReq: " << nErr << '\n';
}

void m4_BeckHoffWriteAndRead::m4_BeckHoff_ReadFuYang()
{
	// Read value to MD3
	nErr = AdsSyncReadReq(pAddr, 0x4020, 0xc, 0x4, &m4_FuYangRead);
	if (nErr) cerr << "Error: AdsSyncReadReq: " << nErr << '\n';
}
void m4_BeckHoffWriteAndRead::m4_BeckHoff_WriteFuYang()
{
	// Write value to MD1
	nErr = AdsSyncWriteReq(pAddr, 0x4020, 0x4, 0x4, &m4_FuYangWrite);
	if (nErr) cerr << "Error: AdsSyncWriteReq: " << nErr << '\n';
}

void m4_BeckHoffWriteAndRead::m4_BeckHoff_FangWeiEnable()
{
	// Write value to MD5
	nErr = AdsSyncWriteReq(pAddr, 0x4020, 0x14, 0x4, &m4_FWEnable);
	//if (nErr)
	//{
	//	qDebug() << "Error: AdsSyncWriteReq: " << nErr << '\n';
	//}
	if (nErr) cerr << "Error: AdsSyncWriteReq: " << nErr << '\n';
}

void m4_BeckHoffWriteAndRead::m4_BeckHoff_FuYangEnable()
{
	// Write value to MD4
	nErr = AdsSyncWriteReq(pAddr, 0x4020, 0x10, 0x4, &m4_FYEable);
	//if (nErr)
	//{
	//	qDebug() << "Error: AdsSyncWriteReq: " << nErr << '\n';
	//}
	if (nErr) cerr << "Error: AdsSyncWriteReq: " << nErr << '\n';
}

void m4_BeckHoffWriteAndRead::m4_BeckHoff_AxisMove()
{
	// Write value to MD6
	nErr = AdsSyncWriteReq(pAddr, 0x4020, 0x18, 0x4, &m4_AxisMove);
	if (nErr) cerr << "Error: AdsSyncWriteReq: " << nErr << '\n';
}

void m4_BeckHoffWriteAndRead::m4_BeckHoff_FileOpen()
{
	// Write value to MD7
	nErr = AdsSyncWriteReq(pAddr, 0x4020, 0x1C, 0x4, &m4_FileOpen);
	if (nErr) cerr << "Error: AdsSyncWriteReq: " << nErr << '\n';
}

void m4_BeckHoffWriteAndRead::m4_BeckHoff_FileClose()
{
	// Write value to MD8
	nErr = AdsSyncWriteReq(pAddr, 0x4020, 0x20, 0x4, &m4_FileClose);
	if (nErr) cerr << "Error: AdsSyncWriteReq: " << nErr << '\n';
}


//回零位
void m4_BeckHoffWriteAndRead::m4_BeckHoff_MoveToZero()
{
	// Write value to MD9
	nErr = AdsSyncWriteReq(pAddr, 0x4020, 0x24, 0x4, &m4_MoveToZero);
	if (nErr) cerr << "Error: AdsSyncWriteReq: " << nErr << '\n';
}

//码盘标零位
void m4_BeckHoffWriteAndRead::m4_BeckHoff_EncodeSetZero()
{
	// Write value to MD10
	nErr = AdsSyncWriteReq(pAddr, 0x4020, 0x28, 0x4, &m4_EncodeSetZero);
	if (nErr) cerr << "Error: AdsSyncWriteReq: " << nErr << '\n';
}

//俯仰轴速度
void m4_BeckHoffWriteAndRead::m4_BeckHoff_FuYangVelocity()
{
	// Write value to MD11
	nErr = AdsSyncWriteReq(pAddr, 0x4020, 0x2c, 0x4, &m4_FuYangVelocity);
	if (nErr) cerr << "Error: AdsSyncWriteReq: " << nErr << '\n';
}

//方位轴速度
void m4_BeckHoffWriteAndRead::m4_BeckHoff_FangWeiVelocity()
{
	// Write value to MD12
	nErr = AdsSyncWriteReq(pAddr, 0x4020, 0x30, 0x4, &m4_FangWeiVelocity);
	if (nErr) cerr << "Error: AdsSyncWriteReq: " << nErr << '\n';
}

//方位轴俯仰轴运动停止
void m4_BeckHoffWriteAndRead::m4_BeckHoff_MoveStop()
{
	// Write value to MD13
	nErr = AdsSyncWriteReq(pAddr, 0x4020, 0x34, 0x4, &m4_MoveStop);
	if (nErr) cerr << "Error: AdsSyncWriteReq: " << nErr << '\n';
}





/*
//方位速度控制，速度指令，变量读写
void m4_BeckHoffWriteAndRead::m4_BeckHoff_FangWeiVelocityControl()
{
	// Write value to MD17
	nErr = AdsSyncWriteReq(pAddr, 0x4020, 0x44, 0x4, &m4_VelocityFWC);
	if (nErr) cerr << "Error: AdsSyncWriteReq: " << nErr << '\n';
}

//俯仰速度控制，速度指令，变量读写
void m4_BeckHoffWriteAndRead::m4_BeckHoff_FuYangVelocityControl()
{
	// Write value to MD16
	nErr = AdsSyncWriteReq(pAddr, 0x4020, 0x40, 0x4, &m4_VelocityFYC);
	if (nErr) cerr << "Error: AdsSyncWriteReq: " << nErr << '\n';
}
//方位速度控制，方向，变量读写
void m4_BeckHoffWriteAndRead::m4_BeckHoff_FangWeiDirection()
{
	// Write value to MD15
	nErr = AdsSyncWriteReq(pAddr, 0x4020, 0x3c, 0x4, &m4_DirectionFW_PN);
	if (nErr) cerr << "Error: AdsSyncWriteReq: " << nErr << '\n';
}
//俯仰速度控制，方向，变量读写
void m4_BeckHoffWriteAndRead::m4_BeckHoff_FuYangDirection()
{
	// Write value to MD14
	nErr = AdsSyncWriteReq(pAddr, 0x4020, 0x38, 0x4, &m4_DirectionFY_PN);
	if (nErr) cerr << "Error: AdsSyncWriteReq: " << nErr << '\n';
}

//速度控制，运动指令，变量读写
void m4_BeckHoffWriteAndRead::m4_BeckHoff_VelocityMove()
{
	// Write value to MD18
	nErr = AdsSyncWriteReq(pAddr, 0x4020, 0x48, 0x4, &m4_VelocityMove);
	if (nErr) cerr << "Error: AdsSyncWriteReq: " << nErr << '\n';
}
*/


// ******************************************************************************************
// *                                       功能函数                                         *
// ******************************************************************************************

//回零位
void m4_BeckHoffWriteAndRead::m4_BeckHoff_Function_MoveToZero()
{
	m4_MoveToZero = 0;
	m4_BeckHoff_MoveToZero();
	m4_MoveToZero = 1;
	m4_BeckHoff_MoveToZero();
}

//码盘标零位
void m4_BeckHoffWriteAndRead::m4_BeckHoff_Function_EncodeSetZero()
{
	m4_EncodeSetZero = 0;
	m4_BeckHoff_EncodeSetZero();
	m4_EncodeSetZero = 1;
	m4_BeckHoff_EncodeSetZero();
}
//方位轴俯仰轴运动
void m4_BeckHoffWriteAndRead::m4_BeckHoff_Function_AxisMove()
{
	m4_BeckHoff_WriteFangWei();
	m4_BeckHoff_WriteFuYang();
	m4_AxisMove = 0;
	m4_BeckHoff_AxisMove();
	m4_AxisMove = 1;
	m4_BeckHoff_AxisMove();
}

//方位轴俯仰轴运动停止
void m4_BeckHoffWriteAndRead::m4_BeckHoff_Function_MoveStop()
{
	m4_MoveStop = 0;
	m4_BeckHoff_MoveStop();
	m4_MoveStop = 1;
	m4_BeckHoff_MoveStop();
	//m4_MoveStop = 0;
	//m4_BeckHoff_MoveStop();
}

//速度控制的运动
void m4_BeckHoffWriteAndRead::m4_BeckHoff_Function_VelocityControlMove()
{
	//m4_BeckHoff_FuYangDirection();
	//m4_BeckHoff_FangWeiDirection();
	//m4_BeckHoff_FuYangVelocityControl();
	//m4_BeckHoff_FangWeiVelocityControl();
	//m4_VelocityMove = 0;
	//m4_BeckHoff_VelocityMove();
	//m4_VelocityMove = 1;
	//m4_BeckHoff_VelocityMove();
	m4_BeckHoff_WriteArray();
}
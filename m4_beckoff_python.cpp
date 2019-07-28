#include <iostream>
#include <sstream>
#include <Python.h>
#include <structmember.h>
#include "m4_BeckHoffWriteAndRead.h"
using namespace std;

m4_BeckHoffWriteAndRead m4_beckhoffClass;
// ��/�ṹ�Ķ���.
typedef struct _m4_beckhoff
{
	PyObject_HEAD      // == PyObject ob_base;  ����һ��PyObject����.
	char*  m_szName;
	float  m_dMath;
	float  m_dEnglish;
	int m4_FWEnable;
	int m4_FYEnable;
	float m4_FWDirection;
	float m4_FYDirection;
	float m4_FWVelocityWrite;
	float m4_FYVelocityWrite;
	float m4_FWVelocityRead;
	float m4_FYVelocityRead;

	float m4_FWPositionWrite;
	float m4_FYPositionWrite;
	float m4_FWPositionRead;
	float m4_FYPositionRead;


}m4_beckhoff;

static PyMemberDef m4_beckhoff_DataMembers[] =         //PyMemberDef�����Ա��˵���ṹ
{
	//�ַ�����m_szName�����ǵ�����Python�е����Ա��������ֲ�һ���ǵú�C++����Ӧ���Ա��������ͬ��
	//T_STRING��T_FLOAT�������Ա���������͵�˵��
	//offsetof����һ���꣬��STDDEF.h��
	//�ַ�����The �����������ǳ�Ա��DocString
	{ "m_szName", T_STRING, offsetof(m4_beckhoff, m_szName), 0, "The Name of instance" },
	{ "m_dMath", T_FLOAT, offsetof(m4_beckhoff, m_dMath), 0, "The Math score of instance." },
	{ "m_dEnglish", T_FLOAT, offsetof(m4_beckhoff, m_dEnglish), 0, "The English score of instance." },


	{ "m4_FWEnable", T_INT, offsetof(m4_beckhoff, m4_FWEnable), 0, "FW aixs flag" },
	{ "m4_FYEnable", T_INT, offsetof(m4_beckhoff, m4_FYEnable), 0, "FY aixs flag" },
	{ "m4_FWDirection", T_FLOAT, offsetof(m4_beckhoff, m4_FWDirection), 0, "FW aixs direction flag" },
	{ "m4_FYDirection", T_FLOAT, offsetof(m4_beckhoff, m4_FYDirection), 0, "FY aixs direction flag" },
	{ "m4_FWVelocityWrite", T_FLOAT, offsetof(m4_beckhoff, m4_FWVelocityWrite), 0, "FW aixs velocity write" },
	{ "m4_FYVelocityWrite", T_FLOAT, offsetof(m4_beckhoff, m4_FYVelocityWrite), 0, "FY aixs velocity write" },
	{ "m4_FWVelocityRead", T_FLOAT, offsetof(m4_beckhoff, m4_FWVelocityRead), 0, "FW aixs velocity read" },
	{ "m4_FYVelocityRead", T_FLOAT, offsetof(m4_beckhoff, m4_FYVelocityRead), 0, "FY aixs velocity read" },
	{ "m4_FWPositionRead", T_FLOAT, offsetof(m4_beckhoff, m4_FWPositionRead), 0, "FW aixs position read" },
	{ "m4_FYPositionRead", T_FLOAT, offsetof(m4_beckhoff, m4_FYPositionRead), 0, "FY aixs position read" },
	{ "m4_FWPositionWrite", T_FLOAT, offsetof(m4_beckhoff, m4_FWPositionWrite), 0, "FW aixs position write" },
	{ "m4_FYPositionWrite", T_FLOAT, offsetof(m4_beckhoff, m4_FYPositionWrite), 0, "FY aixs position write" },




	{ NULL, NULL, NULL, 0, NULL }
};


//�ڲ�����
// CScore����������á����췽��.
//���Կ�������ĳ�Ա������������һ����ף�static void MethodName(ClassType* Self, ��),��������з���ֵ�Ļ�����void�滻ΪPyobject*���ɡ����еĺ������Լ���㶨��
//���ڵ�һ������Self���Ǳ����еģ�������Python���෽������ʱ��selfһ������C++�е�thisָ��Ļ����ࡣ�������������������������е����ݳ�Ա��

static int m4_beckhoff_init(m4_beckhoff* Self, PyObject* pArgs)    //���췽��.
{
	const char* Name = 0;
	if (!PyArg_ParseTuple(pArgs, "sff", &Name, &Self->m_dMath, &Self->m_dEnglish))
	{
		cout << "Parse the argument FAILED! You should pass correct values!" << endl;
		return 0;
	}

	Self->m_szName = new char[strlen(Name) + 1];
	strcpy(Self->m_szName, Name);
	return 0;

}

static void m4_beckhoff_Destruct(m4_beckhoff* Self)                   //��������.
{
	if (Self->m_szName)
		delete[] Self->m_szName;              //���ͷ����ַ�ָ�����.

	//�������PyObject*��Ա�Ļ���Ҫһ���ͷ�֮.
	//�磺Py_XDECREF(Self->Member);
	Py_TYPE(Self)->tp_free((PyObject*)Self);      //�ͷŶ���/ʵ��.
}

static PyObject* m4_beckhoff_Str(m4_beckhoff* Self)             //����str/printʱ�Զ����ô˺���.
{
	ostringstream OStr;
	OStr << "Name    : " << Self->m_szName << endl
		<< "Math    : " << Self->m_dMath << endl
		<< "English : " << Self->m_dEnglish << endl;
	string Str = OStr.str();
	return Py_BuildValue("s", Str.c_str());
}

static PyObject* m4_beckhoff_Repr(m4_beckhoff* Self)            //����repr���ú���ʱ�Զ�����.
{
	return m4_beckhoff_Str(Self);
}

//�ⲿ����
// m4_beckhoff�������Get����.
//
static PyObject* m4_beckhoff_GetName(m4_beckhoff* Self)
{
	return Py_BuildValue("s", Self->m_szName);
}

static PyObject* m4_beckhoff_GetMath(m4_beckhoff* Self)
{
	return Py_BuildValue("f", Self->m_dMath);
}

static PyObject* m4_beckhoff_GetEnglish(m4_beckhoff* Self)
{
	return Py_BuildValue("f", Self->m_dEnglish);
}

static PyObject* m4_beckhoff_Init(m4_beckhoff* Self)
{
	m4_beckhoffClass.m4_BeckHoffInit();
	return Py_BuildValue("f", 1.0);
}

// ��ȡFWʹ�ܱ�־λ
static PyObject* m4_beckhoff_GetFWEnable(m4_beckhoff* Self)
{
	Self->m4_FWEnable = m4_beckhoffClass.m4_FWEnable;

	return Py_BuildValue("i", Self->m4_FWEnable);
}

// ��ȡFYʹ�ܱ�־λ
static PyObject* m4_beckhoff_GetFYEnable(m4_beckhoff* Self)
{
	Self->m4_FYEnable = m4_beckhoffClass.m4_FYEable;

	return Py_BuildValue("i", Self->m4_FYEnable);
}

// ��ȡ �������ٶ�����ת��־λ(1-��ת��3-��ת��
static PyObject* m4_beckhoff_GetFYDirection(m4_beckhoff* Self)
{
	Self->m4_FYDirection = m4_beckhoffClass.m4_Array[0];

	return Py_BuildValue("f", Self->m4_FYDirection);
}

// ��ȡ ��λ���ٶ�����ת��־λ(1-��ת��3-��ת��
static PyObject* m4_beckhoff_GetFWDirection(m4_beckhoff* Self)
{
	Self->m4_FWDirection = m4_beckhoffClass.m4_Array[1];

	return Py_BuildValue("f", Self->m4_FWDirection);
}

// ��ȡ �������ٶ�
static PyObject* m4_beckhoff_GetFYVelocity(m4_beckhoff* Self)
{
	Self->m4_FYVelocityRead = m4_beckhoffClass.m4_ArrayRead[3];

	return Py_BuildValue("f", Self->m4_FYVelocityRead);
}

// ��ȡ ��λ���ٶ�
static PyObject* m4_beckhoff_GetFWVelocity(m4_beckhoff* Self)
{
	Self->m4_FWVelocityRead = m4_beckhoffClass.m4_ArrayRead[2];

	return Py_BuildValue("f", Self->m4_FWVelocityRead);
}

// �ӻ�ȡ�������л�ȡ��λ����������ٶ� 
static PyObject* m4_beckhoff_GetVelocityFromController(m4_beckhoff* Self)
{
	m4_beckhoffClass.m4_BeckHoff_ArrayRead();

	return Py_BuildValue("f", 1.0);
}

// ��ȡ ������Ƕ�λ��
static PyObject* m4_beckhoff_GetFYPosition(m4_beckhoff* Self)
{
	Self->m4_FYPositionRead = m4_beckhoffClass.m4_FuYangRead;

	return Py_BuildValue("f", Self->m4_FYPositionRead);
}

// ��ȡ ��λ��Ƕ�λ��
static PyObject* m4_beckhoff_GetFWPosition(m4_beckhoff* Self)
{
	Self->m4_FWPositionRead = m4_beckhoffClass.m4_FangWeiRead;

	return Py_BuildValue("f", Self->m4_FWPositionRead);
}

// �ӿ������л�ȡ��λ��������ĽǶ�
static PyObject* m4_beckhoff_GetPositionFromController(m4_beckhoff* Self)
{
	m4_beckhoffClass.m4_BeckHoff_ReadFangWei();
	m4_beckhoffClass.m4_BeckHoff_ReadFuYang();
	return Py_BuildValue("f", 1.0);
}










////////////////////////////////////////////////////////////
// m4_beckhoff�������Set����.
static PyObject* m4_beckhoff_SetMath(m4_beckhoff* Self, PyObject* Argvs)
{
	Py_INCREF(Py_None);
	if (!PyArg_ParseTuple(Argvs, "f", &Self->m_dMath))
	{
		cout << "Parse the argument FAILED! You should pass correct values!" << endl;
		return Py_None;
	}

	return Py_None;
}

static PyObject* m4_beckhoff_SetEnglish(m4_beckhoff* Self, PyObject* Argvs)
{
	Py_INCREF(Py_None);
	if (!PyArg_ParseTuple(Argvs, "f", &Self->m_dEnglish))
	{
		cout << "Parse the argument FAILED! You should pass correct values!" << endl;
		return Py_None;
	}
	
	return Py_None;
}

// ����FWʹ�ܱ�־λ
static PyObject* m4_beckhoff_SetFWEnable(m4_beckhoff* Self, PyObject* Argvs)
{
	Py_INCREF(Py_None);

	if (!PyArg_ParseTuple(Argvs, "i", &Self->m4_FWEnable))
	{
		cout << "Parse the argument 'm4_FWEnable' FAILED! You should pass correct values!" << endl;
		return Py_None;
	}
	else
	{
		m4_beckhoffClass.m4_FWEnable = Self->m4_FWEnable;
	}
	return Py_None;
}

// ����FYʹ�ܱ�־λ
static PyObject* m4_beckhoff_SetFYEnable(m4_beckhoff* Self, PyObject* Argvs)
{
	Py_INCREF(Py_None);

	if (!PyArg_ParseTuple(Argvs, "i", &Self->m4_FYEnable))
	{
		cout << "Parse the argument 'm4_FYEnable' FAILED! You should pass correct values!" << endl;
		return Py_None;
	}
	else
	{
		m4_beckhoffClass.m4_FYEable = Self->m4_FYEnable;
	}
	return Py_None;
}

// ʹ�ܷ�λ��
static PyObject* m4_EnableFWAixs(m4_beckhoff* Self)
{
	m4_beckhoffClass.m4_BeckHoff_FangWeiEnable();

	return Py_BuildValue("f", 1.0);
}

// ʹ�ܸ�����
static PyObject* m4_EnableFYAixs(m4_beckhoff* Self)
{
	m4_beckhoffClass.m4_BeckHoff_FuYangEnable();

	return Py_BuildValue("f", 1.0);
}

// ���� �������ٶ�����ת(1-��ת��3-��ת��
static PyObject* m4_beckhoff_SetFYDirection(m4_beckhoff* Self, PyObject* Argvs)
{
	Py_INCREF(Py_None);

	if (!PyArg_ParseTuple(Argvs, "f", &Self->m4_FYDirection))
	{
		cout << "Parse the argument 'FYDirection' m4_FYEnable FAILED! You should pass correct values!" << endl;
		return Py_None;
	}
	else
	{
		m4_beckhoffClass.m4_Array[0] = Self->m4_FYDirection;
	}
	return Py_None;
}

// ���� ��λ���ٶ�����ת(1-��ת��3-��ת��
static PyObject* m4_beckhoff_SetFWDirection(m4_beckhoff* Self, PyObject* Argvs)
{
	Py_INCREF(Py_None);

	if (!PyArg_ParseTuple(Argvs, "f", &Self->m4_FWDirection))
	{
		cout << "Parse the argument 'FWDirection' m4_FYEnable FAILED! You should pass correct values!" << endl;
		return Py_None;
	}
	else
	{
		m4_beckhoffClass.m4_Array[1] = Self->m4_FWDirection;
	}
	return Py_None;
}

// ���� �������ٶ�(����ֵ��
static PyObject* m4_beckhoff_SetFYVelocity(m4_beckhoff* Self, PyObject* Argvs)
{
	Py_INCREF(Py_None);

	if (!PyArg_ParseTuple(Argvs, "f", &Self->m4_FYVelocityWrite))
	{
		cout << "Parse the argument 'm4_FYVelocityWrite' m4_FYEnable FAILED! You should pass correct values!" << endl;
		return Py_None;
	}
	else
	{
		m4_beckhoffClass.m4_Array[2] = Self->m4_FYVelocityWrite;
	}
	return Py_None;
}

// ���� ��λ���ٶ�(����ֵ��
static PyObject* m4_beckhoff_SetFWVelocity(m4_beckhoff* Self, PyObject* Argvs)
{
	Py_INCREF(Py_None);

	if (!PyArg_ParseTuple(Argvs, "f", &Self->m4_FWVelocityWrite))
	{
		cout << "Parse the argument 'm4_FWVelocityWrite' m4_FYEnable FAILED! You should pass correct values!" << endl;
		return Py_None;
	}
	else
	{
		m4_beckhoffClass.m4_Array[3] = Self->m4_FWVelocityWrite;
	}
	return Py_None;
}

// ��MD14д�������(�ٶ�д�������)
static PyObject* m4_beckhoff_WriteVelocityToController(m4_beckhoff* Self)
{
	m4_beckhoffClass.m4_BeckHoff_WriteArray();

	return Py_BuildValue("f", 1.0);
}

// �˶�ֹͣ
static PyObject* m4_beckhoff_MoveStop(m4_beckhoff* Self)
{
	m4_beckhoffClass.m4_BeckHoff_Function_MoveStop();

	return Py_BuildValue("f", 1.0);
}


// ���� ������Ƕ�
static PyObject* m4_beckhoff_SetFYPosition(m4_beckhoff* Self, PyObject* Argvs)
{
	Py_INCREF(Py_None);

	if (!PyArg_ParseTuple(Argvs, "f", &Self->m4_FYPositionWrite))
	{
		cout << "Parse the argument 'm4_FYPositionWrite' m4_FYEnable FAILED! You should pass correct values!" << endl;
		return Py_None;
	}
	else
	{
		m4_beckhoffClass.m4_FuYangWrite = Self->m4_FYPositionWrite;
	}
	return Py_None;
}

// ���� ��λ��Ƕ�
static PyObject* m4_beckhoff_SetFWPosition(m4_beckhoff* Self, PyObject* Argvs)
{
	Py_INCREF(Py_None);

	if (!PyArg_ParseTuple(Argvs, "f", &Self->m4_FWPositionWrite))
	{
		cout << "Parse the argument 'm4_FWPositionWrite' m4_FYEnable FAILED! You should pass correct values!" << endl;
		return Py_None;
	}
	else
	{
		m4_beckhoffClass.m4_FangWeiWrite = Self->m4_FWPositionWrite;
	}
	return Py_None;
}

// �Ƕ�д�������
static PyObject* m4_beckhoff_WritePositionToController(m4_beckhoff* Self)
{
	m4_beckhoffClass.m4_BeckHoff_Function_AxisMove();

	return Py_BuildValue("f", 1.0);
}


// ת̨����
static PyObject* m4_BeckHoff_Function_EncodeSetZero(m4_beckhoff* Self)
{
	m4_beckhoffClass.m4_BeckHoff_Function_EncodeSetZero();

	return Py_BuildValue("f", 1.0);
}

// open file
static PyObject* m4_OpenFile(m4_beckhoff* Self)
{
	m4_beckhoffClass.m4_FileOpen = 0;
	m4_beckhoffClass.m4_BeckHoff_FileOpen();
	m4_beckhoffClass.m4_FileOpen = 1;
	m4_beckhoffClass.m4_BeckHoff_FileOpen();
	return Py_BuildValue("f", 1.0);
}

// close file
static PyObject* m4_CloseFile(m4_beckhoff* Self)
{
	m4_beckhoffClass.m4_FileClose = 0;
	m4_beckhoffClass.m4_BeckHoff_FileClose();
	m4_beckhoffClass.m4_FileClose = 1;
	m4_beckhoffClass.m4_BeckHoff_FileClose();
	return Py_BuildValue("f", 1.0);
}


static PyObject* m4_beckhoff_PrintInfo(m4_beckhoff* Self)
{
	cout << "The scores as follows:" << endl
		<< "==============================" << endl
		<< "Name    : " << Self->m_szName << endl
		<< "Math    : " << Self->m_dMath << endl
		<< "English : " << Self->m_dEnglish << endl
		<< "==============================" << endl;

	Py_XINCREF(Py_None);
	return Py_None;
}

//������г�Ա�����ṹ�б�.
// ��Ȼ��static��PyMethodDef�����˷����б�˵���Ľṹ����һ���ַ�����GetName��������Python�пɼ����Ǹ�������������Ȼ������C++������Ӧ�ĺ�������ͬ�������Լ�����
// (PyCFunction)m4_beckhoff������C++�еĶ�Ӧ�ĺ���ָ�롣
// METH_VARARGS���������˴�Python��C++�������ݲ����ķ�����METH_VARARGSָ������Tuple���ݣ����û�в���������METH_NOARGS��
// һ���ַ�����Get the Name ��Instance�����������������DocString����Python�п�����MethodName.__doc__��á�
static PyMethodDef m4_beckhoff_MethodMembers[] =
{
	{ "m4_beckhoff_Init", (PyCFunction)m4_beckhoff_Init, METH_VARARGS, "Set the english of instance." }, // ������������ʼ��

	// ��ȡ��������ֵ
	{ "GetName", (PyCFunction)m4_beckhoff_GetName, METH_NOARGS, "Get the name of instance." },
	{ "GetMath", (PyCFunction)m4_beckhoff_GetMath, METH_NOARGS, "Get the math score of instance." },
	{ "GetEnglish", (PyCFunction)m4_beckhoff_GetEnglish, METH_NOARGS, "Get the english score of isntance." },
	{ "m4_GetFWEnable", (PyCFunction)m4_beckhoff_GetFWEnable, METH_VARARGS, "Get FW aixs flag." },
	{ "m4_GetFYEnable", (PyCFunction)m4_beckhoff_GetFYEnable, METH_VARARGS, "Get FY aixs flag." },
	{ "m4_GetFYDirection", (PyCFunction)m4_beckhoff_GetFYDirection, METH_VARARGS, "Get FY aixs Direction flag." },
	{ "m4_GetFWDirection", (PyCFunction)m4_beckhoff_GetFWDirection, METH_VARARGS, "Get FW aixs Direction flag." },
	{ "m4_GetFYVelocity", (PyCFunction)m4_beckhoff_GetFYVelocity, METH_VARARGS, "Get FY aixs velocity." },
	{ "m4_GetFWVelocity", (PyCFunction)m4_beckhoff_GetFWVelocity, METH_VARARGS, "Get FW aixs velocity." },
	{ "m4_GetVelocityFromController", (PyCFunction)m4_beckhoff_GetVelocityFromController, METH_VARARGS, "Get aixs velocity from controller." },
	{ "m4_GetFYPosition", (PyCFunction)m4_beckhoff_GetFYPosition, METH_VARARGS, "Get FY aixs position." },
	{ "m4_GetFWPosition", (PyCFunction)m4_beckhoff_GetFWPosition, METH_VARARGS, "Get FW aixs position." },
	{ "m4_GetPositionFromController", (PyCFunction)m4_beckhoff_GetPositionFromController, METH_VARARGS, "Get aixs position from controller." },
	

	// ���ÿ�������ֵ
	{ "SetMath", (PyCFunction)m4_beckhoff_SetMath, METH_VARARGS, "Set the math score of instance." },
	{ "SetEnglish", (PyCFunction)m4_beckhoff_SetEnglish, METH_VARARGS, "Set the english of instance." },
	{ "m4_SetFWEnable", (PyCFunction)m4_beckhoff_SetFWEnable, METH_VARARGS, "Set FW aixs flag." },
	{ "m4_SetFYEnable", (PyCFunction)m4_beckhoff_SetFYEnable, METH_VARARGS, "Set FY aixs flag." },

	{ "m4_EnableFWAixs", (PyCFunction)m4_EnableFWAixs, METH_VARARGS, "Enable FW aixs." },
	{ "m4_EnableFYAixs", (PyCFunction)m4_EnableFYAixs, METH_VARARGS, "Enable FY aixs." },
	


	{ "m4_SetFYDirection", (PyCFunction)m4_beckhoff_SetFYDirection, METH_VARARGS, "Set FY aixs Direction flag." },
	{ "m4_SetFWDirection", (PyCFunction)m4_beckhoff_SetFWDirection, METH_VARARGS, "Set FW aixs Direction flag." },
	{ "m4_SetFYVelocity", (PyCFunction)m4_beckhoff_SetFYVelocity, METH_VARARGS, "Set FY aixs velocity." },
	{ "m4_SetFWVelocity", (PyCFunction)m4_beckhoff_SetFWVelocity, METH_VARARGS, "Set FW aixs velocity." },
	{ "m4_WriteVelocityToController", (PyCFunction)m4_beckhoff_WriteVelocityToController, METH_VARARGS, "Write velocity to beckhoff controller." },
	{ "m4_MoveStop", (PyCFunction)m4_beckhoff_MoveStop, METH_VARARGS, "FW and FY aixs move stop." },
	{ "m4_SetFYPosition", (PyCFunction)m4_beckhoff_SetFYPosition, METH_VARARGS, "Set FY aixs position." },
	{ "m4_SetFWPosition", (PyCFunction)m4_beckhoff_SetFWPosition, METH_VARARGS, "Set FW aixs position." },
	{ "m4_WritePositionToController", (PyCFunction)m4_beckhoff_WritePositionToController, METH_VARARGS, "Write position to beckhoff controller." },
	{ "m4_EncodeSetZero", (PyCFunction)m4_BeckHoff_Function_EncodeSetZero, METH_VARARGS, "set zero of encoder." },
	{ "m4_OpenFile", (PyCFunction)m4_OpenFile, METH_VARARGS, "open file" },
	{ "m4_OpenClose", (PyCFunction)m4_CloseFile, METH_VARARGS, "close file" },

	

	{ "PrintInfo", (PyCFunction)m4_beckhoff_PrintInfo, METH_NOARGS, "Print all information of instance." },

	{ NULL, NULL, NULL, NULL }
};



// ��/�ṹ�����г�Ա���������Ե�˵����Ϣ.
// ��Ȼstatic����һ���ַ���������ClassName.__name__��ȡ���������������
// sizeof(m4_beckhoff)����˵������/�ṹ�Ĵ�С��
// ��0�Ĳ����ˣ��������ע�ͣ�����ÿ��λ�õĶ�Ӧ��ɸ��
static PyTypeObject m4_beckhoff_ClassInfo =
{
	PyVarObject_HEAD_INIT(NULL, 0)"Module.MyCppClass",                 //����ͨ��__class__�������ַ���. CPP��������.__name__��ȡ.
	sizeof(m4_beckhoff),                 //��/�ṹ�ĳ���.����PyObject_Newʱ��Ҫ֪�����С.
	0,
	(destructor)m4_beckhoff_Destruct,    //�����������.
	0,
	0,
	0,
	0,
	(reprfunc)m4_beckhoff_Repr,          //repr ���ú������á�
	0,
	0,
	0,
	0,
	0,
	(reprfunc)m4_beckhoff_Str,          //Str/print���ú�������.
	0,
	0,
	0,
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                 //���û���ṩ�����Ļ���ΪPy_TPFLAGS_DEFAULE
	"MyCppClass Objects---Extensioned by C++!",                   //__doc__,��/�ṹ��DocString.
	0,
	0,
	0,
	0,
	0,
	0,
	m4_beckhoff_MethodMembers,        //������з�������.
	m4_beckhoff_DataMembers,          //����������ݳ�Ա����.
	0,
	0,
	0,
	0,
	0,
	0,
	(initproc)m4_beckhoff_init,      //��Ĺ��캯��.
	0,
};

// ��ģ���˵����Ϣ.
// ��Ȼstatic����һ����ΪPyModuleDef_HEAD_INIT
// ģ�����������������ModuleName.__name__��ȡ��
// ģ���DocString��������ModuleName.__doc__��ȡ
static PyModuleDef ModuleInfo =
{
	PyModuleDef_HEAD_INIT,
	"My C++ Class Module",               //ģ���������--__name__.
	"This Module Created By C++--extension a class to Python!",                 //ģ���DocString.__doc__
	-1,
	NULL, NULL, NULL, NULL, NULL
};


// ģ��ĳ�ʼ������. import ʱ�Զ�����.
// PyType_Ready ���������ݲ��������������˵����Ϣ�������ж����Ƿ�ɵ�����
// PyModule_Create�������ģ��
// PyModule_AddObject���������뵽ģ���У���ע�⣺��һ������ΪPyObject*ģ����󣬵ڶ���Ϊ��������Python Intepreter�е����֡�������ַ�����Ȼ���Ժ�C++������Ӧ��������ͬ��
// == __decslpec(dllexport) PyObject*, ���嵼������.
PyMODINIT_FUNC PyInit_m4_beckoff(void)       //ģ���ⲿ����Ϊ--CppClass
{
	PyObject* pReturn = 0;
	m4_beckhoff_ClassInfo.tp_new = PyType_GenericNew;       //�����new���ú�������������.

	/////////////////////////////////////////////////////
	// ��ɶ������͵ĳ�ʼ�������������̳����Եȵȡ�
	// ����ɹ����򷵻�0�����򷵻�-1���׳��쳣.
	//

	if (PyType_Ready(&m4_beckhoff_ClassInfo) < 0)
		return NULL;

	pReturn = PyModule_Create(&ModuleInfo);          //����ģ����Ϣ����ģ��.
	if (pReturn == 0)
		return NULL;

	Py_INCREF(&ModuleInfo);
	PyModule_AddObject(pReturn, "m4_beckhoff", (PyObject*)&m4_beckhoff_ClassInfo); //���������뵽ģ���Dictionary��.
	return pReturn;
}
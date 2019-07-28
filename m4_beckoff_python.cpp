#include <iostream>
#include <sstream>
#include <Python.h>
#include <structmember.h>
#include "m4_BeckHoffWriteAndRead.h"
using namespace std;

m4_BeckHoffWriteAndRead m4_beckhoffClass;
// 类/结构的定义.
typedef struct _m4_beckhoff
{
	PyObject_HEAD      // == PyObject ob_base;  定义一个PyObject对象.
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

static PyMemberDef m4_beckhoff_DataMembers[] =         //PyMemberDef是类成员的说明结构
{
	//字符串”m_szName”就是导出到Python中的类成员，这个名字不一定非得和C++中相应类成员的名字相同。
	//T_STRING、T_FLOAT是这个成员的数据类型的说明
	//offsetof亦是一个宏，在STDDEF.h中
	//字符串”The …”——这是成员的DocString
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


//内部方法
// CScore类的所有内置、构造方法.
//可以看出，类的成员函数都是这样一个面孔：static void MethodName(ClassType* Self, …),如果函数有返回值的话，将void替换为Pyobject*即可。所有的函数名自己随便定。
//至于第一个参数Self，是必须有的，它就像Python中类方法定义时的self一样，和C++中的this指针的机理差不多。正如你所见，用它来引用类中的数据成员。

static int m4_beckhoff_init(m4_beckhoff* Self, PyObject* pArgs)    //构造方法.
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

static void m4_beckhoff_Destruct(m4_beckhoff* Self)                   //析构方法.
{
	if (Self->m_szName)
		delete[] Self->m_szName;              //先释放其字符指针对象.

	//如果还有PyObject*成员的话，要一并释放之.
	//如：Py_XDECREF(Self->Member);
	Py_TYPE(Self)->tp_free((PyObject*)Self);      //释放对象/实例.
}

static PyObject* m4_beckhoff_Str(m4_beckhoff* Self)             //调用str/print时自动调用此函数.
{
	ostringstream OStr;
	OStr << "Name    : " << Self->m_szName << endl
		<< "Math    : " << Self->m_dMath << endl
		<< "English : " << Self->m_dEnglish << endl;
	string Str = OStr.str();
	return Py_BuildValue("s", Str.c_str());
}

static PyObject* m4_beckhoff_Repr(m4_beckhoff* Self)            //调用repr内置函数时自动调用.
{
	return m4_beckhoff_Str(Self);
}

//外部方法
// m4_beckhoff类的所有Get方法.
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

// 获取FW使能标志位
static PyObject* m4_beckhoff_GetFWEnable(m4_beckhoff* Self)
{
	Self->m4_FWEnable = m4_beckhoffClass.m4_FWEnable;

	return Py_BuildValue("i", Self->m4_FWEnable);
}

// 获取FY使能标志位
static PyObject* m4_beckhoff_GetFYEnable(m4_beckhoff* Self)
{
	Self->m4_FYEnable = m4_beckhoffClass.m4_FYEable;

	return Py_BuildValue("i", Self->m4_FYEnable);
}

// 获取 俯仰轴速度正反转标志位(1-正转，3-反转）
static PyObject* m4_beckhoff_GetFYDirection(m4_beckhoff* Self)
{
	Self->m4_FYDirection = m4_beckhoffClass.m4_Array[0];

	return Py_BuildValue("f", Self->m4_FYDirection);
}

// 获取 方位轴速度正反转标志位(1-正转，3-反转）
static PyObject* m4_beckhoff_GetFWDirection(m4_beckhoff* Self)
{
	Self->m4_FWDirection = m4_beckhoffClass.m4_Array[1];

	return Py_BuildValue("f", Self->m4_FWDirection);
}

// 获取 俯仰轴速度
static PyObject* m4_beckhoff_GetFYVelocity(m4_beckhoff* Self)
{
	Self->m4_FYVelocityRead = m4_beckhoffClass.m4_ArrayRead[3];

	return Py_BuildValue("f", Self->m4_FYVelocityRead);
}

// 获取 方位轴速度
static PyObject* m4_beckhoff_GetFWVelocity(m4_beckhoff* Self)
{
	Self->m4_FWVelocityRead = m4_beckhoffClass.m4_ArrayRead[2];

	return Py_BuildValue("f", Self->m4_FWVelocityRead);
}

// 从获取控制器中获取方位，俯仰轴的速度 
static PyObject* m4_beckhoff_GetVelocityFromController(m4_beckhoff* Self)
{
	m4_beckhoffClass.m4_BeckHoff_ArrayRead();

	return Py_BuildValue("f", 1.0);
}

// 获取 俯仰轴角度位置
static PyObject* m4_beckhoff_GetFYPosition(m4_beckhoff* Self)
{
	Self->m4_FYPositionRead = m4_beckhoffClass.m4_FuYangRead;

	return Py_BuildValue("f", Self->m4_FYPositionRead);
}

// 获取 方位轴角度位置
static PyObject* m4_beckhoff_GetFWPosition(m4_beckhoff* Self)
{
	Self->m4_FWPositionRead = m4_beckhoffClass.m4_FangWeiRead;

	return Py_BuildValue("f", Self->m4_FWPositionRead);
}

// 从控制器中获取方位，俯仰轴的角度
static PyObject* m4_beckhoff_GetPositionFromController(m4_beckhoff* Self)
{
	m4_beckhoffClass.m4_BeckHoff_ReadFangWei();
	m4_beckhoffClass.m4_BeckHoff_ReadFuYang();
	return Py_BuildValue("f", 1.0);
}










////////////////////////////////////////////////////////////
// m4_beckhoff类的所有Set方法.
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

// 设置FW使能标志位
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

// 设置FY使能标志位
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

// 使能方位轴
static PyObject* m4_EnableFWAixs(m4_beckhoff* Self)
{
	m4_beckhoffClass.m4_BeckHoff_FangWeiEnable();

	return Py_BuildValue("f", 1.0);
}

// 使能俯仰轴
static PyObject* m4_EnableFYAixs(m4_beckhoff* Self)
{
	m4_beckhoffClass.m4_BeckHoff_FuYangEnable();

	return Py_BuildValue("f", 1.0);
}

// 设置 俯仰轴速度正反转(1-正转，3-反转）
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

// 设置 方位轴速度正反转(1-正转，3-反转）
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

// 设置 俯仰轴速度(绝对值）
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

// 设置 方位轴速度(绝对值）
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

// 将MD14写入控制器(速度写入控制器)
static PyObject* m4_beckhoff_WriteVelocityToController(m4_beckhoff* Self)
{
	m4_beckhoffClass.m4_BeckHoff_WriteArray();

	return Py_BuildValue("f", 1.0);
}

// 运动停止
static PyObject* m4_beckhoff_MoveStop(m4_beckhoff* Self)
{
	m4_beckhoffClass.m4_BeckHoff_Function_MoveStop();

	return Py_BuildValue("f", 1.0);
}


// 设置 俯仰轴角度
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

// 设置 方位轴角度
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

// 角度写入控制器
static PyObject* m4_beckhoff_WritePositionToController(m4_beckhoff* Self)
{
	m4_beckhoffClass.m4_BeckHoff_Function_AxisMove();

	return Py_BuildValue("f", 1.0);
}


// 转台标零
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

//类的所有成员函数结构列表.
// 依然是static，PyMethodDef定义了方法列表说明的结构。第一个字符串”GetName”——是Python中可见的那个函数名——依然不必与C++中所对应的函数名相同，可以自己定。
// (PyCFunction)m4_beckhoff——是C++中的对应的函数指针。
// METH_VARARGS——定义了从Python向C++函数传递参数的方法。METH_VARARGS指定了用Tuple传递，如果没有参数，请用METH_NOARGS。
// 一个字符串”Get the Name …Instance”——是这个函数的DocString，在Python中可以用MethodName.__doc__获得。
static PyMethodDef m4_beckhoff_MethodMembers[] =
{
	{ "m4_beckhoff_Init", (PyCFunction)m4_beckhoff_Init, METH_VARARGS, "Set the english of instance." }, // 倍福控制器初始化

	// 获取控制器的值
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
	

	// 设置控制器的值
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



// 类/结构的所有成员、内置属性的说明信息.
// 依然static！第一个字符串可以用ClassName.__name__获取，是类的内置名称
// sizeof(m4_beckhoff)——说明了类/结构的大小。
// 有0的不看了，其余的有注释，其中每个位置的对应项不可搞错
static PyTypeObject m4_beckhoff_ClassInfo =
{
	PyVarObject_HEAD_INIT(NULL, 0)"Module.MyCppClass",                 //可以通过__class__获得这个字符串. CPP可以用类.__name__获取.
	sizeof(m4_beckhoff),                 //类/结构的长度.调用PyObject_New时需要知道其大小.
	0,
	(destructor)m4_beckhoff_Destruct,    //类的析构函数.
	0,
	0,
	0,
	0,
	(reprfunc)m4_beckhoff_Repr,          //repr 内置函数调用。
	0,
	0,
	0,
	0,
	0,
	(reprfunc)m4_beckhoff_Str,          //Str/print内置函数调用.
	0,
	0,
	0,
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                 //如果没有提供方法的话，为Py_TPFLAGS_DEFAULE
	"MyCppClass Objects---Extensioned by C++!",                   //__doc__,类/结构的DocString.
	0,
	0,
	0,
	0,
	0,
	0,
	m4_beckhoff_MethodMembers,        //类的所有方法集合.
	m4_beckhoff_DataMembers,          //类的所有数据成员集合.
	0,
	0,
	0,
	0,
	0,
	0,
	(initproc)m4_beckhoff_init,      //类的构造函数.
	0,
};

// 此模块的说明信息.
// 依然static！第一项总为PyModuleDef_HEAD_INIT
// 模块的内置名，可以用ModuleName.__name__获取。
// 模块的DocString，可以用ModuleName.__doc__获取
static PyModuleDef ModuleInfo =
{
	PyModuleDef_HEAD_INIT,
	"My C++ Class Module",               //模块的内置名--__name__.
	"This Module Created By C++--extension a class to Python!",                 //模块的DocString.__doc__
	-1,
	NULL, NULL, NULL, NULL, NULL
};


// 模块的初始化函数. import 时自动调用.
// PyType_Ready 函数，根据参数——导出类的说明信息——来判断类是否可导出。
// PyModule_Create创建这个模块
// PyModule_AddObject将这个类加入到模块中！请注意：第一个参数为PyObject*模块对象，第二个为导出类在Python Intepreter中的名字——这个字符串依然可以和C++中所对应的类名不同！
// == __decslpec(dllexport) PyObject*, 定义导出函数.
PyMODINIT_FUNC PyInit_m4_beckoff(void)       //模块外部名称为--CppClass
{
	PyObject* pReturn = 0;
	m4_beckhoff_ClassInfo.tp_new = PyType_GenericNew;       //此类的new内置函数—建立对象.

	/////////////////////////////////////////////////////
	// 完成对象类型的初始化—包括添加其继承特性等等。
	// 如果成功，则返回0，否则返回-1并抛出异常.
	//

	if (PyType_Ready(&m4_beckhoff_ClassInfo) < 0)
		return NULL;

	pReturn = PyModule_Create(&ModuleInfo);          //根据模块信息创建模块.
	if (pReturn == 0)
		return NULL;

	Py_INCREF(&ModuleInfo);
	PyModule_AddObject(pReturn, "m4_beckhoff", (PyObject*)&m4_beckhoff_ClassInfo); //将这个类加入到模块的Dictionary中.
	return pReturn;
}
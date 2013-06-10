// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
#define _CRT_SECURE_NO_DEPRECATE 1
// Windows 头文件:
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <objbase.h>
#include <zmouse.h>


//#include "../duilib/UIlib.h"

//using namespace DuiLib;


//#ifdef _DEBUG
//#   ifdef _UNICODE
//#       pragma comment(lib, "..\\..\\bin\\DuiLib_ud.lib")
//#   else
//#       pragma comment(lib, "..\\..\\bin\\DuiLib_d.lib")
//#   endif
//#else
//#   ifdef _UNICODE
//#       pragma comment(lib, "..\\..\\bin\\DuiLib_u.lib")
//#   else
//#       pragma comment(lib, "..\\..\\bin\\DuiLib.lib")
//#   endif
//#endif



#ifdef _DEBUG
#pragma message("[mousee] 调试版（Debug）")
#else
#pragma message("[mousee] 非调试（Release）")
#endif

#ifdef _MT
#pragma message("[mousee] 多线程（MT）")
#else
#pragma message("[mousee] 非多线程"
#endif

#ifdef _DLL
#pragma message("[mousee] 动态链接VC Runtime")
#else
#pragma message("[mousee] 静态链接到VC Runtime")
#endif

#ifdef _UNICODE
#pragma message("[mousee] UNICODE编码")
#else
#pragma message("[mousee] ANSI编码")
#endif

#if 0

#ifdef _DEBUG
#	if   ( defined(_MT) && !defined(_DLL) && defined(_DEBUG) && defined(_UNICODE))
#		pragma comment(lib,"DuiLib_mtdu.lib")
#	elif ( defined(_MT) && !defined(_DLL) && defined(_DEBUG) && !defined(_UNICODE))
#		pragma comment(lib,"DuiLib_mtda.lib")
#	elif ( defined(_MT) && defined(_DLL) && defined(_DEBUG) && defined(_UNICODE))
#		pragma comment(lib,"DuiLib_mddu.lib")
#	elif ( defined(_MT) && defined(_DLL) && defined(_DEBUG) && defined(_UNICODE))
#	   pragma comment(lib,"DuiLib_mdda.lib")
#	endif
#else
#	if   ( defined(_MT) && !defined(_DLL) && defined(_UNICODE))
#		pragma comment(lib,"DuiLib_mtdu.lib")
#	elif ( defined(_MT) && !defined(_DLL) && !defined(_UNICODE))
#		pragma comment(lib,"DuiLib_mtda.lib")
#	elif ( defined(_MT) && defined(_DLL) && defined(_UNICODE))
#		pragma comment(lib,"DuiLib_mddu.lib")
#	elif ( defined(_MT) && defined(_DLL) && defined(_UNICODE))
#	   pragma comment(lib,"DuiLib_mdda.lib")
#	endif
#endif // _DEBUG

#endif

// TODO: 在此处引用程序需要的其他头文件
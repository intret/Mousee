// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
#define _CRT_SECURE_NO_DEPRECATE 1
// Windows ͷ�ļ�:
#include <windows.h>

// C ����ʱͷ�ļ�
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
#pragma message("[mousee] ���԰棨Debug��")
#else
#pragma message("[mousee] �ǵ��ԣ�Release��")
#endif

#ifdef _MT
#pragma message("[mousee] ���̣߳�MT��")
#else
#pragma message("[mousee] �Ƕ��߳�"
#endif

#ifdef _DLL
#pragma message("[mousee] ��̬����VC Runtime")
#else
#pragma message("[mousee] ��̬���ӵ�VC Runtime")
#endif

#ifdef _UNICODE
#pragma message("[mousee] UNICODE����")
#else
#pragma message("[mousee] ANSI����")
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

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
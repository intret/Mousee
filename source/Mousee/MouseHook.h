/// 
/// Copyright (C) 2011, intret. All rights reserved.
/// 
/// @file   MouseHook.h
/// @author intret
/// @date   2011.9.17
/// @brief  
/// 
//////////////////////////////////////////////////////////////////////////

#ifndef MOUSEHOOK_H_
#define MOUSEHOOK_H_

#include "MouseeDef.h"

HHOOK SetLowLevelMouseHook();
BOOL UnhookLowLevelMouseHook(HHOOK hHook);
LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam );
LRESULT CALLBACK GetMsgProc( int code, WPARAM wParam, LPARAM lParam );
LRESULT CALLBACK MouseProc( int code, WPARAM wParam, LPARAM lParam );

class MouseHook
{
public:
	MouseHook( HWND hReceiver );
	~MouseHook();

	HHOOK InstallLlMouseHook();
	void UninstallLlMouseHook();

	//static LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam );
private: 
	HWND	hWnd;

};


class Hook
{
public:
	bool SetHook( int idHook, HOOKPROC lpfn, HINSTANCE hInst, DWORD dwThreadId );


private:
	HHOOK	_hook;
};


#endif // MOUSEHOOK_H_
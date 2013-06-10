/// 
/// Copyright (C) 2011, intret. All rights reserved.
/// 
/// @file   Mousee.h
/// @author 
/// @date   2011.9.17
/// @brief  
/// 
//////////////////////////////////////////////////////////////////////////
#ifndef MOUSEE_H_
#define MOUSEE_H_


#include "resource.h"
#include "Config.h"


extern HINSTANCE hInst;
extern HHOOK hMouseHook;
extern HHOOK hGetMessageHook;

extern HWND hLabelCursorPos;
extern HWND hLabelCurrentWndClassName;
extern HWND hLabelAncestorWndClassName;
extern HWND hLabelParentWndClassName;
extern HWND hLabelWindowRect;
extern HWND hLabelClientRect;
extern HWND hLabelHandle;
extern HWND hLabelMessage;
extern HWND g_hwndMaskLayer;
extern HWND hWndMain;

Config& GetAppGlobalConfig();
static HINSTANCE GetAppInstance() 
{ 
	return hInst; 
}

static HWND GetMainWindowHandle()
{
	return hWndMain;
}

BOOL	InitInstance(HINSTANCE, int);
void	LoadConfig();
BOOL	InitNotifyAreaIcon( HWND hWndMain );
BOOL	InitControls(HINSTANCE hInstance, HWND hWndMain);
HRESULT EnableBlurBehind( HWND hwnd );


#endif // MOUSEE_H_
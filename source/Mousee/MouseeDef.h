/// 
/// Copyright (C) 2011, intret. All rights reserved.
/// 
/// @file   MouseeDef.h
/// @author 
/// @date   2011.9.17
/// @brief  
/// 
//////////////////////////////////////////////////////////////////////////

#ifndef CONSTANT_H_
#define CONSTANT_H_

// 
// User message
// 

// Low level hook message
#define UM_LBUTTONDOWN		WM_USER+0
#define UM_LBUTTONUP		WM_USER+1
#define UM_MOUSEMOVE		WM_USER+2
#define UM_MOUSEWHEEL		WM_USER+3
#define UM_MOUSEHWHEEL		WM_USER+4
#define UM_RBUTTONDOWN		WM_USER+5
#define UM_RBUTTONUP		WM_USER+6
#define UM_TOPMOST_WINDOW	WM_USER+7
#define UM_SHOWMESSAGE		WM_USER+8
#define UM_MBUTTONDOWN		WM_USER+9
#define UM_MBUTTONUP		WM_USER+10
#define UM_MBUTTONCLICK		WM_USER+11

// Notification area icon message
#define	UM_NOTIFYICON		(WM_USER + 100 + 1)

// Notification icon context menu item ID
#define IDM_TRAY_ENABLE							201
#define IDM_TRAY_ABOUT							202
#define IDM_TRAY_CLOSE							203
#define IDM_TRAY_RUN_WITH_STARTUP				204
#define IDM_TRAY_CLICK_MBUTTON_TO_CLOSE_WINDOW	205
#define IDM_TRAY_SELET_WINDOW					206
#define IDM_TRAY_RIGHT_KEY_TOPMOST_WINDOW		207
#define IDM_TRAY_CLOSE_MONITOR					208

#endif // CONSTANT_H_

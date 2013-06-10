/// 
/// Copyright (C) 2011, intret. All rights reserved.
/// 
/// @file   WindowHelper.h
/// @author 
/// @date   2011.9.17
/// @brief  
/// 
//////////////////////////////////////////////////////////////////////////

#ifndef WINDOWHELPER_H_
#define WINDOWHELPER_H_

#include <Windows.h>

class WindowHelper
{
public:
	static void AlphaTransparent( HWND hWnd, BYTE bAlpha );
	static void ColorTransparent( HWND hWnd, COLORREF crKey = RGB(255,255,255) );
	static void RemoveCaption( HWND hWnd );
	static void TopmostWindow( HWND hWnd, BOOL bTopmost = TRUE );
	static void CenterWindow( HWND hWnd, HWND hParent = NULL );
	static void ShowMessageBox( HWND hWnd );
};


#pragma warning(push)
#pragma warning(disable:4995)
#include <string>
#pragma warning(pop)

class StrHelper
{
public:
	static void format( std::wstring& str, const wchar_t* fmt, ... );
	static void format( std::string& str, const char* fmt, ... );
	//static string format( const char* fmt, ... );
};

#endif // WINDOWHELPER_H_
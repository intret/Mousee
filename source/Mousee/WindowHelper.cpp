#include "stdafx.h"
#include "WindowHelper.h"
 

void WindowHelper::AlphaTransparent( HWND hWnd, BYTE bAlpha )
{
	SetWindowLongPtr(hWnd, GWL_EXSTYLE, GetWindowLongPtr(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hWnd, RGB(255,255,255), bAlpha, LWA_ALPHA);
}

void WindowHelper::ColorTransparent( HWND hWnd, COLORREF crKey /*= RGB(255,255,255) */ )
{
	SetWindowLongPtr(hWnd, GWL_EXSTYLE, GetWindowLongPtr(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hWnd, crKey, 0, LWA_COLORKEY);
}

void WindowHelper::RemoveCaption( HWND hWnd )
{
	SetWindowLongPtr(hWnd, GWL_STYLE, GetWindowLongPtr(hWnd, GWL_STYLE) & ~WS_CAPTION);
}

void WindowHelper::TopmostWindow( HWND hWnd, BOOL bTopmost /*= TRUE */ )
{
	if (bTopmost)
	{
		SetWindowLongPtr(hWnd, GWL_EXSTYLE, GetWindowLongPtr(hWnd, GWL_EXSTYLE) | WS_EX_TOPMOST);
	}
	else
	{
		SetWindowLongPtr(hWnd, GWL_EXSTYLE, GetWindowLongPtr(hWnd, GWL_EXSTYLE) & ~WS_EX_TOPMOST);
	}
}

void WindowHelper::CenterWindow( HWND hWnd, HWND hParent )
{
	if ( hWnd )
	{
		if ( hParent == NULL )
		{
			hParent = GetDesktopWindow( );
		}

		if ( hParent )
		{
			RECT rcClient = { 0 };
			GetClientRect( hParent, &rcClient );
	
			RECT rcWindow = { 0 };
			GetWindowRect( hWnd, &rcWindow );

			MoveWindow( 
				hWnd, 
				( rcClient.right - rcClient.left - rcWindow.right + rcWindow.left ) / 2, 
				(rcClient.bottom - rcClient.top - rcWindow.bottom + rcWindow.top ) / 2,
				rcWindow.right - rcWindow.left,
				rcWindow.bottom - rcWindow.top,
				FALSE 
				);
		}
	}
}

void StrHelper::format( std::wstring& str, const wchar_t* fmt, ... )
{
	setlocale(LC_ALL, "chs");
	
	va_list args;
	va_start(args, fmt);

	int charCount = _vscwprintf(fmt, args) + 1 ;
	wchar_t* bufferPtr = new wchar_t[ charCount * sizeof(wchar_t) ];
	vswprintf_s(bufferPtr, charCount, fmt, args);
	
	va_end(args);

	str = bufferPtr;
	delete[] bufferPtr;
}

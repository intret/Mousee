#include "stdafx.h"

#include <strsafe.h>

#include "MouseHook.h"
#include "Mousee.h"


HHOOK hHook = NULL;


HHOOK SetLowLevelMouseHook()
{
	return (hHook = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, NULL, 0));
}

BOOL UnhookLowLevelMouseHook(HHOOK hHook)
{
	return UnhookWindowsHookEx(hHook);
}

LRESULT CALLBACK LowLevelMouseProc(int nCode,
								   WPARAM wParam,
								   LPARAM lParam
								   )
{
	if (nCode < 0)
	{
		return CallNextHookEx(hHook, nCode, wParam, lParam);
	}
	HWND hwndTarget = GetMainWindowHandle();

	if (nCode == HC_ACTION)
	{
		switch(wParam)
		{
		case WM_LBUTTONDOWN:
			SendMessage(hwndTarget, UM_LBUTTONDOWN, wParam, lParam);
			break;
		case WM_LBUTTONUP:
			SendMessage(hwndTarget, UM_LBUTTONUP, wParam, lParam);
			break;
		case WM_MOUSEMOVE:
			SendMessage(hwndTarget, UM_MOUSEMOVE, wParam, lParam);
			break;
		case WM_MOUSEWHEEL:
			SendMessage(hwndTarget, UM_MOUSEWHEEL, wParam, lParam);	
			break;
#if (_WIN32_WINNT >= 0x0600)
		case WM_MOUSEHWHEEL:
			SendMessage(hwndTarget, UM_MOUSEHWHEEL, wParam, lParam);
			break;
#endif
		case WM_RBUTTONDOWN:
			SendMessage(hwndTarget, UM_RBUTTONDOWN, wParam, lParam );
			break;
		case WM_RBUTTONUP:
			SendMessage(hwndTarget, UM_RBUTTONUP, wParam, lParam );
			break;
		case WM_MBUTTONDOWN:
			SendMessage(hwndTarget, UM_MBUTTONDOWN, wParam, lParam );
			break;
		case WM_MBUTTONUP:
			SendMessage(hwndTarget, UM_MBUTTONUP, wParam, lParam );
			break;
		default:
			{
				WCHAR szMsg[100] = {0};
				StringCchPrintf(szMsg, 100, L"wParam( Message ID) = 0x%X, lParam = 0x%X", wParam, lParam);
				SendMessage(hwndTarget, UM_SHOWMESSAGE, wParam, (LPARAM)&szMsg[0]);
			}
		}
	}

	return 0;
}

#if 0
LRESULT CALLBACK GetMsgProc( int code, WPARAM wParam, LPARAM lParam )
{
	if (code < 0)
	{
		//return CallNextHookEx(hGetMessageHook, code, wParam, lParam);
	}

	PMSG msg = (PMSG)lParam;
	if ( LOWORD(msg->message) == WM_MBUTTONDBLCLK )
	{
		SendMessage(hWndMain, UM_MBUTTONCLICK, wParam, lParam );
	}

	return 0;
}
#endif // 0

#if 0
LRESULT CALLBACK MouseProc( int code, WPARAM wParam, LPARAM lParam )
{
	if (code < 0)
	{
		return CallNextHookEx(hGetMessageHook, code, wParam, lParam);
	}

	if ( code == HC_ACTION )
	{
		switch (wParam)
		{
		case WM_MBUTTONDBLCLK:
			SendMessage(hWndMain, UM_MBUTTONCLICK, wParam, lParam);
			break;
		default:
			break;
		}
	}

	return 0;
}
#endif
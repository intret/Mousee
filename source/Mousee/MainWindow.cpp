#include "stdafx.h"

#include <string>

#include <assert.h>
#include <commctrl.h>
#include <Strsafe.h>
#include <Windowsx.h>

#include "AboutDialog.h"
#include "Mousee.h"
#include "MouseHook.h"
#include "MaskLayerWnd.h"
#include "SystemNotifyIcon.h"
#include "WindowHelper.h"
#include "SystemUtility.h"
#include "Config.h"
#include "MainWindow.h"
#include "AboutDlg.h"
#include "Mousee.h"

using namespace std;
//using namespace DuiLib;

HWND g_hwndMaskLayer = NULL;
BOOL g_bShowMaskWnd = TRUE;

///////////////////////////////////////////////////////////////////////////
// Main window
///////////////////////////////////////////////////////////////////////////

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
		//-------------------------------------------------------------------------
		//               User-defined message
		//-------------------------------------------------------------------------
	case UM_MOUSEMOVE:
		{
			OnMouseMove(hWnd, wParam, lParam);
		}
		break;
	case UM_MOUSEWHEEL:
		{
			OnMouseWheel(hLabelMessage, wParam, lParam);
		}
		break;
	case UM_LBUTTONDOWN:
		{
			WCHAR szMessage[100] = {0};
			StringCchPrintf(szMessage, 100,  L"UM_LBUTTONDOWN  wParam:0x%08X lParam:0x%08X", wParam, lParam );
			SetWindowText(hLabelMessage, szMessage );
			break;
		}
	case UM_LBUTTONUP:
		{
			WCHAR szMessage[100] = {0};
			StringCchPrintf(szMessage, 100,  L"UM_LBUTTONUP   wParam:0x%08X lParam:0x%08X", wParam, lParam );
			SetWindowText(hLabelMessage, szMessage );
		}
		break;
	case UM_RBUTTONDOWN:
		{
			WCHAR szMessage[100] = {0};
			StringCchPrintf(szMessage, 100,  L"UM_RBUTTONDOWN    wParam:0x%08X lParam:0x%08X", wParam, lParam );
			SetWindowText(hLabelMessage, szMessage );
		}
		break;
	case UM_RBUTTONUP:
		{
			WCHAR szMessage[100] = {0};
			StringCchPrintf(szMessage, 100,  L"UM_RBUTTONUP    wParam:0x%08X lParam:0x%08X", wParam, lParam );
			SetWindowText(hLabelMessage, szMessage );
		}
		break;
	case UM_MBUTTONDOWN:
		{
			WCHAR szMessage[100] = {0};
			StringCchPrintf(szMessage, 100,  L"UM_MBUTTONDOWN    wParam:0x%08X lParam:0x%08X", wParam, lParam );
			SetWindowText(hLabelMessage, szMessage );
		}
		break;
	case UM_MBUTTONUP:
		{
			WCHAR szMessage[100] = {0};
			StringCchPrintf(szMessage, 100,  L"UM_MBUTTONUP    wParam:0x%08X lParam:0x%08X", wParam, lParam );
			SetWindowText(hLabelMessage, szMessage );

			OnMiddleButtonClicked( hWnd, wParam, lParam );
		}
		break;
	case UM_MBUTTONCLICK:
		{
			OnMiddleButtonClicked( hWnd, wParam, lParam );
		}
		break;
	case UM_NOTIFYICON:
		{
			OnSystemNotifyIcon( hWnd, wParam, lParam );
		}
		break;
	case UM_SHOWMESSAGE:
		{
			WCHAR szMessage[100] = {0};
			StringCchPrintf(szMessage, 100,  L"UM_SHOWMESSAGE    wParam:0x%08X lParam:0x%08X", wParam, lParam );
			SetWindowText(hLabelMessage, szMessage );
		}
		break;

		//-------------------------------------------------------------------------
		//            System message
		//-------------------------------------------------------------------------
	case WM_SYSCOMMAND:
		if ( wParam == SC_CLOSE )
		{
			BOOL isCaptureWindow = (g_hwndMaskLayer == NULL);
			if ( isCaptureWindow )
			{
				ShowWindow( hWnd, SW_HIDE );
			}
		}
		else
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_COMMAND:
		{
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			// 分析菜单选择:
			switch (wmId)
			{
			case IDM_ABOUT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, AboutWindowProc);
				break;
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;

		//-------------------------------------------------------------------------
		//               Painting message
		//-------------------------------------------------------------------------
	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			// TODO: 在此添加任意绘图代码...
			//HBRUSH hOldBrush = (HBRUSH)SelectObject( hdc, (HGDIOBJ)GetStockObject(NULL_BRUSH));

			SetBkMode(hdc, TRANSPARENT );
			//SetBkColor(hdc, RGB(23,43,34));
			SetTextColor(hdc, RGB(240, 100, 100));

			TextOut(hdc, 0, 180, _T("Textout"), _tcslen(_T("Textout")) );

			//SelectObject(hdc, hOldBrush);
			EndPaint(hWnd, &ps);
		}
		break;
	case WM_DESTROY:
		{
			if (hMouseHook)
			{
				UnhookLowLevelMouseHook(hMouseHook);
				//UnhookWindowsHookEx(hGetMessageHook);
			}
			PostQuitMessage(0);
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  注释:
//
//    仅当希望
//    此代码与添加到 Windows 95 中的“RegisterClassEx”
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
//    这样应用程序就可以获得关联的
//    “格式正确的”小图标。
//
ATOM RegisterMainWndClass(HINSTANCE hInstance, TCHAR *pszWindowClass )
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= MainWindowProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(CreateSolidBrush(RGB(213,226,246)));
	wcex.lpszMenuName	= NULL; // MAKEINTRESOURCE(IDC_Mousee);
	wcex.lpszClassName	= pszWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_LOGO));

	return RegisterClassEx(&wcex);
}

LRESULT OnMouseMove( HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;

	HWND hWndChild = NULL; // = WindowFromPoint(cursorPos);
	HWND hWndParent = NULL;
	HWND hWndCursorPos = NULL;
	HWND hWndToProcess = NULL;

	HWND hAncestor = NULL;

	WCHAR szCurrentWndClassName[63] = {0};
	WCHAR szParentWndClassName[63] = {0};
	WCHAR szAncestorWndClassName[63] = {0};

	static POINT cursorPos = {0};
	static POINT cliPos = {0};
	static RECT rcWindow = {0};

	GetCursorPos(&cursorPos);

	hWndCursorPos = ::WindowFromPoint(cursorPos);

	hAncestor = GetAncestor(hWndCursorPos, GA_ROOTOWNER );
	if (hAncestor != NULL)
	{
		GetClassName(hAncestor, szAncestorWndClassName, sizeof(szAncestorWndClassName) );
	}

	//if (hWndCursorPos)
	//{
		hWndParent = GetParent(hWndCursorPos);
	//	ScreenToClient(hWndCursorPos, &cliPos);
	//	hWndChild = RealChildWindowFromPoint(hWndParent, cliPos); // RealChildWindowFromPoint
	//	if ( hWndChild != NULL)
	//	{
	//		hWndToProcess = hWndChild;
	//	}
	//}
	hWndToProcess = hWndCursorPos;
	if ( NULL != hWndToProcess )
	{
		if ( IsWindowVisible( hWnd ))
		{
			wchar_t szMsg[200] = { 0 };
			int itemLen = 15;
			WINDOWINFO wndInfo = { 0 };

			if (hWndToProcess)
			{
				GetClassName(hWndToProcess, szCurrentWndClassName, sizeof(szCurrentWndClassName)/sizeof(WCHAR));
			}
			else
			{
				StringCbPrintfW(szCurrentWndClassName, sizeof(szCurrentWndClassName), L"null");
			}

			if ( hWndParent )
			{
				GetClassName(hWndParent, szParentWndClassName, sizeof(szParentWndClassName)/sizeof(WCHAR));
			}
			else
			{
				StringCbPrintfW(szParentWndClassName, sizeof(szParentWndClassName), L"null");
			}

			GetWindowInfo(hWndToProcess, &wndInfo );
			GetWindowRect(hWndToProcess, &rcWindow);

			StringCbPrintfW(szMsg, sizeof(szMsg), L"%*s: %d,%d \r\n" ,
				itemLen, L"Position", cursorPos.x, cursorPos.y  );
			SetWindowText( hLabelCursorPos, szMsg );

			StringCchPrintfW(szMsg, sizeof(szMsg)/sizeof(wchar_t), L"%*s: (%08x) %s",
				itemLen, L"Window class", hWndToProcess, szCurrentWndClassName );
			SetWindowText( hLabelCurrentWndClassName, szMsg );

			StringCchPrintfW(szMsg, sizeof(szMsg)/sizeof(wchar_t), L"%*s: (%08x) %s \r\n",
				itemLen, L"Parent class", hWndParent,szParentWndClassName );
			SetWindowText( hLabelParentWndClassName, szMsg );

			StringCchPrintfW(szMsg, sizeof(szMsg)/sizeof(wchar_t), L"%*s: (%08x) %s \r\n",
				itemLen, L"Ancestor class", hAncestor, szAncestorWndClassName );
			SetWindowText( hLabelAncestorWndClassName, szMsg );

			StringCchPrintfW(szMsg, sizeof(szMsg)/sizeof(wchar_t), L"%*s: (%4d,%4d,%4d,%4d) \r\n",
				itemLen, L"Window rect", rcWindow.left, rcWindow.top, rcWindow.right, rcWindow.bottom  );
			SetWindowText( hLabelWindowRect, szMsg );

			StringCchPrintf(szMsg, sizeof(szMsg)/sizeof(wchar_t), _T("%*s: (%4d,%4d,%4d,%4d)"),
				itemLen, _T("Client rect"), wndInfo.rcClient.left, wndInfo.rcClient.top, wndInfo.rcClient.right, wndInfo.rcClient.bottom );
			SetWindowText(hLabelClientRect, szMsg);

			StringCchPrintfW(szMsg, sizeof(szMsg)/sizeof(wchar_t), L"%*s: %08X \r\n", itemLen, L"HANDLE", hWndToProcess);
			SetWindowText( hLabelHandle, szMsg );

			static HWND hLastWnd = NULL;
			static RECT LastWndRC = { 0, 0 };

			if ( hWndToProcess != hLastWnd
				|| LastWndRC.left != rcWindow.left
				|| LastWndRC.top != rcWindow.top
				|| LastWndRC.right != rcWindow.right
				|| LastWndRC.bottom != rcWindow.bottom )
			{
				// 鼠标移动的时候绘制焦点窗口
				if ( g_hwndMaskLayer )
				{
					///////////////////////////////////////////////////////////////////////////
					hdc = GetWindowDC( g_hwndMaskLayer );

					MoveWindow(g_hwndMaskLayer, rcWindow.left, rcWindow.top, rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top, TRUE);

					HPEN hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0) );
					SelectObject(hdc, (HGDIOBJ)hPen);
					SelectObject(hdc, (HGDIOBJ)NULL_BRUSH);
					Rectangle(hdc, 0, 0, rcWindow.right-rcWindow.left, rcWindow.bottom - rcWindow.top);
					BringWindowToTop(g_hwndMaskLayer);

					ReleaseDC(g_hwndMaskLayer, hdc);
				}
				hLastWnd = hWndToProcess;
				LastWndRC.left = rcWindow.left;
				LastWndRC.top = rcWindow.top;
				LastWndRC.right = rcWindow.right;
				LastWndRC.bottom = rcWindow.bottom;
			}
		}
	}
	return 0;
}

BOOL CaptionHitTest( HWND hWnd, POINT wndPos )
{
	_ASSERT(hWnd!=NULL);

	LRESULT curPosition = SendMessage( hWnd, WM_NCHITTEST, 0, MAKELPARAM(wndPos.x, wndPos.y) );
	return (curPosition == HTCAPTION);
}

LRESULT OnMouseWheel(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//ShowWindow(hWndMain, SW_MINIMIZE);
	short virtualKey = GET_KEYSTATE_WPARAM(wParam);	// The low-order word indicates whether various virtual keys are down

	POINTS pos = MAKEPOINTS(lParam);

	PMSLLHOOKSTRUCT pllHook = (PMSLLHOOKSTRUCT)lParam;
	short zDelta = (short)HIWORD(pllHook->mouseData);	// The high-order word indicates the distance the wheel is rotated
	LONG xPos = pllHook->pt.x;
	LONG yPos = pllHook->pt.y;

	static POINT wndPos = {0};
	GetCursorPos(&wndPos);
	//wndPos.x = xPos;
	//wndPos.y = yPos;

	//HWND hParentWnd = WindowFromPhysicalPoint( wndPos );

	HWND hParentWnd = WindowFromPoint(wndPos);

	//RECT rcClient = {0};
	//GetClientRect(hParentWnd, &rcClient );

	if (hParentWnd)
	{
		// 判断鼠标是否在标题栏上
		BOOL bIsPointedToCaption = CaptionHitTest( hParentWnd, wndPos );
		if ( bIsPointedToCaption )
		{
			WINDOWINFO wndInfo = { 0 };
			wndInfo.cbSize = sizeof(WINDOWINFO);
			GetWindowInfo(hParentWnd, &wndInfo);

			if ( zDelta <= -120 )
			{
				SendMessage(hParentWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
			}
			else if (zDelta >= 120 )
			{
				SendMessage(hParentWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
			}
		}

		//HWND hDesktop = GetDesktopWindow();
		//if ( hDesktop == GetParent(hWndParent) )
	}

	return 0;
}

VOID OnMiddleButtonClicked( HWND hWndMain,  WPARAM wParam, LPARAM lParam )
{
	// TODO: settting : EnabledMButtonClosingWindow
	BOOL bMButtonClosingWindowEnabled = GetAppGlobalConfig()["ClickMiddleButtonToCloseWindow"] == "YES";

	static POINT wndPos = {0};
	GetCursorPos(&wndPos);

	HWND hParentWnd = WindowFromPoint(wndPos);
	if ( hParentWnd != NULL )
	{
		BOOL bIsPointedToCaption = CaptionHitTest( hParentWnd, wndPos );
		if ( bIsPointedToCaption && bMButtonClosingWindowEnabled)
		{
			SendMessage( hParentWnd, WM_SYSCOMMAND, SC_CLOSE, 0 );
		}
	}
}

VOID OnContextMenuRunAtStartup()
{
	if ( GetAppGlobalConfig()["RunAtSystemStartup"] == "YES" )
	{
		// 取消随机启动
		UINT error = SystemUtility::DeleteRunKey( _T("Mousee"), TRUE);
		if ( ERROR_SUCCESS !=  error )
		{
			std::wstring msg;
			StrHelper::format(msg, L"%d", error );
			::MessageBoxW(NULL, msg.c_str(), L"", MB_OK );
		}
		else
		{
			GetAppGlobalConfig()["RunAtSystemStartup"] = "NO";
		}
	}
	else
	{
		UINT error = SystemUtility::RunAtSystemStartup( _T("Mousee"), NULL, TRUE );
		GetAppGlobalConfig()["RunAtSystemStartup"] = "YES";
		if ( ERROR_SUCCESS !=  error )
		{
			std::wstring msg;
			StrHelper::format(msg, L"%d", error );
			::MessageBoxW(NULL, msg.c_str(), L"", MB_OK );
		}
	}
}

VOID OnContexMenuMiddleButtonCloseWindow()
{
	if ( GetAppGlobalConfig()["ClickMiddleButtonToCloseWindow"] == "YES" )
	{
		GetAppGlobalConfig()["ClickMiddleButtonToCloseWindow"] = "NO";
	}
	else
	{
		GetAppGlobalConfig()["ClickMiddleButtonToCloseWindow"] = "YES";
	}
}

VOID OnContextMenuAbout(HWND hWndMain)
{
	//CPaintManagerUI::SetInstance(GetAppInstance());
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));
	//CPaintManagerUI::SetResourceZip(_T("360SafeRes.zip"));

	//HRESULT Hr = ::CoInitialize(NULL);
	//if( FAILED(Hr) )
	//	return ;

	//AboutDialog* pFrame = new AboutDialog();
	//if( pFrame == NULL )
	//	return ;
	//pFrame->Create(NULL, _T("360安全卫士"), UI_WNDSTYLE_FRAME, 0L, 0, 0, 800, 572);
	//pFrame->CenterWindow();
	//::ShowWindow(*pFrame, SW_SHOW);

	//CPaintManagerUI::MessageLoop();

	//::CoUninitialize();

	//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWndMain, AboutWindowProc);
}

VOID OnContextMenuSelectWindow()
{
	if ( g_hwndMaskLayer == NULL )
	{
		g_hwndMaskLayer = CreateMaskLayer( CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, GetDesktopWindow() );
		if ( NULL == g_hwndMaskLayer )
		{
			MessageBox(NULL, L"Create mask layer window failed", L"Error", MB_OK );
		}
	}

	if ( g_bShowMaskWnd )
	{
		ShowWindow( g_hwndMaskLayer, SW_SHOW );
		g_bShowMaskWnd = FALSE;
	}
	else
	{
		ShowWindow( g_hwndMaskLayer, SW_HIDE );
		CloseWindow( g_hwndMaskLayer );
		g_bShowMaskWnd = TRUE;
	}
}

VOID ShowTrayContextMenu( HWND hWndMain, WPARAM wParam, LPARAM lParam )
{
	POINT pos;
	GetCursorPos( &pos );

	if ( g_hwndMaskLayer && !g_bShowMaskWnd )
	{
		ShowWindow( g_hwndMaskLayer, SW_HIDE );
		CloseWindow( g_hwndMaskLayer );
		g_bShowMaskWnd = TRUE;
	}

	// TODO:Show menu
	HMENU hTrayMenu = CreatePopupMenu();
	if ( NULL == hTrayMenu )
	{
		return ;
	}

	//AppendMenu( hTrayMenu, MF_STRING | MF_GRAYED, IDM_TRAY_ENABLE, _T("所有功能") );

	UINT RunAtSystemStartupFlag = MF_UNCHECKED;
	UINT ClickMiddleButtonToCloseWindow = MF_UNCHECKED;
	if ( GetAppGlobalConfig()["RunAtSystemStartup"] == "YES" )
	{
		RunAtSystemStartupFlag = MF_CHECKED;
	}
	if ( GetAppGlobalConfig()["ClickMiddleButtonToCloseWindow"] == "YES" )
	{
		ClickMiddleButtonToCloseWindow = MF_CHECKED;
	}

	AppendMenu( hTrayMenu, MF_STRING | RunAtSystemStartupFlag, IDM_TRAY_RUN_WITH_STARTUP, _T("随系统启动") );
	AppendMenu( hTrayMenu, MF_STRING | ClickMiddleButtonToCloseWindow, IDM_TRAY_CLICK_MBUTTON_TO_CLOSE_WINDOW, _T("按下鼠标中键：关闭窗口") );
	//AppendMenu( hTrayMenu, MF_STRING, IDM_TRAY_SELET_WINDOW, _T("长按右键：置顶窗口(&S)") );
	AppendMenu( hTrayMenu, MF_STRING | MF_USECHECKBITMAPS, IDM_TRAY_SELET_WINDOW, _T("选择窗口(&S)") );
	AppendMenu( hTrayMenu, MF_STRING, IDM_TRAY_CLOSE_MONITOR, _T("关闭显示器") );
	AppendMenu( hTrayMenu, MF_SEPARATOR, 0, NULL );
	AppendMenu( hTrayMenu, MF_STRING, IDM_TRAY_ABOUT, _T("关于(&A)") );
	AppendMenu( hTrayMenu, MF_STRING, IDM_TRAY_CLOSE, _T("退出(&E)") );

	SetForegroundWindow( hWndMain ); // 使得鼠标离开菜单后，菜单自己消失

	INT nID = (INT)::TrackPopupMenu( hTrayMenu, TPM_LEFTALIGN | TPM_RETURNCMD | TPM_LEFTBUTTON, pos.x, pos.y, 0, hWndMain, NULL );
	switch ( nID )
	{
	case IDM_TRAY_RUN_WITH_STARTUP:
		OnContextMenuRunAtStartup();
		break;
	case IDM_TRAY_CLICK_MBUTTON_TO_CLOSE_WINDOW:
		OnContexMenuMiddleButtonCloseWindow();
		break;
	case IDM_TRAY_SELET_WINDOW:
		OnContextMenuSelectWindow();
		break;
	case IDM_TRAY_CLOSE_MONITOR:
		PostMessage( HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 2 );
		break;
	case IDM_TRAY_ENABLE:// TODO:
		break;
	case IDM_TRAY_ABOUT:
		OnContextMenuAbout(hWndMain);
		break;
	case IDM_TRAY_CLOSE:
		DestroyWindow( hWndMain );
		break;
	}

	//PostMessage( hWndMain, WM_NULL, 0, 0);
	DestroyMenu( hTrayMenu );
}

VOID OnSystemNotifyIcon( HWND hWndMain,  WPARAM wParam, LPARAM lParam )
{
	if ( lParam == WM_LBUTTONDBLCLK)
	{
		if ( IsWindowVisible( hWndMain ) )
		{
			ShowWindow(hWndMain, SW_HIDE );
		}
		else
		{
			ShowWindow(hWndMain, SW_SHOW );
			SetForegroundWindow( hWndMain );
		}
	}
	else if ( lParam == WM_RBUTTONDBLCLK )
	{
		DestroyWindow( hWndMain );
	}
	else if ( lParam == WM_RBUTTONUP )
	{
		ShowTrayContextMenu(hWndMain, wParam, lParam );
	}
}
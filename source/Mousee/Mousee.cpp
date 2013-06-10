// Mousee.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"

#include <string>
using namespace std;

#include <commctrl.h>
#include <Strsafe.h>
#include <Windowsx.h>

#include "Mousee.h"
#include "MouseHook.h"
#include "MaskLayerWnd.h"
#include "SystemNotifyIcon.h"
#include "WindowHelper.h"
#include "SystemUtility.h"
#include "Config.h"
#include "MainWindow.h"
#include <assert.h>
#include "AboutDlg.h"

#pragma comment(lib,"ComCtl32.lib ")
#pragma comment(lib,"dwmapi.lib")

///////////////////////////////////////////////////////////////////////////

// 全局变量:
HINSTANCE			hInst;		// 当前实例
SystemNotifyIcon	g_notifyIcon;

HWND				hWndMain;
HHOOK				hMouseHook;

#define		MAX_LOADSTRING 100
TCHAR		szTitle[MAX_LOADSTRING];				// 标题栏文本
TCHAR		szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 
// Controls
// 
HWND hLabelCursorPos;
HWND hLabelCurrentWndClassName;
HWND hLabelParentWndClassName;
HWND hLabelAncestorWndClassName;
HWND hLabelWindowRect;
HWND hLabelClientRect;
HWND hLabelHandle;
HWND hLabelMessage;


///////////////////////////////////////////////////////////////////////////

int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	CreateMutex(NULL, TRUE, _T("__MOUSEE_SINGLE_APP_INSTANCE__"));
	if ( GetLastError() == ERROR_ALREADY_EXISTS )
	{
		return -1;
	}

	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_Mousee, szWindowClass, MAX_LOADSTRING);
	RegisterMainWndClass(hInstance, szWindowClass );

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow = SW_HIDE))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_Mousee));

	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}

BOOL InitControls(HINSTANCE hInstance, HWND hWndMain)
{
	//InitCommonControls();
	//INITCOMMONCONTROLSEX commonCtrl;
	//commonCtrl.dwSize = sizeof(INITCOMMONCONTROLSEX);
	//commonCtrl.dwICC = ICC_STANDARD_CLASSES | ICC_WIN95_CLASSES;
	//if ( !InitCommonControlsEx(&commonCtrl) )
	//{
	//	DWORD dwLastError = GetLastError();
	//	std::wstring  msg;
	//	StrHelper::format( msg, L"InitCommonControlsEx failed with error %d",  dwLastError );
	//	MessageBox(NULL, msg.c_str(), L"Error", MB_OK);
	//}

	//hWndButton = CreateWindow(
	//	L"Button", NULL,
	//	WS_CHILD |WS_VISIBLE | BS_PUSHBUTTON | BS_DEFPUSHBUTTON | BS_PUSHLIKE  ,
	//	5, 5, 50, 50, hWndMain, NULL, hInstance, NULL);

	int nSLWidth = 500;
	int nSLHeigth = 20;
	hLabelCursorPos = CreateWindowEx(WS_EX_TRANSPARENT, 	L"STATIC", L"cursor position",
		WS_CHILD | WS_VISIBLE | SS_LEFT , 0, 0, nSLWidth, nSLHeigth, hWndMain, NULL, hInstance, NULL);

	hLabelHandle = CreateWindowEx(WS_EX_TRANSPARENT, L"STATIC", L"Handle",
		WS_CHILD | WS_VISIBLE | SS_LEFT , 0, 30, nSLWidth, nSLHeigth, hWndMain, NULL, hInstance, NULL);
	
	hLabelParentWndClassName = CreateWindowEx(WS_EX_TRANSPARENT, 	L"STATIC", L"current class name",
		WS_CHILD | WS_VISIBLE | SS_LEFT  , 0, 50, nSLWidth, nSLHeigth, hWndMain, NULL, hInstance, NULL);
	
	hLabelCurrentWndClassName = CreateWindowEx(WS_EX_TRANSPARENT, 	L"STATIC", L"parent class name",
		WS_CHILD | WS_VISIBLE | SS_LEFT  , 0, 70, nSLWidth, nSLHeigth, hWndMain, NULL, hInstance, NULL);
	
	hLabelAncestorWndClassName = CreateWindowEx(WS_EX_TRANSPARENT, 	L"STATIC", L"ancestor class name",
		WS_CHILD | WS_VISIBLE | SS_LEFT  , 0, 90, nSLWidth, nSLHeigth, hWndMain, NULL, hInstance, NULL);

	hLabelWindowRect = CreateWindowEx(WS_EX_TRANSPARENT, 	L"STATIC", L"WindowRect",
		WS_CHILD | WS_VISIBLE | SS_LEFT , 0, 110, nSLWidth, nSLHeigth, hWndMain, NULL, hInstance, NULL);

	hLabelClientRect = CreateWindowEx(WS_EX_TRANSPARENT, L"STATIC", L"ClientRect",
		WS_CHILD | WS_VISIBLE | SS_LEFT , 0, 130, nSLWidth, nSLHeigth, hWndMain, NULL, hInstance, NULL);

	hLabelMessage = CreateWindowEx(WS_EX_TRANSPARENT, L"STATIC", L"Message",
		WS_CHILD | WS_VISIBLE | SS_LEFT , 0, 150, nSLWidth, nSLHeigth, hWndMain, NULL, hInstance, NULL);

	//hEditCtrl = CreateWindow(
	//	L"EDIT", L"MessageEdit", 
	//	WS_VISIBLE|WS_BORDER |WS_VSCROLL|WS_CHILD|ES_AUTOVSCROLL| 
	//	ES_MULTILINE | ES_LEFT | ES_WANTRETURN,
	//	0, 150, 400, 200, hWndMain, NULL, hInstance, NULL
	//	);
	//	
	//hListCtrl = CreateWindow(
	//	L"LISTBOX", 
	//	L"MSGLIST", 
	//	WS_VISIBLE|WS_BORDER |WS_VSCROLL|WS_CHILD | LBS_HASSTRINGS |LBS_STANDARD,
	//	0, 150, 400, 200, hWndMain, NULL, hInstance, NULL
	//	);
	//SetWindowText(hStaticClassName, L"Hello window static control");
	//SendMessage(hEditCtrl, LB_INSERTSTRING, -1, (LPARAM)L"ddd" );
	//SendMessage(hEditCtrl, WM_SETTEXT, 0, (LPARAM)L"ddd" );
	
	HFONT hFont = NULL;
	//LOGFONT logicFont = { 0 };
	//logicFont.lfHeight = 12;
	//logicFont.lfWeight = 0;
	//logicFont.lfEscapement = 0;
	//logicFont.lfWeight = 0;
	//logicFont.lfItalic = FALSE;
	//logicFont.lfUnderline = FALSE;
	//logicFont.lfStrikeOut = FALSE; // 删除线
	//logicFont.lfCharSet = DEFAULT_CHARSET;
	//logicFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	//logicFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	//logicFont.lfQuality = DEFAULT_QUALITY;
	//logicFont.lfPitchAndFamily = DEFAULT_PITCH; // 倾斜
	//StringCchPrintf(logicFont.lfFaceName, LF_FACESIZE, _T("Consolas"));

	//hFont = CreateFontIndirect(&logicFont);
	//if ( hFont == NULL)
	//{
	//	hFont = (HFONT)GetStockObject(SYSTEM_FIXED_FONT);
	//	MessageBox(0,0,0,0);
	//}
	hFont = (HFONT)GetStockObject(/*OEM_FIXED_FONT*/DEFAULT_GUI_FONT);
	SendMessage(hLabelCursorPos, WM_SETFONT, (WPARAM)hFont, 0 );
	SendMessage(hLabelCurrentWndClassName, WM_SETFONT, (WPARAM)hFont, 0 );
	SendMessage(hLabelParentWndClassName, WM_SETFONT, (WPARAM)hFont, 0 );
	SendMessage(hLabelAncestorWndClassName, WM_SETFONT, (WPARAM)hFont, 0 );
	SendMessage(hLabelWindowRect, WM_SETFONT, (WPARAM)hFont, 0 );
	SendMessage(hLabelClientRect, WM_SETFONT, (WPARAM)hFont, 0 );
	SendMessage(hLabelHandle, WM_SETFONT, (WPARAM)hFont, 0 );
	SendMessage(hLabelMessage, WM_SETFONT, (WPARAM)hFont, 0 );

	//DeleteObject( hFont );
	return TRUE;
}

/**
 * @brief InitInstance 
 * 
 * @param hInstance 
 * @param nCmdShow 
 * @return BOOL         
 */ 
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中
 
	hWndMain = CreateWindow(
		szWindowClass, 
		szTitle, 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 400, 300, NULL, NULL, hInstance, NULL);
	if (!hWndMain)
	{
		return FALSE;
	}

	LoadConfig();
	InitControls(hInstance, hWndMain );
	InitNotifyAreaIcon(hWndMain);

	//
	// 安装鼠标钩子
	//
	hMouseHook = SetLowLevelMouseHook();
	if ( hMouseHook == 0)
	{
		DWORD dwErrorCode = GetLastError();
		std::wstring msg;
		StrHelper::format(msg, L"Setup low level mouse hook failed with error code %d ", dwErrorCode );
		MessageBox(NULL, msg.c_str(), NULL, MB_OK);
	}
	
	// 
	// Show windows
	// 
	WindowHelper::CenterWindow( hWndMain );

	//DwmEnableComposition(DWM_EC_ENABLECOMPOSITION);

	ShowWindow(hWndMain, nCmdShow | SW_HIDE);
	//EnableBlurBehind( hWndMain );
	//WindowHelper::TopmostWindow( hWndMain );
	//ShowWindow(hWndButton, WM_SHOWWINDOW);
	UpdateWindow(hWndMain);
	return TRUE;
}


void LoadConfig() 
{

	// Defualt config
	GetAppGlobalConfig()["RunAtSystemStartup"] = "YES";
	GetAppGlobalConfig()["ClickMiddleButtonToCloseWindow"] = "YES";

	// 
	// Read configuration
	// 
	int retVal = SystemUtility::RegValueExist(
		HKEY_CURRENT_USER,
		_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run\\"),
		_T("Mousee") );
	if ( 0 == retVal )
	{
		GetAppGlobalConfig().SetConfig( "RunAtSystemStartup", "YES" );
	}
	else
	{
		std::wstring msg;
		StrHelper::format(msg, L"%d", retVal );
		GetAppGlobalConfig().SetConfig( "RunAtSystemStartup", "NO" );
	}
}

BOOL InitNotifyAreaIcon( HWND hWndMain ) 
{
	g_notifyIcon.Create( hWndMain, UM_NOTIFYICON, IDI_LOGO);
	g_notifyIcon.Show();
	return TRUE;
}

Config& GetAppGlobalConfig()
{
	static Config globalConfig;
	return globalConfig;
}

HRESULT EnableBlurBehind( HWND hwnd )
{
	HRESULT hr = S_OK;

	// Create and populate the blur-behind structure.
	DWM_BLURBEHIND bb = {0};

	// Specify blur-behind and blur region.
	bb.dwFlags = DWM_BB_ENABLE;
	bb.fEnable = true;
	bb.hRgnBlur = NULL;
	bb.fTransitionOnMaximized = TRUE;

	// Enable blur-behind.
	hr = DwmEnableBlurBehindWindow(hwnd, &bb);
	if (SUCCEEDED(hr))
	{
		// ...
	}
	return hr;
}


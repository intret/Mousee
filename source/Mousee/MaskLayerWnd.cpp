#include "stdafx.h"
#include "MaskLayerWnd.h"
#include "WindowHelper.h"

LRESULT CALLBACK MaskLayerWindowProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
const WCHAR szMaskLayerClassName[] = L"MASKLAYERWND";

//////////////////////////////////////////////////////////////////////////

HWND CreateMaskLayer(int x,
					 int y,
					 int nWidth,
					 int nHeight,
					 HWND hParent )
{
	ATOM classID = RegisterMaskLayerClass();

	if ( 0 == classID )
	{
		return NULL;
	}

	//
	// WS_EX_APPWINDOW 会使Window出现在Taskbar上
	// 设置WS_EX_LAYERED，然后使用SetLayeredWindowAttributes设置透明
	// 
	HWND hWnd = CreateWindowEx(
		WS_EX_NOACTIVATE | WS_EX_TOPMOST/* | WS_EX_TRANSPARENT */| WS_EX_LAYERED, // 
		szMaskLayerClassName,
		NULL,
		WS_VISIBLE/*| WS_POPUP*/ ,
		x,
		y,
		nWidth,
		nHeight,
		NULL,//GetDesktopWindow(),
		NULL,
		GetModuleHandle(NULL),
		NULL
		);
 
	WindowHelper::RemoveCaption(hWnd);
	WindowHelper::ColorTransparent(hWnd);
 
	return hWnd;
}

LRESULT CALLBACK MaskLayerWindowProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    switch (message)
    {
    case WM_CREATE:
        return (0);
		
    case WM_PAINT:
        hdc = BeginPaint (hwnd, &ps);
        
        EndPaint (hwnd, &ps);
        return (0);
		
    case WM_DESTROY:
        //PostQuitMessage (0);
        return (0);
    }
    return DefWindowProc (hwnd, message, wParam, lParam);
}
 

ATOM RegisterMaskLayerClass()
{
	static const WNDCLASSEX wndClass = {
		sizeof(WNDCLASSEX),
		CS_DBLCLKS | CS_DROPSHADOW | CS_SAVEBITS,
		MaskLayerWindowProc,
		0,
		0,
		GetModuleHandle(NULL),
		NULL,
		NULL,
		NULL,
		NULL,
		szMaskLayerClassName,
		NULL
	};
	return  RegisterClassEx(&wndClass);
}

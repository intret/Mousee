/// 
/// Copyright (C) 2011, intret. All rights reserved.
/// 
/// @file   MainWindow.h
/// @author 
/// @date   2011.9.17
/// @brief  
/// 
//////////////////////////////////////////////////////////////////////////
#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "BaseWindow.h"
#include <dwmapi.h>

//BOOL InitControls(HINSTANCE hInstance, HWND hWndMain );



ATOM	RegisterMainWndClass(HINSTANCE hInstance, TCHAR *pszWindowClass );

LRESULT OnMouseMove( HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT OnMouseWheel(HWND hWnd, WPARAM wParam, LPARAM lParam);
VOID	OnSystemNotifyIcon( HWND hWnd, WPARAM wParam, LPARAM lParam );
LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
VOID	OnMiddleButtonClicked( HWND hWndMain, WPARAM wParam, LPARAM lParam );
VOID	ShowTrayContextMenu( HWND hWndMain, WPARAM wParam, LPARAM lParam );
VOID	OnContextMenuAbout(HWND hWndMain);
VOID	OnContexMenuMiddleButtonCloseWindow();
VOID	OnContextMenuSelectWindow();
class MainWindow : public BaseWindow<MainWindow>
{
public:
	MainWindow();
	~MainWindow();

	INT Create();


	INT Show();
	INT Close();

private:
	VOID Destroy();

};

#endif // MAINWINDOW_H_

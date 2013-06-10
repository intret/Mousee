/// 
/// Copyright (C) 2011, intret. All rights reserved.
/// 
/// @file   SystemNotifyIcon.h
/// @author 
/// @date   2011.9.17
/// @brief  
/// 
//////////////////////////////////////////////////////////////////////////
#ifndef SYSTEMNOTIFYICON_H_
#define SYSTEMNOTIFYICON_H_

#include <Windows.h>
#include <ShellAPI.h>


class SystemNotifyIcon
{
public:
	SystemNotifyIcon(void);
	~SystemNotifyIcon(void);
	// 
	// icon support:
	// Windows 2K : system depth icon
	// Windows XP : up to 32 BPP icon
	// 
	int Create( HWND hWnd, UINT uCallbackMesssage, HICON hIcon );
	int Create( HWND hWnd, UINT uCallbackMesssage, WORD wIcon );
	bool Show();
	void Add( HWND hWndReceiver );
	void Modify();
	void Del();

	UINT GetIconID();

	static HICON loadIcon( WORD wID );

private:
	void Init();
	void Destroy();

	static UINT		MakeShellID();
	static UINT		_shellIconID;

	UINT			_myIconID;
	NOTIFYICONDATA	_notifyIconData;
};

#endif // SYSTEMNOTIFYICON_H_

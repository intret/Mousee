#include "StdAfx.h"
#include "SystemNotifyIcon.h"


UINT SystemNotifyIcon::_shellIconID = 0x9523;

SystemNotifyIcon::SystemNotifyIcon(void) :
	_myIconID(0)
{
	Init();
}

SystemNotifyIcon::~SystemNotifyIcon(void)
{
	Destroy();
}

void SystemNotifyIcon::Init()
{
	ZeroMemory( &_notifyIconData, sizeof(NOTIFYICONDATAA) );
}

UINT SystemNotifyIcon::MakeShellID()
{
	return _shellIconID++;
}

HICON SystemNotifyIcon::loadIcon( WORD wID )
{
	return LoadIcon( GetModuleHandle(NULL), MAKEINTRESOURCE(wID) );
}

int SystemNotifyIcon::Create( HWND hWnd, UINT uMsg, HICON hIcon )
{
	if ( hWnd == NULL || hIcon == NULL)
	{
		return 1;
	}

	_notifyIconData.cbSize = sizeof( sizeof(NOTIFYICONDATAA) );
	_notifyIconData.hWnd = hWnd;
	_notifyIconData.hIcon = hIcon;
	_notifyIconData.uFlags |= NIF_ICON;
	_notifyIconData.uCallbackMessage = uMsg;
	_notifyIconData.uFlags |= NIF_MESSAGE;
	_notifyIconData.uID = _myIconID = MakeShellID();

	//_notifyIconData.uVersion = NOTIFYICON_VERSION;

 	return 0;
}

int SystemNotifyIcon::Create( HWND hWnd, UINT uMsg, WORD wIcon )
{
	if (hWnd == NULL )
	{
		return 1;
	}

	HICON hIcon = LoadIcon( GetModuleHandle(NULL), MAKEINTRESOURCE(wIcon) );
	return Create( hWnd, uMsg, hIcon );
}

bool SystemNotifyIcon::Show()
{
	return (TRUE == Shell_NotifyIcon(NIM_ADD, &_notifyIconData ));
}

void SystemNotifyIcon::Destroy()
{
	if ( _myIconID > 0 )
	{
		Shell_NotifyIcon( NIM_DELETE, &_notifyIconData ); 
		_myIconID = 0;
	}
}

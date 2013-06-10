#include "StdAfx.h"
#include "SystemUtility.h"


SystemUtility::SystemUtility(void)
{
}

SystemUtility::~SystemUtility(void)
{
}

UINT SystemUtility::RunAtSystemStartup( LPCTSTR lpszKey,
								   LPCTSTR lpszAppPath, 
								   BOOL bUserOrLocalMachine )
{
	HKEY	hKeyRun = NULL;
	LONG	retVal = 0;
	DWORD	dwLastError = 0;
	LPCTSTR lpszSubKey = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run\\");
	TCHAR	szModulePath[MAX_PATH] = { 0 };

	if ( NULL == lpszAppPath)
	{	
		GetModuleFileName( NULL, szModulePath, MAX_PATH );
	}
	//TCHAR	ptStr = _tcsrchr( szModulePath, _T('\\') );
	//(*ptStr) = _T('\0');
	
	retVal = RegOpenKeyEx( (bUserOrLocalMachine ? HKEY_CURRENT_USER : HKEY_LOCAL_MACHINE), 
		lpszSubKey, 0, KEY_WRITE | KEY_READ, &hKeyRun );
	if ( retVal != ERROR_SUCCESS )
	{
		return retVal;
	}

	//DWORD dwDisposition = 0;
	//retVal = RegCreateKeyEx( 
	//	bCurrentUserOrLocalMachine ? HKEY_CURRENT_USER : HKEY_LOCAL_MACHINE, 
	//	lpszKey, 
	//	0, 
	//	NULL, 
	//	REG_OPTION_VOLATILE, 
	//	KEY_WRITE, 
	//	NULL, 
	//	&hKeyRun,
	//	&dwDisposition
	//	);
	//if ( ERROR_SUCCESS != retVal )
	//{
	//	RegCloseKey( hKeyRun );
	//	return retVal;
	//}

	//retVal = RegSetKeyValue( hKeyRun, NULL, _T("Mousee"), REG_SZ, (lpszAppPath == NULL) ? szModulePath : lpszAppPath, _tcslen(szModulePath) * sizeof(TCHAR) );
	retVal = RegSetValueEx ( hKeyRun, _T("Mousee"), 0, REG_SZ, 
		(const BYTE*)((lpszAppPath == NULL) ? szModulePath : lpszAppPath), 
		_tcslen(szModulePath) * sizeof(TCHAR) );

	if ( ERROR_SUCCESS != retVal )
	{
		dwLastError = GetLastError();
		RegCloseKey( hKeyRun );
		return dwLastError;
	}		
 
	RegCloseKey( hKeyRun );
	return ERROR_SUCCESS;
}

UINT SystemUtility::DeleteRunKey( LPCTSTR lpszValueName, BOOL bUserOrLocalMachine )
{
	HKEY	hRunKey = NULL;
	LONG	lResult = 0;
	DWORD	dwLastError = 0;
	LPCTSTR lpszSubKey = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run");

	DWORD dwDisposition = 0;
	lResult = RegOpenKeyEx( 
		bUserOrLocalMachine ? HKEY_CURRENT_USER : HKEY_LOCAL_MACHINE, 
		lpszSubKey, 
		0, 
		KEY_READ | KEY_WRITE, 
		&hRunKey
		);
	if ( ERROR_SUCCESS != lResult )
	{
		dwLastError = GetLastError();
		return dwLastError;
	}

	lResult = RegDeleteValue( hRunKey, lpszValueName );
	if ( ERROR_SUCCESS != lResult )
	{
		dwLastError = GetLastError();
		RegCloseKey( hRunKey );
		return dwLastError;
	}

	return 0;
}


/**
 * @brief RegValueExist 
 * 
 * @param hKey
 * @param lpszSubKey
 * @param lpszValueName
 * @retval 0 存在.
 * @retval other 不存在，返回Last Error错误号.
 * @return UINT 
 */
UINT SystemUtility::RegValueExist( HKEY hKey, LPCTSTR lpszSubKey, LPCTSTR lpszValueName )
{
	HKEY	hKeyResult = NULL;
	LONG	retVal = 0;
	DWORD	dwLastError = 0;

	retVal = RegOpenKeyEx( 	hKey, lpszSubKey, 
		0, KEY_WRITE | KEY_READ, &hKeyResult );
	if ( retVal != ERROR_SUCCESS )
	{
		return GetLastError();
	}

	DWORD	dwType = 0;
	TCHAR	szBuffer[MAX_PATH];
	DWORD	dataLen = sizeof(szBuffer) * sizeof(TCHAR);
	retVal = RegQueryValueEx( 
		hKeyResult, 
		lpszValueName, 
		0,
		&dwType, 
		(BYTE*)szBuffer, 
		&dataLen
		);
	RegCloseKey(hKeyResult);
	return retVal == ERROR_SUCCESS ? 0 : retVal;
}

UINT SystemUtility::GetRegValue( LPCTSTR hKey, LPCTSTR lpszSubKey, LPTSTR lpszResultValue )
{

	return 0;
}

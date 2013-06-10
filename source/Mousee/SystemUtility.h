/// 
/// Copyright (C) 2011, intret. All rights reserved.
/// 
/// @file   SystemUtility.h
/// @author 
/// @date   2011.9.17
/// @brief  
/// 
//////////////////////////////////////////////////////////////////////////

#ifndef SYSTEMUTILITY_H_
#define SYSTEMUTILITY_H_

class SystemUtility
{
public:
	SystemUtility(void);
	~SystemUtility(void);

	static UINT RunAtSystemStartup( LPCTSTR lpszKey, LPCTSTR lpszAppPath, LPCTSTR lpszParameters, BOOL bUserOrLocalMachine );
	static UINT RunAtSystemStartup( LPCTSTR lpszKey, LPCTSTR lpszAppPath, BOOL bUserOrLocalMachine );
	static UINT DeleteRunKey( LPCTSTR lpszValueName, BOOL bUserOrLocalMachine );
	static UINT RegValueExist( HKEY hKey, LPCTSTR lpszSubKey, LPCTSTR lpszValueName );
	static UINT GetRegValue( LPCTSTR hKey, LPCTSTR lpszSubKey, LPTSTR lpszResultValue );
};

#endif // SYSTEMUTILITY_H_

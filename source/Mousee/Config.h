/// 
/// Copyright (C) 2011, intret. All rights reserved.
/// 
/// @file   Config.h
/// @author 
/// @date   2011.9.17
/// @brief  
/// 
//////////////////////////////////////////////////////////////////////////
#ifndef GLOBALCONFIG_H_
#define GLOBALCONFIG_H_

#include <map>
#include <string>
using namespace std;

class Config
{
public:
	Config(void);
	~Config(void);

	map<string, string>			config()		{ return _configs; }
	const map<string, string>	config() const	{ return _configs; }

	void	SetConfig( string name, string value );
	void	GetConfig( string name, string& value );
	string	GetConfig( string name );
	string& operator [](string key){ return _configs[key]; }

private:
	map<string, string> _configs;
};

#endif // CONFIG_H_

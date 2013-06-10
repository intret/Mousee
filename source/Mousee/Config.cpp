#include "StdAfx.h"
#include "Config.h"

Config::Config(void)
{
}

Config::~Config(void)
{
}

void Config::SetConfig( string configName, string configValue )
{
	if ( !configName.empty() )
	{
		_configs[configName] = configValue;
	}
}

void Config::GetConfig( string configName, string& configValue )
{
	configValue = _configs[configName];
}


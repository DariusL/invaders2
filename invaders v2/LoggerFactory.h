#pragma once
#include "includes.h"
#include "Logger.h"

class LoggerFactory
{
public:
	using LoggerType = Logger;
	static LoggerType Create()
	{
		return Logger("Log.txt");
	}
};
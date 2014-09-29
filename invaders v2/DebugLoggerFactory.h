#pragma once
#include "includes.h"
#include "DebugLogger.h"

class DebugLoggerFactory
{
public:
	using LoggerType = DebugLogger;
	static LoggerType Create()
	{
		return DebugLogger();
	}
};
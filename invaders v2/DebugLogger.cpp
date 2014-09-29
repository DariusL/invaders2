#include "includes.h"
#include "DebugLogger.h"

DebugLogger::DebugLogger()
{
}

void DebugLogger::Log(e::string line)
{
	e::stringstream ss;
	ss << line << e::endl;
	OutputDebugStringA(ss.str().c_str());
}
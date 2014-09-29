#pragma once
#include "includes.h"
class Logger
{
	e::ofstream output;
public:
	Logger(e::string file);
	Logger(Logger&) = delete;
	Logger(Logger&&);

	void Log(e::string line);
};
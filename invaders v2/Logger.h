#pragma once
#include "includes.h"
using namespace std;
class Logger
{
	static const char *FILE;
	ofstream output;
public:
	Logger(void);
	~Logger(void);

	bool Init();
	void Log(string line);
};


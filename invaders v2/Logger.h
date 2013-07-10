#pragma once
#include <string>
#include <fstream>
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


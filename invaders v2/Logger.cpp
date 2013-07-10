#include "Logger.h"

const char *Logger::FILE = "Log.txt";

Logger::Logger(void)
{
}

Logger::~Logger(void)
{
	output.close();
}

bool Logger::Init()
{
	output.open(FILE, ios::out);
	return output.is_open();
}

void Logger::Log(string line)
{
	output << line << endl;
}
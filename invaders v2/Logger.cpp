#include "includes.h"
#include "Logger.h"

Logger::Logger(e::string file)
	:output(file, e::ios::app)
{
}

Logger::Logger(Logger &&other)
	: output(e::move(other.output))
{
}


void Logger::Log(e::string line)
{
	output << line << e::endl;
}
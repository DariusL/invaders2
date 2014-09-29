#pragma once
#include "includes.h"

template<typename... Factories>
class LoggerManager;

template<typename Factory, typename... Factories>
class LoggerManager<Factory, Factories...> : public LoggerManager<Factories...>
{
private:
	using Logger = typename Factory::LoggerType;
	Logger logger;
public:
	LoggerManager() 
		:LoggerManager<Factories...>(),
		logger(Factory::Create()){}

	inline void Log(e::string msg)
	{
		logger.Log(msg);
		LoggerManager<Factories...>::Log(msg);
	}
};

template<>
class LoggerManager<>
{
public:
	LoggerManager(){}
	inline void Log(e::string msg){}
};

template<typename... Factories>
void Log(e::string msg)
{
	static LoggerManager<Factories...> manager;
	manager.Log(msg);
}
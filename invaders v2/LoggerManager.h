#pragma once
#include "includes.h"

template<typename... Factories>
class LoggerManager;

template<typename... Factories>
class LoggerHelper;

template<typename Factory, typename... Factories>
class LoggerManager<Factory, Factories...> : public LoggerManager<Factories...>
{
	friend class LoggerHelper<Factory, Factories...>;

private:
	using Logger = typename Factory::LoggerType;
	Logger logger;
protected:
	LoggerManager()
		:LoggerManager<Factories...>(),
		logger(Factory::Create()){}

public:
	LoggerManager(LoggerManager&) = delete;
	LoggerManager(LoggerManager&&) = delete;
	inline void Log(e::string msg)
	{
		logger.Log(msg);
		LoggerManager<Factories...>::Log(msg);
	}
};

template<>
class LoggerManager<>
{
	friend class LoggerHelper<>;

protected:
	LoggerManager(){}

public:
	LoggerManager(LoggerManager&) = delete;
	LoggerManager(LoggerManager&&) = delete;
	inline void Log(e::string msg){}
};

template<typename... Factories>
class LoggerHelper
{
public:
	static void Log(e::string msg)
	{
		static LoggerManager<Factories...> manager;
		manager.Log(msg);
	}
};
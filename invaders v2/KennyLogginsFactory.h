#pragma once
#include "includes.h"
#include "KennyLoggins.h"

class KennyLogginsFactory
{
public:
	using LoggerType = KennyLoggins;
	static LoggerType Create()
	{
		return KennyLoggins();
	}
};
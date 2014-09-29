#pragma once
class KennyLoggins
{
private:
	e::vector<e::string> lyrics;
	e::ofstream output;
	int id;
public:
	KennyLoggins();
	KennyLoggins(KennyLoggins&) = delete;
	KennyLoggins(KennyLoggins&&);
	void Log(e::string msg);
};


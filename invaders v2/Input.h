#pragma once
class Input
{
public:
	Input();
	~Input();

	void KeyDown(UINT key);
	void KeyUp(UINT key);

	bool IsKeyDown(UINT key);
private:
	bool keys[256];
};
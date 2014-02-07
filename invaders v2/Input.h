#pragma once
class Input
{
public:
	Input();
	~Input();

	void KeyDown(int key);
	void KeyUp(int key);

	static bool IsKeyDown(int key);
private:
	bool keys[256];
	static Input *handle;
};
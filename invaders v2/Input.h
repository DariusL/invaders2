#pragma once
class Input
{
public:
	enum ACTION
	{
		ACTION_LEFT,
		ACTION_RIGHT,
		ACTION_FIRE,
		ACTION_UP,
		ACTION_DOWN,
		ACTION_ESC,
		ACTION_ENTER,

		LAST_ACTION_ENTRY
	};
	Input();
	~Input();

	void KeyDown(int key);
	void KeyUp(int key);

	const e::vector<bool> &Loop();
private:
	bool keys[256];
	static const e::vector<e::pair<int, ACTION>> keyAction;
	e::vector<bool> actions;
};

using InputType = const e::vector<bool>&;
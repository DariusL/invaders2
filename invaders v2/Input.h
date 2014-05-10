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
		ACTION_BACK,
		ACTION_ENTER,
		ACTION_UPGRADE,

		LAST_ACTION_ENTRY
	};
	Input();
	~Input();

	void KeyDown(int key);
	void KeyUp(int key);

	const e::vector<bool> &Loop();
	static Input &Get(){ return *instance;}
	int GetLastKey(){ return lastKey; }
	static e::string DecodeKey(int key);
	void LoadKeys();
private:
	bool keys[256];
	e::vector<e::pair<int, ACTION>> keyAction;
	e::vector<bool> actions;
	int lastKey;
	static Input *instance;
};

using InputType = const e::vector<bool>&;
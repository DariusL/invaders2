#pragma once
#include "includes.h"
#include "GameEntity.h"
template<typename... Args>
class Observers
{
public:
	enum EVENT
	{
		EVENT_ENEMY_DEATH,
		EVENT_PLAYER_BULLET_CREATE,
		EVENT_ENEMY_CREATE,
		EVENT_ENEMY_BULLET_CREATE
	};
private:
	static e::unordered_map<int, e::vector<e::function<void(Args...)>>> observers;

public:
	template<typename Observer>
	static void Register(int ev, Observer &&observer)
	{
		observers[ev].push_back(e::forward<Observer>(observer));
	}

	static void Notify(int ev, Args... args)
	{
		try
		{
			auto &obs = observers.at(ev);
			for (auto &o : obs)
				o(args...);
		}
		catch (...){}
	}

	static void Cleanup()
	{
		observers.clear();
	}
};

template<typename... Args>
e::unordered_map<int, e::vector<e::function<void(Args...)>>> Observers<Args...>::observers;

using GameObservers = Observers < const e::shared_ptr<GameEntity> > ;
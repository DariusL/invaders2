#pragma once
#include "includes.h"
#include "GameEntity.h"
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
	static e::unordered_map<int, e::vector<e::function<void(const e::shared_ptr<GameEntity>)>>> observers;

public:
	template<typename Observer>
	static void Register(int ev, Observer &&observer)
	{
		observers[ev].push_back(e::forward<Observer>(observer));
	}

	static void Notify(int ev, const e::shared_ptr<GameEntity> entity)
	{
		try
		{
			auto &obs = observers.at(ev);
			for (auto &o : obs)
				o(entity);
		}
		catch (...){}
	}

	static void Cleanup()
	{
		observers.clear();
	}
};
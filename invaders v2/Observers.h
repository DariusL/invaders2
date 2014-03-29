#pragma once
#include "includes.h"
#include "GameEntity.h"
class Observers
{
public:
	enum EVENT
	{
		EVENT_ENEMY_DEATH,
		EVENT_PLAYER_CREATE,
		EVENT_ENEMY_CREATE
	};
private:
	static e::unordered_map<int, e::function<void(const e::shared_ptr<GameEntity>)>> observers;

public:
	template<typename Observer>
	static void Register(EVENT ev, Observer &&observer)
	{
		observers.emplace(ev, e::forward<Observer>(observer));
	}

	static void Notify(int ev, const e::shared_ptr<GameEntity> entity)
	{
		try
		{
			observers.at(ev)(entity);
		}
		catch (...){}
	}
};
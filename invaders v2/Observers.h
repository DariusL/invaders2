#pragma once
#include "includes.h"
#include "GameEntity.h"
template<typename... Args>
class Observers
{
private:
	e::unordered_map<int, e::vector<e::function<void(Args...)>>> observers;
	static Observers<Args...> *instance;
public:
	Observers()
	{
		instance = this;
	}

	template<typename Observer>
	static void Register(int ev, Observer &&observer)
	{
		instance->observers[ev].push_back(e::forward<Observer>(observer));
	}

	static void Notify(int ev, Args... args)
	{
		try
		{
			auto &obs = instance->observers.at(ev);
			for (auto &o : obs)
				o(args...);
		}
		catch (...){}
	}
};

template<typename... Args>
Observers<Args...> *Observers<Args...>::instance;

using GameObservers = Observers < const e::shared_ptr<GameEntity> > ;
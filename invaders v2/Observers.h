#pragma once
#include "includes.h"
#include "GameEntity.h"
template<typename... Args>
class Observers
{
public:
	using funcs = e::list<e::function<void(Args...)>>;
	using it = typename funcs::const_iterator;
private:
	static e::unordered_map<int, funcs> observers;
public:
	class ObserverScopeRef;

	Observers() = delete;

	template<typename Observer>
	static ObserverScopeRef Register(int ev, Observer &&observer)
	{
		auto &f = observers[ev];
		f.push_back(e::forward<Observer>(observer));
		return ObserverScopeRef(ev, e::prev(f.end()));
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

private:

	static void Remove(int key, it iterator)
	{
		observers[key].erase(iterator);
	}
public:

	class ObserverScopeRef
	{
		it iterator;
		int key;
		bool init;
		using Parent = Observers<Args...>;
	public:
		ObserverScopeRef(int key, it iterator) : key(key), iterator(iterator), init(true){}
		ObserverScopeRef() : init(false){}
		~ObserverScopeRef()
		{
			if (init)
				Parent::Remove(key, iterator);
		}
		ObserverScopeRef(ObserverScopeRef&) = delete;
		ObserverScopeRef(ObserverScopeRef &&other)
			:key(other.key), iterator(other.iterator), init(other.init)
		{
			other.init = false;
		}
		ObserverScopeRef& operator=(ObserverScopeRef&) = delete;
		ObserverScopeRef& operator=(ObserverScopeRef &&other)
		{
			if (this != &other)
			{
				init = other.init;
				key = other.key;
				iterator = other.iterator;
				other.init = false;
			}
			return *this;
		}
	};
};

template<typename... Args>
e::unordered_map<int, typename Observers<Args...>::funcs> Observers<Args...>::observers;

using GameObservers = Observers < const e::shared_ptr<GameEntity> > ;
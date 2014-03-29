#include "includes.h"
#include "Observers.h"

e::unordered_map<int, e::function<void(const e::shared_ptr<GameEntity>)>> Observers::observers;
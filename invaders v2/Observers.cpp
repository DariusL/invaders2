#include "includes.h"
#include "Observers.h"

e::unordered_map<Observers::EVENT, e::function<void(const e::shared_ptr<GameEntity>)>> Observers::observers;
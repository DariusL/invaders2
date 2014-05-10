#include "includes.h"
#include "GameScreen.h"
#include "PauseMenu.h"
#include "Direct3D.h"
#include "Observers.h"
#include "UpgradeMenu.h"

GameScreen::GameScreen(e::XMVECTOR pos)
:Screen(pos), pause(Input::ACTION_BACK), world(Direct3D::GetDevice(), pos),
score(pos + Utils::VectorSet(25.0f, -10.0f), "SCORE", 15.0f),
exp(pos + Utils::VectorSet(25.0f, -12.0f), "EXP", 15.0f),
upgrade(Input::ACTION_UPGRADE)
{
	or = GameObservers::Register(GAME_EVENT_ENEMY_DEATH, e::bind(&GameScreen::UpdateCounters, this, e::placeholders::_1));
	ur = UpgradeObservers::Register(UPGRADE_EVENT_EXP_SET, e::bind(&Counter::SetCount, &exp, e::placeholders::_1));
}

void GameScreen::RenderInternal(const RenderParams &params)
{
	world.Render(params);
	score.Render(params);
	exp.Render(params);
}

int GameScreen::LoopInternal(InputType input, int frame)
{
	if (childResult == RESULT_QUIT_APP || childResult == RESULT_QUIT_TO_MAIN)
		return childResult;
	if (pause.Register(input))
		child = e::make_unique<PauseMenu>(e::XMLoadFloat3(&pos));
	if (upgrade.Register(input))
		child = e::make_unique<UpgradeMenu>(e::XMLoadFloat3(&pos), GetPlayerData());
	world.Loop(input, frame);
	return RESULT_CONTINUE;
}

void GameScreen::DelayInternal()
{
	pause.Reset();
	upgrade.Reset();
}

void GameScreen::UpdateCounters(const e::shared_ptr<GameEntity> entity)
{
	score += 10;
	exp += 1;
}

e::unordered_map<int, int> GameScreen::GetPlayerData()
{
	e::unordered_map<int, int> ret;
	ret[UPGRADE_EVENT_EXP_SET] = exp.GetValue();
	auto moarRet = world.GetPlayerData();
	ret.insert(moarRet.begin(), moarRet.end());
	return ret;
}
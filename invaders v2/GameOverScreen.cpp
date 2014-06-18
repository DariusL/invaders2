#include "includes.h"
#include "GameOverScreen.h"
#include "StringPool.h"
#include "ResourceManager.h"
#include "GameEntity.h"
#include "Utils.h"

using namespace e;

GameOverScreen::GameOverScreen(e::XMVECTOR pos, int score)
	:Screen(pos),
	enter(Input::ACTION_ENTER),
	esc(Input::ACTION_BACK),
	message(StringPool::Get().GetString("YOU TRIED"), RM::Get().GetShader<ColorShader>(), e::make_shared<GameEntity>(pos + Utils::VectorSet(0.0f, 10.0f))),
	score(pos, "FINAL SCORE", 20.0f, score)
{
}

void GameOverScreen::RenderInternal(RenderParams &params)
{
	message.Render(params);
	score.Render(params);
}

int GameOverScreen::LoopInternal(InputType input, int frame)
{
	if (enter.Register(input))
		return RESULT_QUIT_TO_MAIN;

	if (esc.Register(input))
		return RESULT_QUIT_TO_MAIN;

	return RESULT_CONTINUE;
}

void GameOverScreen::DelayInternal()
{
	enter.Reset();
	esc.Reset();
}
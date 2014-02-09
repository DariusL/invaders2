#include "includes.h"
#include "GameScreen.h"
#include "PauseMenu.h"

void GameScreen::RenderInternal(const RenderParams &params)
{

}

int GameScreen::LoopInternal(int input, float frame)
{
	if (childResult == RESULT_QUIT_APP || childResult == RESULT_QUIT_TO_MAIN)
		return childResult;
	if (pause.Register())
		child = e::make_unique<PauseMenu>(e::XMLoadFloat3(&pos));
	return RESULT_CONTINUE;
}

void GameScreen::DelayInternal()
{
	pause.Reset();
}
#include "includes.h"
#include "GameScreen.h"
#include "PauseMenu.h"
#include "Direct3D.h"

GameScreen::GameScreen(e::XMVECTOR pos)
:Screen(pos), pause(KEYS_ESC), world(Direct3D::GetDevice(), pos)
{}

void GameScreen::RenderInternal(const RenderParams &params)
{
	world.Render(params);
}

int GameScreen::LoopInternal(int input, int frame)
{
	if (childResult == RESULT_QUIT_APP || childResult == RESULT_QUIT_TO_MAIN)
		return childResult;
	if (pause.Register())
		child = e::make_unique<PauseMenu>(e::XMLoadFloat3(&pos));
	world.Loop(frame);
	return RESULT_CONTINUE;
}

void GameScreen::DelayInternal()
{
	pause.Reset();
}
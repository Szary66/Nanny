#include "Basic.h"

CBasic::CBasic (SDL_Renderer* rend, CStateGame* state)
:renderer (rend), state (state)
{
	keyboard = new CKeyboard ();
	player = new CPlayer (keyboard, 3, renderer, state, &xCamera, &yCamera);
}


CBasic::~CBasic ()
{
	delete player;
	delete keyboard;
}


void CBasic::mainGameLoop ()
{

	while ( state->state == CStateGame::playGame)
	{
		begin ();

		player->update ();
		
		draw ();
		end ();
	}	
}


void CBasic::begin ()const
{
	SDL_RenderClear (renderer);
	keyboard->pollEvent ();
}


void CBasic::end ()const
{
	SDL_RenderPresent (renderer);
}


void CBasic::draw ()const
{
	player->getSprite ()->draw ();
}



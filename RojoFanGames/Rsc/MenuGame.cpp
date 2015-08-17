#include "MenuGame.h"


CMenuBeginGame::CMenuBeginGame (SDL_Renderer* rend, int w, int h, CStateGame* state)
:Menu::CBaseGame (rend, w, h, state) 
{	
	textMenu.push_back (new Engine::Text::COut ("../Date/AFGAN.TTF", "NEW GAME", renderer, setX (), 70, setX (), 70, 50, Engine::CColor::BROWN));
	textMenu.push_back (new Engine::Text::COut (textMenu [0]->font.getFont (), "MAP EDITOR", renderer, setX (), 140, setX (), 70, 50, Engine::CColor::BLACK));
	textMenu.push_back (new Engine::Text::COut (textMenu [0]->font.getFont (), "LOAD GAME", renderer, setX (), 210, setX (), 70, 50, Engine::CColor::BLACK));
	textMenu.push_back (new Engine::Text::COut (textMenu [0]->font.getFont (), "OPTIONS GAME", renderer, setX (), 280, setX (), 70, 50, Engine::CColor::BLACK));
	textMenu.push_back (new Engine::Text::COut (textMenu [0]->font.getFont (), "EXIT GAME", renderer, setX (), 350, setX (), 70, 50, Engine::CColor::BLACK));

	select = textMenu.begin ();
}


CMenuBeginGame::~CMenuBeginGame ()
{
}


void CMenuBeginGame::loop ()
{
	while ( state->state == CStateGame::mainMenu)
	{
		begin ();
		update ();
		draw ();
		end ();
	}
}


void CMenuBeginGame::update ()
{
	if ( event.keyboard->isPressed () == true && event.keyboard->pressed == false )
	{
		event.keyboard->pressed = true;

		switch ( event.keyboard->getEvent ()->key.keysym.sym )
		{
		case SDLK_UP:
			selectkUp ();
			break;
		case SDLK_DOWN:
			selectDown ();
			break;
		case SDLK_SPACE:
			doIt ();
			break;
		default:
			break;
		}
	}
	else
		event.keyboard->pressed = event.keyboard->isPressed ();
}


void CMenuBeginGame::doIt ()
{
	if ( select == textMenu.end () - 1 )
		state->state = CStateGame::exitGame;
	else if ( select == textMenu.begin () + 1 )
		state->state = CStateGame::mapEditor;
	else if ( select == textMenu.begin () + 2 )
		state->state = CStateGame::loadGame;
	else if ( select == textMenu.begin () + 3 )
		state->state = CStateGame::optionGame;
	else if ( select == textMenu.begin () )
		state->state = CStateGame::playGame;
}
 

CMenuBreakGame::CMenuBreakGame (SDL_Renderer* rend, int w, int h, CStateGame* state)
:Menu::CBaseGame (rend, w, h, state)
{
	textMenu.push_back (new Engine::Text::COut ("../Date/AFGAN.TTF", "RESUME GAME", renderer, setX (), 50, setX (), 70, 50, Engine::CColor::BROWN));
	textMenu.push_back (new Engine::Text::COut (textMenu [0]->font.getFont (), "LOAD GAME", renderer, setX (), 120, setX (), 70, 50, Engine::CColor::BLACK));
	textMenu.push_back (new Engine::Text::COut (textMenu [0]->font.getFont (), "SAVE GAME", renderer, setX (), 190, setX (), 70, 50, Engine::CColor::BLACK));
	textMenu.push_back (new Engine::Text::COut (textMenu [0]->font.getFont (), "OPTIONS GAME", renderer, setX (), 260, setX (), 70, 50, Engine::CColor::BLACK));
	textMenu.push_back (new Engine::Text::COut (textMenu [0]->font.getFont (), "EXIT TO MAIN MENU", renderer, setX (), 330, setX (), 70, 50, Engine::CColor::BLACK));

	select = textMenu.begin ();
}


CMenuBreakGame::~CMenuBreakGame ()
{
}


void CMenuBreakGame::doIt ()
{
	if ( select == textMenu.begin () )
		state->state = CStateGame::STATE::playGame;
	else if ( select == textMenu.begin () + 1 )
		state->state = CStateGame::loadGame;
	else if ( select == textMenu.begin () + 2 )
		state->state = CStateGame::saveGame;
	else if ( select == textMenu.begin () + 3 )
		state->state = CStateGame::optionGame;
	else if ( select == textMenu.end () - 1 )
		state->state = CStateGame::STATE::mainMenu;
}


void CMenuBreakGame::loop ()
{
	while ( state->state == CStateGame::pauseGame )
	{
		begin ();
		update ();
		draw ();
		end ();
	}
}


void CMenuBreakGame::update ()
{
	if ( event.keyboard->isPressed () == true && event.keyboard->pressed == false )
	{
		event.keyboard->pressed = true;

		switch ( event.keyboard->getEvent ()->key.keysym.sym )
		{
		case SDLK_UP:
			selectkUp ();
			break;
		case SDLK_DOWN:
			selectDown ();
			break;
		case SDLK_SPACE:
			doIt ();
			break;
		default:
			break;
		}
	}
	else
		event.keyboard->pressed = event.keyboard->isPressed ();
}
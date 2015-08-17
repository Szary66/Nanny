#include "HandlingGame.h"
#include "BaseMenu.h"

CHandlingGame::CHandlingGame (SDL_Renderer* rend, int w, int h)
:kindGame (nope), renderer (rend), mainMenu (nullptr), pauseMenu (nullptr), mapEditor (nullptr), optionsMenu (nullptr), width (w), height (h)
{
	state = new CStateGame (CStateGame::STATE::mainMenu);

	items.push_back (CBaseItems (renderer, "../Date/ground_", w, h, 1, Engine::CSprite::GROUND));
	items.push_back (CBaseItems (renderer, "../Date/obstancle_", w, h, 3, Engine::CSprite::OBSTANCLE));
	items.push_back (CBaseItems (renderer, "../Date/furniture_", w, h, 0, Engine::CSprite::FURNITURE));
	items.push_back (CBaseItems (renderer, "../Date/monster_", w, h, 0, Engine::CSprite::MOSTER));

	Menu::CBase basic(renderer, state, w, h);
}


CHandlingGame::~CHandlingGame ()
{
	delete state;
}


void CHandlingGame::loop ()
{
	while ( state->state != CStateGame::exitGame )
	{
		switch ( state->state )
		{
		case CStateGame::mainMenu:
			clearGame ();
			mainMenu = new CMenuBeginGame (renderer, width, height, state);
			mainMenu->loop ();
			delete mainMenu;
			break;
		case CStateGame::STATE::pauseGame:
			pauseMenu = new CMenuBreakGame (renderer, width, height, state);
			pauseMenu->loop ();
			delete pauseMenu;
			break;
		case CStateGame::STATE::playGame:
			if ( kindGame == nope )
				game = new CBasic(renderer, state);
			kindGame = gameplay;
			game->mainGameLoop ();
			break;
		case CStateGame::STATE::mapEditor:
			if ( kindGame == nope )
				mapEditor = new CMapEditor (renderer, state, items, width, height);
			kindGame = mapCreate;
			mapEditor->loop ();
			break;
		case CStateGame::STATE::optionGame:
			if ( game != nullptr )
				optionsMenu = new Options::CMain (renderer, state, CStateGame::pauseGame, width, height);
			else
				optionsMenu = new Options::CMain (renderer, state, CStateGame::mainMenu, width, height);
			optionsMenu->loop ();
			delete optionsMenu;
			break;
		case CStateGame::STATE::exitGame:
			continue;
			break;
		default:
			break;
		}
	}
}


void CHandlingGame::clearGame ()
{
	switch ( kindGame )
	{
	case nope:
		break;
	case gameplay:
		delete game;
		break;
	case mapCreate:
		delete mapEditor;
		break;
	default:
		break;
	}

	kindGame = nope;
}


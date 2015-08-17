#ifndef HANDINGGAME_H
#define HANDINGGAME_H
#pragma once
#include "stdafx.h"
#include "Basic.h"
#include "MenuGame.h"
#include "MapEditor.h"
#include "Options.h"

//Class is handing main status game
class CHandlingGame
{
public:
	CHandlingGame (SDL_Renderer*, int, int);
	~CHandlingGame ();

	void loop ();

private:
	//delete everything
	void clearGame ();

	CStateGame* state;
	CBasic* game;
	CMapEditor* mapEditor;
	CMenuBeginGame* mainMenu;
	CMenuBreakGame* pauseMenu;
	Options::CMain* optionsMenu;
	std::vector<CBaseItems> items;


	enum kindGame
	{
		nope, gameplay, mapCreate, optionsGame
	};

	kindGame kindGame;
	int width;
	int height;

	SDL_Renderer* renderer;
	
};

#endif
#ifndef STATEGAME_H
#define STATEGAME_H
#pragma once
#include "stdafx.h"

//Main status game
class CStateGame
{
public:
	enum STATE
	{
		mainMenu, pauseGame, playGame, loadGame, saveGame, mapEditor, optionGame, exitGame,
	};

	CStateGame (STATE);
	~CStateGame ();

	STATE state;
};

#endif
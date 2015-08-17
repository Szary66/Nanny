#ifndef MENUGAME_H
#define MENUGAME_H
#pragma once
#include "BaseMenu.h"

//Class present first menu
class CMenuBeginGame :public Menu::CBaseGame
{
public:
	CMenuBeginGame (SDL_Renderer*, int, int, CStateGame*);
	~CMenuBeginGame ();

	virtual void loop ();
private:
	virtual void doIt ();
	void update ();
};

//Class present menu break game
class CMenuBreakGame :public Menu::CBaseGame
{
public:
	CMenuBreakGame (SDL_Renderer*, int, int, CStateGame*);
	~CMenuBreakGame ();

	virtual void loop ();
private:
	virtual void doIt ();
	void update ();
};

#endif
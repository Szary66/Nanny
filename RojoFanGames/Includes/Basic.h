#ifndef BASIC_H
#define BASIC_H
#pragma once
#include "StateGame.h"
#include "stdafx.h"
#include "Player.h"
#include "Text.h"

//Class:: basic gameplay
class CBasic
{
public:
	CBasic (SDL_Renderer*, CStateGame*);
	~CBasic ();

	void mainGameLoop ();
private:
	//Clear screen
	void begin ()const;
	
	//Present renderer
	inline void end ()const;
	inline void draw ()const;

	CKeyboard* keyboard;
	CPlayer* player;
	CStateGame* state;

	SDL_Renderer* renderer;

	int xCamera;
	int	yCamera;
};

#endif
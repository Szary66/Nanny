#ifndef PLAYER_H
#define PLAYER_H
#pragma once
#include "StateGame.h"
#include "stdafx.h"
#include "Event.h"
#include "Move.h"

//Class present player's hero
class CPlayer
{
public:
	CPlayer (CKeyboard*, int speed, SDL_Renderer*, CStateGame*, int*, int*);
	~CPlayer ();

	Engine::CSprite* getSprite ()const{return boy;}

	//update player's move
	void update ();
private:
	Engine::CSprite* boy;

	CKeyboard* newEvent, lastEvent;
	CStateGame* state;
	CMove* move;
	CMoveDown down;
	CMoveUp up;
	CMoveRight right;
	CMoveLeft left;
	CStay stay;

	int speed;
};

#endif
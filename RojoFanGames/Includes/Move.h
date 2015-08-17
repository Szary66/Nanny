#ifndef MOVE_H
#define MOVE_H
#pragma once
#include "stdafx.h"
#include "Sprite.h"
class CMove
{
public:
	CMove ();
	~CMove ();

	virtual void move () = 0;
protected:
};


class CMoveDown :public CMove
{
public:
	CMoveDown (Engine::CSprite*, int*);
	virtual void move ();
private:
	Engine::CSprite* player;
	int* speed;
};


class CMoveUp :public CMove
{
public:
	CMoveUp (Engine::CSprite*, int*);
	virtual void move ();
private:
	Engine::CSprite* player;
	int* speed;
};


class CMoveLeft :public CMove
{
public:
	CMoveLeft (Engine::CSprite*, int*);
	virtual void move ();
private:
	Engine::CSprite* player;
	int* speed;
};


class CMoveRight :public CMove
{
public:
	CMoveRight (Engine::CSprite*, int*);
	virtual void move ();
private:
	Engine::CSprite* player;
	int* speed;
};

class CStay :public CMove
{
public:
	CStay (Engine::CSprite*);
	virtual void move ();
private:
	Engine::CSprite* player;
};
#endif
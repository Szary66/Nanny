#ifndef COLLISION_H
#define COLLISION_H
#pragma once
#include "stdafx.h"
#include "Event.h"
#include <cmath>

//Class: use collision
class CCollision
{
public:
	CCollision ();
	~CCollision ();

	//Mouse is on hte sprite
	bool mauseCollision (CMouse*, const SDL_Rect)const;

	//TWo textures collided
	bool TextureCollision (const SDL_Rect, const SDL_Rect)const;
};

#endif
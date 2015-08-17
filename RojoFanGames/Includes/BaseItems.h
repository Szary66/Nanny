#ifndef BASEITEMS_H
#define BASEITEMS_H
#pragma once
#include <sstream>
#include <vector>
#include <memory>
#include "stdafx.h"
#include "Sprite.h"
#include "Event.h"
#include "Collision.h"

//List loaded texturer of this kind
class CBaseItems  
{
public:
	CBaseItems (SDL_Renderer*, const std::string, const int, const int, const int, const Engine::CSprite::KIND);
	~CBaseItems ();

	//Get item
	Engine::CSprite getItem (const int);
	
	//Get kind of list
	Engine::CSprite::KIND getKind ();

	//Get sprite under mause
	Engine::CSprite* selectObject (CMouse*, CCollision&);

	//Draw all
	void draw ();

	//Draw one item
	void draw (int);

	//Get number of elements
	int getSize ()const;
protected:
	//List of sprites
	std::vector<Engine::CSprite*> pictures;
	
	void virtual loadTexture (SDL_Renderer*, std::string, int, int);
	void clear ();

	const Engine::CSprite::KIND kind;

	const int maxItems;
};

#endif
#ifndef MENAGERMAP_H
#define MENAGERMAP_H
#pragma once
#include "stdafx.h"
#include "FileStream.h"

//Class to handle class CMap
class CMenagerMap
{
public:
	CMenagerMap ();
	~CMenagerMap ();

	//if resolution is new conwer w and h tile 
	SDL_Rect convertTileMap (unsigned, unsigned);
private:
	void loadItems ();
	
	unsigned width;
	unsigned height;

	unsigned xTile;
	unsigned yTile;
};

#endif
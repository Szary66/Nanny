#include "MenagerMap.h"


CMenagerMap::CMenagerMap ()
{
	loadItems ();
}


CMenagerMap::~CMenagerMap ()
{}


SDL_Rect CMenagerMap::convertTileMap (unsigned x, unsigned y)
{
	SDL_Rect rect;

	rect.w = width / xTile;
	rect.h = height / yTile;

	rect.x = x * rect.w;
	rect.y = y * rect.h;

	return rect;
}


void CMenagerMap::loadItems ()
{
	File::CLoad load("../Date/mainSave.dat");
	
	if ( load.isOpen () )
	{
		load.bufforOnLine (8, File::FIND::FROM_END);		
		
	//	load.read (xTile);
	//	load.read (yTile);

		load.close ();
	}
}


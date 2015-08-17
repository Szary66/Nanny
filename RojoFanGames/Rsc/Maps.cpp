#include "stdafx.h"
#include "Maps.h"


CMaps::CMaps ( SDL_Renderer* rend, int xMaps, int yMaps, int width, int height)
: xMaps (xMaps), yMaps (yMaps), newMap (false), xNumberFields (20), yNumberFields (20), widthScreen (width), heightScreen (height)
{
	for ( int i = 0; i < xNumberFields; i++ )
	{
		for ( int j = 0; j < yNumberFields; j++ )
			fields [i][j] = new CFieldMap (rend, false, false);
	}
}


CMaps::CMaps (SDL_Renderer* rend, int width, int height)
: xMaps (1), yMaps (1), newMap (true), xNumberFields (20), yNumberFields (20), widthScreen (width), heightScreen (height)
{
	for ( int i = 0; i < xNumberFields; i++ )
	{
		for ( int j = 0; j < yNumberFields; j++ )
			fields [i][j] = new CFieldMap (rend, false, false);
	}
}


void CMaps::draw ()
{
	for ( int i = 0; i < xNumberFields; i++ )
	{
		for ( int j = 0; j < yNumberFields; j++ )
			fields [i][j]->draw ();
	}
}


void CMaps::save (File::Save::CSaveField &fout)
{
	for ( int i = 0; i < xNumberFields; i++ )
	for ( int j = 0; j < yNumberFields; j++ )
		fields [i][j]->save (fout, i, j);
}


void CMaps::load (File::Load::CLoadField  &fin, std::vector<CBaseItems> &temps)
{
	for ( int i = 0; i < xNumberFields; i++ )
	for ( int j = 0; j < yNumberFields; j++ )
		fields [i][j]->load (fin, temps);
}


void CMaps::setGroundOnMap (int x, int y, Engine::CSprite* texture)
{
	if ( y >=  heightScreen / yNumberFields)
	{
		SDL_Rect rect;
		rect.w = widthScreen / xNumberFields;
		rect.h = heightScreen / yNumberFields;

		x /= rect.w;
		y /= rect.h;

		if ( fields [y - 1][x]->isSubstatum () == false )
		{
			rect.x = x * rect.w;
			rect.y = y * rect.h;

			fields [y - 1][x]->setGroundOnMap (rect, texture);
		}
	}
}

void CMaps::setObstancleOnMap (int x, int y, Engine::CSprite* texture)
{
	if ( y >= heightScreen / yNumberFields )
	{
		SDL_Rect rect;
		rect.w = widthScreen / xNumberFields;
		rect.h = heightScreen / yNumberFields;

		x /= rect.w;
		y /= rect.h;

		if ( fields [y - 1][x]->isObstancle () == false && fields [y - 1][x]->isSubstatum () == true )
		{
			rect.x = x * rect.w;
			rect.y = y * rect.h;

			fields [y - 1][x]->setObstancleOnMap (rect, texture);
		}
	}
}


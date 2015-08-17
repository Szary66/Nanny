#include "stdafx.h"
#include "FieldMap.h"


CFieldMap::CFieldMap (SDL_Renderer* rend, bool ground, bool obstancle)
: renderer (rend), hurdle (obstancle), substratum (ground), ground (nullptr), obstancle (nullptr)
{}


CFieldMap::~CFieldMap ()
{
	if ( ground != nullptr )
		delete ground;

	if ( obstancle != nullptr )
		delete obstancle;
}


bool CFieldMap::isObstancle ()const
{
	return obstancle;
}


bool CFieldMap::isSubstatum ()const
{
	return substratum;
}


void CFieldMap::setGroundOnMap (SDL_Rect rect, Engine::CSprite* texture)
{
		ground = new Engine::CSprite(*texture);
		ground->rectSprite = rect;

		substratum = true;
}


void CFieldMap::setObstancleOnMap (SDL_Rect rect, Engine::CSprite* texture)
{
	obstancle = new Engine::CSprite (*texture);
	obstancle->rectSprite = rect;

	hurdle = true;
}


void CFieldMap::clearField (int x, int y)
{
	if ( hurdle )
	{
		delete obstancle;
		obstancle = nullptr;

		hurdle = false;
	}
	else if ( substratum )
	{
		delete ground;
		ground = nullptr;

		substratum = false;
	}
}


void CFieldMap::draw ()const
{
	if ( ground != nullptr )
		ground->draw ();
	if ( obstancle != nullptr )
		obstancle->draw ();
}


void CFieldMap::save (File::Save::CSaveField &fout, int &xPlate, int &yPlate)
{
	fout.saveHurdle (hurdle);
	fout.saveSubstratum (substratum);

	if ( substratum )
	{
		fout.saveNumberTexture (ground->kind, ground->numberOfTexture);
		fout.saveRect (ground->rectSprite);
	}
	
	if ( hurdle )
	{
		fout.saveNumberTexture (obstancle->kind, obstancle->numberOfTexture);
		fout.saveRect (obstancle->rectSprite);
	}
}


void CFieldMap::load (File::Load::CLoadField &fin, std::vector<CBaseItems> &temps)
{
	hurdle = fin.loadHurdle ();
	substratum = fin.loadSubstratum ();

	if ( substratum )
	{
		int ID;
		Engine::CSprite::KIND kind;

		fin.loadNumberTexture (kind, ID);
		ground = new Engine::CSprite( findTexture (temps, kind, ID));

		fin.loadRect (ground->rectSprite);
	}

	if ( hurdle )
	{
		Engine::CSprite::KIND kind;
		int ID;

		fin.loadNumberTexture (kind, ID);
		obstancle = new Engine::CSprite(findTexture (temps, kind, ID));

		fin.loadRect (obstancle->rectSprite);
	}
}


Engine::CSprite CFieldMap::findTexture (std::vector<CBaseItems> &itemps, Engine::CSprite::KIND kind, int ID)
{
	switch ( kind )
	{
	case Engine::CSprite::GROUND:
		return itemps [0].getItem (ID);
		break;
	case Engine::CSprite::OBSTANCLE:
		return itemps [1].getItem (ID);
		break;
	case Engine::CSprite::FURNITURE:
		return itemps [2].getItem (ID);
		break;
	case Engine::CSprite::MOSTER:
		return itemps [3].getItem (ID);
		break;
	default:
		break;
	}
}
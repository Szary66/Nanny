#ifndef FIELDMAP_H
#define FIELDMAP_H
#pragma once
#include <vector>
#include "BaseItems.h"
#include "LoadField.h"
#include "SaveField.h"
#include "MenagerMap.h"

//Class pressent one field of map
class CFieldMap
{
public:
	CFieldMap (SDL_Renderer*, bool, bool);
	~CFieldMap ();

	void draw ()const;

	//Create ground and set on this field
	void setGroundOnMap (SDL_Rect, Engine::CSprite*);

	//Create hurdle and set on this field if ground was creating
	void setObstancleOnMap (SDL_Rect, Engine::CSprite*);

	void clearField (int, int);
	
	//save items field
	void save (File::Save::CSaveField &, int&, int&);
	
	//load items field
	void load (File::Load::CLoadField &, std::vector<CBaseItems>&);

	bool isObstancle ()const;
	bool isSubstatum ()const;
private:
	//Find texture from base items list 
	Engine::CSprite findTexture (std::vector<CBaseItems>&, Engine::CSprite::KIND, int);

	SDL_Renderer* renderer;

	bool hurdle;
	bool substratum;

	Engine::CSprite* ground;
	Engine::CSprite* obstancle;

	CMenagerMap menager;
};

#endif
#ifndef MAPS_H
#define MAPS_H
#pragma once
#include "FieldMap.h"
#include <vector>

//Class implement full map
class CMaps
{
public:
	CMaps (SDL_Renderer*, int, int, int, int );
	CMaps (SDL_Renderer*, int, int);
	~CMaps (){}
	
	//send x,y and sprite to field map
	void setGroundOnMap (int, int, Engine::CSprite*);

	//sexd x,y and sprite to field map
	void setObstancleOnMap (int, int, Engine::CSprite*);
	void draw ();

	//send save pointer to CFieldMap
	void save (File::Save::CSaveField &);
	//send load pointer to CFieldMap
	void load (File::Load::CLoadField &, std::vector<CBaseItems>&);
private:
	int xMaps;
	int yMaps;
	
	const int xNumberFields;
	const int yNumberFields;

	const int widthScreen;
	const int heightScreen;

	bool newMap;

	CFieldMap* fields [20][20];
};

#endif
#ifndef MAPEDITOR_H
#define MAPEDITOR_H
#pragma once
#include <vector>
#include "Maps.h"
#include "StateGame.h"
#include "Event.h"
#include "MenuMapEditor.h"

//Main class map editor
class CMapEditor: Menu::CBase
{
public:
	CMapEditor (SDL_Renderer*, CStateGame*, std::vector<CBaseItems>&, int, int);
	~CMapEditor ();

	//loop to create map
	void loop ();
private:

	void draw ();
	
	//update click mause
	void update ();

	//Close menu or cantel to sprite on buffor
	void handleKeyESC ();

	void save ();
	void load ();
	void openMenuCategory ();
	void selectSprite ();
	
	//copy sprite on map
	void setSpriteOnMap ();

	bool openMenu;
	
	std::vector<CMaps> world;
	std::vector<CBaseItems> &items;

	Engine::CSprite* selectedOne;
	Engine::CSprite::KIND kind;

	Menu::CMapEditor* menu;

	
};

#endif
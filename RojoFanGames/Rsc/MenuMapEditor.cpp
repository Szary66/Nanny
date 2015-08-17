#include "MenuMapEditor.h"
using namespace Menu;
//MENU MAP EDITOR *********************************************************************************************************

CMapEditor::CMapEditor (SDL_Renderer* rend, CMouse* mouse, std::vector<CBaseItems> &items, int w, int h)
{
	obstancle = new Menu::CBaseEditor ("../Date/obstancle.png", rend, mouse, &items [1], Engine::CSprite::OBSTANCLE, w, h, 1);
	ground = new Menu::CBaseEditor ("../Date/ground.png", rend, mouse, &items [0], Engine::CSprite::GROUND, w, h, 0);
	furniture = new Menu::CBaseEditor ("../Date/furniture.png", rend, mouse, &items [2], Engine::CSprite::FURNITURE, w, h, 2);
	monster = new Menu::CBaseEditor ("../Date/monster.png", rend, mouse, &items [3], Engine::CSprite::MOSTER, w, h, 3);
}


CMapEditor::~CMapEditor ()
{}


void CMapEditor::draw ()
{
	ground->draw ();
	furniture->draw ();
	obstancle->draw ();
	monster->draw ();
}


bool CMapEditor::isOpen ()const
{
	return ( furniture->isOpen () || monster->isOpen () || obstancle->isOpen () || ground->isOpen () ) ? true : false;
}


bool CMapEditor::openCategories (Engine::CSprite::KIND &kind)
{
	if ( ground->openCategory () )
	{
		kind = ground->getSpriteKind ();
		category = ground;
		return true;
	}
	else if ( furniture->openCategory () )
	{
		kind = furniture->getSpriteKind ();
		category = furniture;
		return true;
	}
	else if ( obstancle->openCategory () )
	{
		kind = obstancle->getSpriteKind ();
		category = obstancle;
		return true;
	}
	else if ( monster->openCategory () )
	{
		kind = monster->getSpriteKind ();
		category = monster;
		return true;
	}
	else
	{
		kind = Engine::CSprite::EMPTY;
		category = nullptr;
		return false;
	}
}


Engine::CSprite* CMapEditor::selectSprite ()
{
	return category->selectObject ();
}
#ifndef MENUMAPEDITOR_H
#define MENUMAPEDITOR_H
#pragma once
#include "stdafx.h"
#include "BaseMenu.h"
#include "BaseItems.h"

namespace Menu
{
	//Class menu for map editor
	class CMapEditor
	{
	public:
		CMapEditor (SDL_Renderer*, CMouse*, std::vector<CBaseItems>&, int, int);
		~CMapEditor ();

		void draw ();

		bool openCategories (Engine::CSprite::KIND&);
		bool  isOpen ()const;

		Engine::CSprite* selectSprite ();

	private:
		//selected item pointer
		Menu::CBaseEditor* category;

		Menu::CBaseEditor* furniture;
		Menu::CBaseEditor* monster;
		Menu::CBaseEditor* obstancle;
		Menu::CBaseEditor* ground;
	};
}
#endif
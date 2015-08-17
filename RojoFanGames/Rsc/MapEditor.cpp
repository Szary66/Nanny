#include "stdafx.h"
#include "MapEditor.h"


CMapEditor::CMapEditor (SDL_Renderer* rend, CStateGame* state, std::vector<CBaseItems> &items, int w, int h)
:Menu::CBase (rend, state, w, h), selectedOne (nullptr), items (items)
{
	world.push_back (CMaps (renderer, w, h));
	menu = new Menu::CMapEditor (renderer, event.mouse, this->items, w, h);

	load ();

	kind = Engine::CSprite::EMPTY;
}


CMapEditor::~CMapEditor ()
{
	world.clear ();
}


void CMapEditor::loop ()
{
	while ( state->state == CStateGame::STATE::mapEditor )
	{
		begin ();

		update ();
		draw ();
		 
		end ();
	}
}


void CMapEditor::draw ()
{
	for (unsigned int i = 0; i < world.size (); i++ )
		world [i].draw ();
	
	menu->draw ();
}


void CMapEditor::openMenuCategory ()
{
	menu->openCategories (kind);
	event.mouse->pressed = true;
	selectedOne = nullptr;
}


void CMapEditor::selectSprite ()
{
	selectedOne = menu->selectSprite ();
	event.mouse->pressed = true;
}


void CMapEditor::setSpriteOnMap ()
{
	if ( kind == Engine::CSprite::GROUND )
	for (unsigned int i = 0; i < world.size (); i++ )
		world [i].setGroundOnMap (event.mouse->getMouseX (), event.mouse->getMouseY (), selectedOne);
	else
		for (unsigned int i = 0; i < world.size (); i++ )
			world [i].setObstancleOnMap (event.mouse->getMouseX (), event.mouse->getMouseY (), selectedOne);
}


void CMapEditor::handleKeyESC ()
{
	if ( selectedOne != nullptr )
	{
		event.keyboard->pressed = true;
		selectedOne = nullptr;
	}
	else if ( event.keyboard->pressed == false )
		state->state = CStateGame::mainMenu;
}


void CMapEditor::update ()
{
	if ( event.mouse->isPressed () && event.mouse->pressed == false )
	{
		if ( selectedOne == nullptr && menu->isOpen () == false )
		{
			openMenuCategory ();
		}
		else if ( selectedOne == nullptr && menu->isOpen () )
		{
			selectSprite ();
		}
		else if ( selectedOne != nullptr )
		{
			setSpriteOnMap ();
		}
	}
	else if ( event.keyboard->isPressed () )
	{
		if ( event.keyboard->getEvent ()->key.keysym.sym == SDLK_ESCAPE )
		{
			handleKeyESC ();
		}
		else if ( event.keyboard->getEvent ()->key.keysym.sym == SDLK_F5 )
			save ();
	}
	else 
	{
		event.mouse->pressed = event.mouse->isPressed ();
		event.keyboard->pressed = event.keyboard->isPressed ();
	}
}


void CMapEditor::save ()
{
	File::Save::CSaveField fSave("../Date/map.bin");

	if ( fSave.isOpen () )
	{
		for ( unsigned int i = 0; i < world.size (); i++ )
			world [i].save (fSave);
	}
}


void CMapEditor::load ()
{
	File::Load::CLoadField fLoad ("../Date/map.bin");

	if ( fLoad.isOpen () )
	{
		for ( unsigned int i = 0; i < world.size (); i++ )
			world [i].load (fLoad, items);
	}
}

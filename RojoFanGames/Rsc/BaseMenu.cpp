#include "BaseMenu.h"
using namespace Menu;

//BASE ********************************************************************************************
CBase::CBase (SDL_Renderer* rend, CStateGame* state, int w, int h)
: renderer (rend), state (state), width (w), height (h)
{}


CBase::CBase (SDL_Renderer* rend, CStateGame* state, CMouse* mouse, int w, int h)
: renderer (rend), state (state), event (mouse), width (w), height (h)
{}


void CBase::begin ()
{
	event.mouse->pollEvent ();
	SDL_RenderClear (renderer);
}


void CBase::end ()const
{
	SDL_RenderPresent (renderer);
}


//BASE MENU EDITOR********************************************************************************************************
CBaseEditor::CBaseEditor(std::string file, SDL_Renderer* rend, CMouse* mouse, CBaseItems* item, Engine::CSprite::KIND spriteKind, int w, int h, int number)
:CBase (rend, state, mouse, w, h), open (false), item (item)
{
	mainTexture = new Engine::CSprite (file, rend, w / 20 * number, 0, w / 20, h / 20, nullptr, nullptr, 1, 1, spriteKind, 0);
}


CBaseEditor::~CBaseEditor ()
{}


void CBaseEditor::draw ()
{
	mainTexture->draw ();

	if ( open )
		item->draw ();
}


bool CBaseEditor::openCategory ()
{
	if ( collision.mauseCollision (event.mouse, mainTexture->rectSprite) )
	{
		open = true;
		return true;
	}
	else
		return false;
}


Engine::CSprite* CBaseEditor::selectObject ()
{
	Engine::CSprite* sprite = item->selectObject (event.mouse, collision);
	
	if ( sprite != nullptr )
		open = false;

	return sprite;
}


Engine::CSprite::KIND CBaseEditor::getSpriteKind ()
{
	return item->getKind ();
}


// BASE MENU GAME *******************************************************************************************************************************
CBaseGame::CBaseGame (SDL_Renderer* rend, int w, int h, CStateGame* state)
	: OG (rend, w, h, state)
{}


CBaseGame::~CBaseGame ()
{}


void CBaseGame::update ()
{
	if ( event.keyboard->isPressed () == true && event.keyboard->pressed == false )
	{
		event.keyboard->pressed = true;

		switch ( event.keyboard->getEvent ()->key.keysym.sym )
		{
		case SDLK_UP:
			selectkUp ();
			break;
		case SDLK_DOWN:
			selectDown ();
			break;
		case SDLK_SPACE:
			doIt ();
			break;
		default:
			break;
		}
	}
	else
		event.keyboard->pressed = event.keyboard->isPressed ();
}





//OG**********************************************************************************************************************
OG::OG (SDL_Renderer* rend, unsigned w, unsigned h, CStateGame* state)
	: CBase (rend, state, w, h)
{
	background = new Engine::CSprite ("../Date/MenuBackground.jpg", rend, 0, 0, w, h, nullptr, nullptr, 1, 1, Engine::CSprite::GROUND, 0);
}


OG::~OG ()
{
	delete background;

//	delete background;

	for ( auto i = textMenu.begin (); i != textMenu.end (); i++ )
		delete ( *i );

	textMenu.clear ();
}




int OG::setX ()
{
	return width / 3;
}


void OG::selectkUp ()
{
	( *select )->setColor (Engine::CColor::BLACK);

	if ( select == textMenu.begin () )
		select = textMenu.end () - 1;
	else
		select--;

	( *select )->setColor (Engine::CColor::BROWN);
}


void OG::selectDown ()
{
	( *select )->setColor (Engine::CColor::BLACK);

	if ( select == textMenu.end () - 1 )
		select = textMenu.begin ();
	else
		select++;

	( *select )->setColor (Engine::CColor::BROWN);
}


void OG::draw ()
{
	background->draw ();

	for ( auto i = textMenu.begin (); i != textMenu.end (); i++ )
		( *i )->draw ();
}


//BASE OPTIONS*********************************************************************************

CBaseOptions::CBaseOptions (SDL_Renderer* renderer, unsigned width, unsigned height, CStateGame* state)
	: OG (renderer, width, height, state)
{}


CBaseOptions::~CBaseOptions ()
{ }


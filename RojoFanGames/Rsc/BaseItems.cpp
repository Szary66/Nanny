
#include "BaseItems.h"


CBaseItems::CBaseItems (SDL_Renderer* rend, const std::string file, const int width, const int height, const int maxItems, const Engine::CSprite::KIND kind)
:maxItems (maxItems), kind (kind)
{
	loadTexture (rend, file, width, height);
}


CBaseItems::~CBaseItems ()
{}


void CBaseItems::loadTexture (SDL_Renderer* renderer, const std::string file, int width, int height)
{

	for ( int i = 0; i < maxItems; i++ )
	{
		std::string fileTexture = file;
		fileTexture += std::to_string (i) + ".png";

		pictures.push_back (new Engine::CSprite (fileTexture, renderer, width / 10 * i, 60, width / 10, height / 10, nullptr, nullptr, 1, 1, kind, i) );
	}
}


Engine::CSprite CBaseItems::getItem (const int item)
{
	return  *pictures [item];
}


void CBaseItems::draw ()
{
	for ( auto i = pictures.begin (); i != pictures.end (); i++ )
		( *i )->draw ();
}


void CBaseItems::draw (int i)
{
	pictures [i]->draw ();
}


Engine::CSprite* CBaseItems::selectObject (CMouse* mouse, CCollision &collision)
{
	for (unsigned int i = 0; i < pictures.size (); i++ )
	{
		if ( collision.mauseCollision (mouse, pictures [i]->rectSprite) )
			return pictures [i];
	}
}


Engine::CSprite::KIND CBaseItems::getKind ()
{
	return kind;
}


int CBaseItems::getSize ()const
{
	return pictures.size ();
}
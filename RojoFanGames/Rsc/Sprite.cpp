#include "Sprite.h"
using namespace Engine;

CSprite::CSprite (std::string file, SDL_Renderer* rend, int x, int y, int w, int h, int* xCamera, int* yCamera, int xPlate, int yPlate, KIND kind, int numberOfTexture)
:renderer (rend), xPlate (xPlate), yPlate (yPlate), xCamera (xCamera), yCamera (yCamera), firsSprite (true), animationDelay (0), xTile (0), row (0), file (file), kind (kind), numberOfTexture (numberOfTexture)
{
	texture = loadTexture_IMG (file);
	if ( texture == nullptr )
		std::cout << "Can't load texture! ";
	SDL_QueryTexture (texture, nullptr, nullptr, &rectTexture.w, &rectTexture.h);
	
	rectTexture.h /= this->yPlate;	
	rectTexture.w /= this->xPlate;

	rectSprite.x = x;
	rectSprite.y = y;
	rectSprite.h = h;
	rectSprite.w = w;

	if ( w == 0 )
		rectSprite.w = rectTexture.w;
	if ( h == 0 )
		rectSprite.h = rectTexture.h;
}


CSprite::CSprite (SDL_Texture* texture, std::string file, SDL_Renderer* rend, int x, int y, int w, int h, int* xCamera, int* yCamera, int xPlate, int yPlate, KIND kind, int numberOfTexture)
:texture (texture), renderer (rend), xPlate (xPlate), yPlate (yPlate), xCamera (xCamera), yCamera (yCamera), firsSprite (false), animationDelay (0), xTile (0), file (file), kind (kind), numberOfTexture (numberOfTexture)
{
	SDL_QueryTexture (this->texture, nullptr, nullptr, &rectTexture.w, &rectTexture.h);

	rectTexture.h /= this->yPlate;
	rectTexture.w /= this->xPlate;

	rectSprite.x = x;
	rectSprite.y = y;
	rectSprite.h = h;
	rectSprite.w = w;

	if ( w == 0 )
		rectSprite.w = rectTexture.w;
	if ( h == 0 )
		rectSprite.h = rectTexture.h;
}


CSprite::~CSprite ()
{
	if ( firsSprite )
		SDL_DestroyTexture (texture);
}


SDL_Texture* CSprite::loadTexture_IMG (std::string file)const
{
	SDL_Surface *loadedImage = nullptr;
	SDL_Texture *texture = nullptr;

	texture = IMG_LoadTexture (renderer, file.c_str ());
	if (texture == nullptr )
		std::cout << SDL_GetError () << std::endl;
	return texture;
}


void CSprite::draw ()const
{
	SDL_RenderCopy (renderer, texture, &rectTexture, &rectSprite);
}


void CSprite::setAnimation (int row, const float speed)
{
	this->row = row;
	if ( animationDelay + speed < SDL_GetTicks () )
	{
		if ( xTile >= xPlate - 1)
			xTile = 0;
		else
			xTile++;

		rectTexture.x = xTile * rectTexture.w;
		rectTexture.y = row * rectTexture.h;

		animationDelay = SDL_GetTicks ();
	}
}
 

void CSprite::stopAnimation ()
{
	rectTexture.x = (xPlate - 1) * rectTexture.w;
}

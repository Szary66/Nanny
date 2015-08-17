#include "stdafx.h"
#include "Text.h"
using namespace Engine;
using namespace Text;

COut::COut (std::string file, std::string mes, SDL_Renderer* rend, int x, int y, int w, int h, int size, CColor::HUE hue)
:renderer (rend), color (hue), font (file, size), message (mes)
{
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	texture = RenderText ();
	if ( texture == nullptr )
		std::cout << "Can't load texture font! " << std::endl;
}


COut::COut (std::string file, std::string mes, SDL_Renderer* rend, int x, int y, int w, int h, int size, int r, int g, int b)
:renderer (rend), color (r, g, b), font (file, size), message (mes)
{
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	color.setColor (r, g, b);

	texture = RenderText ();
	if ( texture == nullptr )
		std::cout << "Can't load texture font! " << std::endl;
}



COut::COut (TTF_Font* font, std::string mes, SDL_Renderer* rend, int x, int y, int w, int h, int size, CColor::HUE hue)
:renderer (rend), color (hue), font (font), message (mes)
{
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	texture = RenderText ();
	if ( texture == nullptr )
		std::cout << "Can't load texture font! " << std::endl;
}


COut::COut (TTF_Font* font, std::string mes, SDL_Renderer* rend, int x, int y, int w, int h, int size, int r, int g, int b)
:renderer (rend), color (r, g, b), font (font), message (mes)
{
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	color.setColor (r, g, b);

	texture = RenderText ();
	if ( texture == nullptr )
		std::cout << "Can't load texture font! " << std::endl;
}


COut::~COut ()
{
	SDL_DestroyTexture (texture);
	SDL_FreeSurface (surface);
}


void COut::draw ()const
{
	SDL_RenderCopy (renderer, texture, nullptr, &rect);
}


SDL_Texture* COut::RenderText ()
{
	texture = nullptr;

	surface = TTF_RenderText_Blended (font.getFont(), message.c_str (), color.getColor());
	return  SDL_CreateTextureFromSurface (renderer, surface);
}


void COut::setColor (CColor::HUE hue)
{
	color.setColor (hue);
	texture = RenderText ();
}


void COut::changeMessage (std::string message)
{
	SDL_FreeSurface (surface);
	SDL_DestroyTexture (texture);

	this->message = message;

	surface = TTF_RenderText_Blended (font.getFont (), this->message.c_str (), color.getColor ());
	texture = SDL_CreateTextureFromSurface (renderer, surface);
}


//FONT******************************************************************************************************************
CFont::CFont (std::string file, int size)
:copy (false)
{
	font = nullptr;
	font = TTF_OpenFont (file.c_str (), size);
	if ( font == nullptr )
		std::cout << "Can't load ttf_font! " << std::endl;
}

CFont::CFont (TTF_Font* font)
:font (font), copy (true) {}


CFont::~CFont ()
{
	if ( !copy )
		TTF_CloseFont (font);
}



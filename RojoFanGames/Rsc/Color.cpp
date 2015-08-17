#include "stdafx.h"
#include "Color.h"
using namespace Engine;

CColor::CColor (int r, int g, int b)
{
	color = SDL_Color { r, g, b };
}


CColor::CColor (HUE hue)
{
	setColor (hue);
}


CColor::~CColor ()
{
}


void CColor::setColor (int r, int g, int b)
{
	color = SDL_Color {r, g, b};
}


void CColor::setColor (const HUE hue)
{
	switch ( hue )
	{
	case WHITE:
		color = SDL_Color { 255, 255, 255 };
		break;
	case BLACK:
		color = SDL_Color { 0, 0, 0 };
		break;
	case RED:
		color = SDL_Color { 255, 0, 0 };
		break;
	case GREEN:
		color = SDL_Color { 0, 255, 0 };
		break;
	case BLUE:
		color = SDL_Color { 0, 0, 255 };
		break;
	case YELLOW:
		color = SDL_Color { 255, 255, 0 };
		break;
	case BROWN:
		color = SDL_Color { 165, 42, 42 };
		break;
	default:
		break;
	}
}


const SDL_Color CColor::getColor ()const
{
	return color;
}



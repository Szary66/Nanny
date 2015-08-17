#ifndef IO_TEXT_H
#define IO_TEXT_H
#pragma once
#include "stdafx.h"
#include "Text.h"

namespace Engine
{
	namespace Text
	{
		//Texture wrapper class;
		//This class is form "lazy tutorial" but it was modification by me 
		class CInput : private Engine::Text::CFont
		{
		public:
			CInput (SDL_Renderer*, std::string, unsigned, unsigned, unsigned);
			~CInput ();

			bool loadFromFile (std::string path);
			bool loadFromRenderedText (std::string textureText, SDL_Color textColor);

			void free ();
			void setColor (Uint8 red, Uint8 green, Uint8 blue);

			//Set blending
			void setBlendMode (SDL_BlendMode blending);

			void setAlpha (Uint8 alpha);
			void render (int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

			std::string enter (std::string = "");

			//Gets image dimensions
			int getWidth ()const;
			int getHeight ()const;

		private:
			std::string input ();
			
			//The actual hardware texture
			SDL_Texture* mTexture;

			//Image dimensions
			unsigned mWidth;
			unsigned mHeight;

			unsigned wScreen;
			unsigned hScreen;
			
			SDL_Renderer* renderer;
			SDL_Color color;
		};
	}
}
#endif

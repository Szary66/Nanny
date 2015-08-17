#ifndef TEXT_H
#define TEXT_H
#pragma once
#include <string>
#include "Color.h"
#include "Event.h"
namespace Engine
{
	namespace Text
	{
		class MYCFont;

		//SDL font
		class CFont
		{
		public:
			CFont (std::string, int);
			CFont (TTF_Font*);
			virtual ~CFont ();
			TTF_Font* getFont ()const
			{ return font;}
		protected:
			TTF_Font* font;
		private:
			bool copy;
		};

		//class presend showed text
		class COut
		{
		public:
			COut (std::string, std::string, SDL_Renderer*, int, int, int, int, int, CColor::HUE);
			COut (std::string, std::string, SDL_Renderer*, int, int, int, int, int, int, int, int);
			COut (TTF_Font*, std::string, SDL_Renderer*, int, int, int, int, int, CColor::HUE);
			COut (TTF_Font*, std::string, SDL_Renderer*, int, int, int, int, int, int, int, int);
			~COut ();

			void draw ()const;

			//set text color
			void setColor (CColor::HUE);

			//set new message
			void changeMessage (std::string);

			std::string getMessage ()const
			{return message;}

			const CFont font;
		private:
			SDL_Texture* RenderText ();

			SDL_Surface* surface;
			SDL_Renderer* renderer;
			SDL_Texture* texture;
			SDL_Rect rect;

			CColor color;

			std::string message;
		};
	}
}
#endif
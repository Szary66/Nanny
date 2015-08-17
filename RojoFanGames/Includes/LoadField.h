#ifndef LOADMAP_H
#define LOADMAP_H
#pragma once
#include <fstream>
#include "stdafx.h"
#include "Sprite.h"

namespace File
{
	namespace Load
	{
		//Load map field
		class CLoadField
		{
		public:
			CLoadField (std::string);
			~CLoadField ();

			bool open (std::string);
			bool isOpen ()const;

			//check is hurdle on this field
			bool loadHurdle ();

			//check is ground on this field
			bool loadSubstratum ();

			void close ();

			//load ID texture
			void loadNumberTexture (Engine::CSprite::KIND&, int&);
			
			//load position texture
			void loadRect (SDL_Rect&);

			//load tiles texture
			void loadPlates (int&, int&);
		private:
			std::ifstream fin;
			std::string file;
		};
	}
}



#endif
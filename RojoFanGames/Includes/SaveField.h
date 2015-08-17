#pragma once
#include <fstream>
#include "stdafx.h"
#include "Sprite.h"

namespace File
{
	namespace Save
	{
		class CSaveField
		{
		public:
			CSaveField (std::string);
			~CSaveField ();

			bool open (std::string);
			bool isOpen ()const;

			//save  is hurdle on field or not 
			void saveHurdle (bool&);
			
			//save  is ground on field or not
			void saveSubstratum (bool&);

			//save rect field
			void saveRect (SDL_Rect&);

			//save tiles of item
			void savePlates (int&, int&);

			//save ID item
			void saveNumberTexture (Engine::CSprite::KIND&, int&);

			void close ();

		private:
			std::ofstream fout;
			std::string file;
		};
	}
}



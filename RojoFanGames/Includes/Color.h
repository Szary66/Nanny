#ifndef COLOR_H
#define COLOR_H
#pragma once
//Basic classes with SDL engine elements
namespace Engine
{
	//Class witch color palette 
	class CColor
	{
	public:
		enum HUE
		{
			WHITE, BLACK, RED, GREEN, BROWN, YELLOW, BLUE
		};
		
		CColor (HUE hue);
		CColor (int, int, int);
		~CColor ();
		
		void setColor (const HUE);
		void setColor (int, int, int);

		const SDL_Color getColor ()const;
	private:
		SDL_Color color;
	};
}
#endif
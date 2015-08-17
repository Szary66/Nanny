#ifndef INIT_H
#define INIT_H
#pragma once
#include "stdafx.h"
#include <fstream>
namespace Engine
{
	class CSDL_INIT
	{
	public:
		CSDL_INIT ();

		~CSDL_INIT ();

		SDL_Renderer* getRenderer ()const;

		//Width screen getter
		int getWidth ()const;

		//Height screen getter
		int getHeight ()const;
	private:
		
		// create and set his possition
		void setWindowPosition ();

		//load screen parameter from file
		void load ();

		SDL_Renderer* renderer;
		SDL_Window* display;

		bool fullScreen;

		int w;
		int h;
	};
}
#endif
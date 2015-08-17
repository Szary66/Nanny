#include "SDL_INIT.h"
using namespace Engine;

CSDL_INIT::CSDL_INIT ()
:w (800), h (600), display (nullptr), renderer (nullptr), fullScreen (false)
{
	if ( SDL_Init (SDL_INIT_EVERYTHING) == -1 )
	{
		std::cout << "CAN'T INIT SDL! " << SDL_GetError () << std::endl;
		EXIT_FAILURE;
	}
	if ( TTF_Init () != 0 )
	{
		std::cout << "CAN'T INIT TTF! " << SDL_GetError () << std::endl;
	}
	setWindowPosition ();

	renderer = SDL_CreateRenderer (display, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if ( renderer == nullptr )
	{
		std::cout << "CAN'T CREATE RENDERER! " << SDL_GetError () << std::endl;
		exit(1);
	}
}


CSDL_INIT::~CSDL_INIT ()
{
	SDL_DestroyRenderer (renderer);
	SDL_DestroyWindow (display);

	SDL_Quit ();
}


int CSDL_INIT::getWidth ()const
{
	return w;
}


int CSDL_INIT::getHeight ()const
{
	return h;
}


void CSDL_INIT::setWindowPosition ()
{
	//load ();
	
 	if ( fullScreen )
		display = SDL_CreateWindow ("ROJO GAME", 0, 0, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
	else
	{
		display = SDL_CreateWindow ("ROJO GAME", 50, 50, w, h, SDL_WINDOW_SHOWN);
	}

	if ( display == nullptr )
	{
		std::cout << "CAN'T CREATE WINDOW! " << SDL_GetError () << std::endl;
		exit (1);
	}
}


SDL_Renderer* CSDL_INIT::getRenderer ()const
{
	return renderer;
}


void CSDL_INIT::load ()
{
	std::ifstream fin ("../Date/mainSave.dat", std::ios::in | std::ios::binary);
	int x, y;
	if ( fin.is_open () )
	{
		fin.seekg (8);

		fin.read (( char* ) &w, sizeof w);
		fin.read (( char* ) &h, sizeof h);
		fin.read (( char* ) &fullScreen, sizeof fullScreen);
		fin.read (( char* ) &x, sizeof x);
		fin.read (( char* ) &y, sizeof y);
		fin.close ();
	}
}
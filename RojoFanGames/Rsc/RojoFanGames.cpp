#include "HandlingGame.h"
#include "SDL_INIT.h"
#include "TextInput.h"
#include <memory>

auto main (int argc, char* argv [])->int
{
	std::shared_ptr <Engine::CSDL_INIT> init (new Engine::CSDL_INIT());
	std::shared_ptr <CHandlingGame> game (new CHandlingGame (init->getRenderer (), init->getWidth (), init->getHeight ()));
	game->loop ();

	
	return 0;
}

#include "Options.h"
using namespace Options;

//MAIN************************************************************************************************
CMain::CMain (SDL_Renderer* rend, CStateGame* oState, CStateGame::STATE uState, int w, int h)
	: Menu::OG (rend, w, h, oState), oState (oState), uState (uState), save ("../Date/mainSave.dat"), load ("../Date/mainSave.dat")
{
	textMenu.push_back (new Engine::Text::COut ("../Date/AFGAN.TTF", "GRAPHIC", renderer, setX (), 50, setX (), 100, 50, Engine::CColor::BLACK));
	textMenu.push_back (new Engine::Text::COut (textMenu [0]->font.getFont (), "SOUND", renderer, setX (), 150, setX (), 100, 50, Engine::CColor::BLACK));
	textMenu.push_back (new Engine::Text::COut (textMenu [0]->font.getFont (), "GAMEPLAY", renderer, setX (), 250, setX (), 100, 50, Engine::CColor::BLACK));
	textMenu.push_back (new Engine::Text::COut (textMenu [0]->font.getFont (), "BACK", renderer, setX (), 350, setX (), 100, 50, Engine::CColor::BROWN));

	select = textMenu.end () - 1;
}


void CMain::loop ()
{
	while ( oState->state == CStateGame::optionGame )
	{
		begin ();

		if ( event.keyboard->getEvent ()->key.keysym.sym == SDLK_ESCAPE )
			oState->state = uState;
		
		update ();
		draw ();

		end ();
	}
}


void CMain::update ()
{
	if ( event.keyboard->isPressed () == true && event.keyboard->pressed == false )
	{
		event.keyboard->pressed = true;

		switch ( event.keyboard->getEvent ()->key.keysym.sym )
		{
		case SDLK_UP:
			selectkUp ();
			break;
		case SDLK_DOWN:
			selectDown ();
			break;
		case SDLK_SPACE:
			doIt ();
			break;
		default:
			break;
		}
	}
	else
		event.keyboard->pressed = event.keyboard->isPressed ();
}


void CMain::doIt ()
 {
	if ( ( *select ) == textMenu [0] )
	{
		graphic = new CGraphic (renderer, width, height, load);
		graphic->loop (save);
		delete graphic;
	}
	else if ( select == textMenu.end () - 2 )
	{
		CGameplay gameplay (renderer, width, height);
		gameplay.loop (save);
	}
	else if ( select == textMenu.end () - 1 )
		oState->state = uState;
}


// GRAPHIC*******************************************************************************************
CGraphic::CGraphic (SDL_Renderer* rend, int w, int h, File::CLoad &fout)
:Menu::CBaseOptions (rend, w, h, nullptr), resolution (rend, w, h)
{
	textMenu.push_back (new Engine::Text::COut ("../Date/AFGAN.TTF", "RESOLUTION", renderer, setX (), 50, setX () * 0.6, 50, 50, Engine::CColor::BLACK));
	textMenu.push_back (new Engine::Text::COut (textMenu [0]->font.getFont (), "FULLSCREEN", renderer, setX (), 100, setX () * 0.6, 50, 50, Engine::CColor::BLACK));
	textMenu.push_back (new Engine::Text::COut (textMenu [0]->font.getFont (), "SAVE", renderer, setX (), 150, setX () * 0.6, 50, 50, Engine::CColor::BLACK));
	textMenu.push_back (new Engine::Text::COut (textMenu [0]->font.getFont (), "BACK", renderer, setX (), 200, setX () * 0.6, 50, 50, Engine::CColor::BROWN));

	select = textMenu.end () - 1;

	noFullscreen = new Engine::Text::COut (textMenu [0]->font.getFont (), "NO", renderer, setX () * 2 - setX () / 3 + 20, 100, setX () / 3 - 20, 50, 50, Engine::CColor::BLACK);
	yesFullscreen = new Engine::Text::COut (textMenu [0]->font.getFont (), "YES", renderer, setX () * 2 - setX () / 3 + 20, 100, setX () / 3 - 20, 50, 50, Engine::CColor::BLACK);

	load (fout);

	setValue ();
}


void CGraphic::update (File::CSave &save)
{
	if ( event.keyboard->isPressed () == true && event.keyboard->pressed == false )
	{
		event.keyboard->pressed = true;

		switch ( event.keyboard->getEvent ()->key.keysym.sym )
		{
		case SDLK_UP:
			selectkUp ();
			break;
		case SDLK_DOWN:
			selectDown ();
			break;
		case SDLK_SPACE:
			doIt (save);
			break;
		default:
			break;
		}
	}
	else
		event.keyboard->pressed = event.keyboard->isPressed ();
}


void CGraphic::setValue (int row)
{
	if ( row == -1 )
	{
		value.push_back (new Engine::Text::COut (textMenu [0]->font.getFont (), resolution.getMessage (), renderer, setX () * 2 - setX () / 3 + 20, 50, setX () / 3 - 20, 50, 50, Engine::CColor::BLACK));
		if ( fullscreen )
			value.push_back (yesFullscreen);
		else
			value.push_back (noFullscreen);
	}
	else if ( row < value.size () )
		switch ( row )
	{
		case 0:
			value [0]->changeMessage (resolution.getMessage ());
			break;
		case 1:
			if ( fullscreen )
				value [1] = yesFullscreen;
			else
				value [1] = noFullscreen;
		default:
			break;
	}
}


void CGraphic::doIt (File::CSave &fout)
{
	if ( select == textMenu.begin () )
	{
		resolution.loop ();
		setValue (0);
	}
	else if ( select == textMenu.begin () + 1 )
	{
		if ( fullscreen )
			fullscreen = false;
		else
			fullscreen = true;

		setValue (1);
	}
	else if ( select == textMenu.begin () + 2 )
		save (fout);
	else if ( select == textMenu.end () - 1 )
		open = false;
}


void CGraphic::loop (File::CSave &save)
{
	open = true;
	while ( open )
	{
		begin ();

		update (save);
		draw ();

		end ();
	}
}


void CGraphic::draw ()
{
	Menu::CBaseOptions::draw ();

	for ( auto i = value.begin (); i != value.end (); i++ )
		( *i )->draw ();
}


void CGraphic::save (File::CSave &save)
{
	w = resolution.w;
	h = resolution.h;

	save.write (w);
	save.write (h);
	save.write (fullscreen);
}


void CGraphic::load (File::CLoad &load)
{
	load.read (&w);
	load.read (&h);
	load.read (&fullscreen);

	resolution.w = w;
	resolution.h = h;

	resolution.loadSelect ();
}


// RESORLUTION*******************************************************************************************************
CResolution::CResolution (SDL_Renderer* rend, int width, int height)
:Menu::CBaseGame (rend, width, height, nullptr)
{
	textMenu.push_back (new Engine::Text::COut ("../Date/AFGAN.TTF", "800x600", renderer, setX (), 50, setX (), 50, 50, Engine::CColor::BLACK));
	textMenu.push_back (new Engine::Text::COut (textMenu [0]->font.getFont (), "1024x768", renderer, setX (), 100, setX (), 50, 50, Engine::CColor::BLACK));
	textMenu.push_back (new Engine::Text::COut (textMenu [0]->font.getFont (), "1280x1024", renderer, setX (), 150, setX (), 50, 50, Engine::CColor::BLACK));
	textMenu.push_back (new Engine::Text::COut (textMenu [0]->font.getFont (), "1366x768", renderer, setX (), 200, setX (), 50, 50, Engine::CColor::BLACK));
	textMenu.push_back (new Engine::Text::COut (textMenu [0]->font.getFont (), "1600x900", renderer, setX (), 250, setX (), 50, 50, Engine::CColor::BLACK));
	textMenu.push_back (new Engine::Text::COut (textMenu [0]->font.getFont (), "BACK", renderer, setX (), 300, setX (), 50, 50, Engine::CColor::BLACK));

	select = textMenu.end () - 1;
}


void CResolution::loop ()
{
	open = true;

	while ( open )
	{
		begin ();

		update ();
		draw ();

		end ();
	}
}


void CResolution::update ()
{
	if ( event.keyboard->isPressed () == true && event.keyboard->pressed == false )
	{
		event.keyboard->pressed = true;

		switch ( event.keyboard->getEvent ()->key.keysym.sym )
		{
		case SDLK_UP:
			selectkUp ();
			break;
		case SDLK_DOWN:
			selectDown ();
			break;
		case SDLK_SPACE:
			doIt ();
			break;
		default:
			break;
		}
	}
	else
		event.keyboard->pressed = event.keyboard->isPressed ();
}


void CResolution::doIt ()
{
	if ( select == textMenu.begin () )
	{
		w = 800;
		h = 600; 
	}
	else if ( select == textMenu.begin () + 1 )
	{
		w = 1024;
		h = 768;
	}
	else if ( select == textMenu.begin () + 2 )
	{
		w = 1280;
		h = 1024;
	}
	else if ( select == textMenu.begin () + 3 )
	{
		w = 1366;
		h = 768;
	}
	else if ( select == textMenu.begin () + 4 )
	{
		w = 1600;
		h = 900;
	}

	open = false;
}


void CResolution::loadSelect ()
{
	if ( w == 800 )
		select = textMenu.begin ();
	else if ( w == 1024 )
		select = textMenu.begin () + 1;
	else if ( w == 1280 )
		select = textMenu.begin () + 2;
	else if ( w == 1366 )
		select = textMenu.begin () + 3;
	else if ( w == 1600 )
		select = textMenu.begin () + 4;
}


std::string CResolution::getMessage ()const
{
	return ( *select )->getMessage();
}


// GAMEPLAY *************************************************************************************************
CGameplay::CGameplay (SDL_Renderer* renderer, unsigned width, unsigned height)
	: Menu::OG (renderer, width, height, nullptr), xPlate (0), yPlate (0)
{
	textMenu.push_back (new Engine::Text::COut ("../Date/AFGAN.TTF", "TILES OF MAP", renderer, setX (), 100, setX (), 50, 50, Engine::CColor::BLACK));
	textMenu.push_back (new Engine::Text::COut (textMenu [0]->font.getFont (), "LEVEL GAME", renderer, setX (), 150, setX (), 50, 50, Engine::CColor::BLACK));
	textMenu.push_back (new Engine::Text::COut (textMenu [0]->font.getFont (), "SAVE", renderer, setX (), 200, setX (), 50, 50, Engine::CColor::BLACK));
	textMenu.push_back (new Engine::Text::COut (textMenu [0]->font.getFont (), "BACK", renderer, setX (), 250, setX (), 50, 50, Engine::CColor::BROWN));

	select = textMenu.end () - 1;
}

void CGameplay::enterPlateX ()
{}


void CGameplay::enterPlateY ()
{}


void CGameplay::save (File::CSave &save)const
{
	save.write (xPlate);
	save.write (yPlate);
}


void CGameplay::load (File::CLoad &load)
{
	load.read (&xPlate);
	load.read (&yPlate);
}


void CGameplay::loop (File::CSave &save)
{
	quit = false;
	
	while ( !quit )
	{
		begin ();

		update (save);
		draw ();

		end ();
	}
}


void CGameplay::doIt (File::CSave &fin)
{
	if ( select == textMenu.end () - 2 )
		save (fin);
	else if ( select == textMenu.end () - 1 )
		quit = true;
}


void CGameplay::update (File::CSave &save)
{
	if ( event.keyboard->isPressed () == true && event.keyboard->pressed == false )
	{
		event.keyboard->pressed = true;

		switch ( event.keyboard->getEvent ()->key.keysym.sym )
		{
		case SDLK_UP:
			selectkUp ();
			break;
		case SDLK_DOWN:
			selectDown ();
			break;
		case SDLK_SPACE:
			doIt (save);
			break;
		default:
			break;
		}
	}
	else
		event.keyboard->pressed = event.keyboard->isPressed ();
}
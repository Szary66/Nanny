#include "Event.h"


bool CKeyboard::isPressed ()const
{
	return bool( event->type == SDL_KEYDOWN );
}


bool CKeyboard::operator==( CKeyboard* keyboard )
{
	return event->key.keysym.sym == keyboard->getEvent ()->key.keysym.sym;
}


bool CKeyboard::operator!= ( CKeyboard* keyboard )
{
	return event->key.keysym.sym != keyboard->getEvent ()->key.keysym.sym;
}


// MAUSE*************************************************************************
bool CMouse::isPressed ()const
{
	return bool ( event->type == SDL_MOUSEBUTTONDOWN );
}


int CMouse::getMouseX ()const
{
	return event->motion.x;
}


int CMouse::getMouseY ()const
{
	return event->motion.y;
}


//EVENT*********************************************************************************
CEvent::CEvent ()
{
	keyboard = new CKeyboard ();
	mouse = new CMouse (keyboard->getEvent ());
}


CEvent::CEvent (SDL_Event* event)
{
	keyboard = new CKeyboard (event);
	mouse = new CMouse (event);
}


CEvent::CEvent (CKeyboard* keyboard)
: keyboard (keyboard) 
{
	mouse = new CMouse (keyboard->getEvent ());
}


CEvent::CEvent (CMouse* mouse)
: mouse (mouse)
{
	keyboard = new CKeyboard (this->mouse->getEvent ());
}


CEvent::CEvent (CKeyboard* keyboard, CMouse* mouse)
: keyboard (keyboard), mouse (mouse)
{}


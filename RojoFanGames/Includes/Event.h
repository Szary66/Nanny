#ifndef EVENT_H
#define EVENT_H
#pragma once
#include "stdafx.h"

namespace Engine
{
	class CEventBase
	{
	public:
		//Set SDL_event
		CEventBase (SDL_Event* event)
			:event (event), newEvent(false){}
		//Create new SDL_Event
		CEventBase () :newEvent (true)
		{
			event = new SDL_Event;
		}
		
		// Poll SDL event
		int pollEvent ()
		{return SDL_PollEvent (event);}

		// Get SDL event
		SDL_Event* getEvent ()const
		{return event;}

		bool pressed;

	protected:
		SDL_Event* event;
	private:
		bool newEvent;
	};
}


class CKeyboard :virtual public Engine::CEventBase
{
public:
	// Set SDL event
	CKeyboard (SDL_Event* event) 
		:CEventBase (event){}
	// Create new keyboard event
	CKeyboard (){};
	~CKeyboard (){};

	// Collate pressed key
	bool operator== ( CKeyboard* );
	// Collate pressed key
	bool operator!= ( CKeyboard* );

	//Check key is pressed
	bool isPressed ()const;
};


class CMouse :virtual public Engine::CEventBase
{
public:
	//Create new mause event
	CMouse (SDL_Event* event)
		:CEventBase(event){}
	CMouse (){};
	~CMouse (){};

	// Check mause is clicked 
	bool isPressed ()const;

	// Get mause point X
	int getMouseX ()const;
	
	//Get mause point Y
	int getMouseY ()const;
};


class CEvent :public CKeyboard, public CMouse
{
public:
	//Create new main event
	CEvent ();

	//Set SDL event
	CEvent (SDL_Event*);

	//Set keyboard event
	CEvent (CKeyboard*);

	//Set mause event
	CEvent (CMouse*);

	//Set mause and keyboard events
	CEvent (CKeyboard*, CMouse*);

	CKeyboard* keyboard;
	CMouse* mouse;
};
#endif
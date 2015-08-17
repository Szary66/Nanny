#ifndef BASEMENU_H
#define BASEMENU_H
#pragma once
#include "stdafx.h"
#include "StateGame.h"
#include "Text.h"
#include "BaseItems.h"
#include "Sprite.h"
#include "FileStream.h"

namespace Menu
{

	class CBase
	{
	public:
		CBase (SDL_Renderer*, CStateGame*, int, int);
		CBase (SDL_Renderer*, CStateGame*, CMouse*, int, int);
		CBase (SDL_Renderer*, CStateGame*, CKeyboard*, int, int);
		CBase (SDL_Renderer*, CStateGame*, CEvent*, int, int);
		~CBase ()
		{
		}

		protected:
		//Clear screen
		void begin ();

		//Present renderer on screen
		void end ()const;

		
		int width;
		int height;	

		CEvent event;
		CStateGame* state;

		SDL_Renderer* renderer;
		CCollision collision;
	};


	class OG: public CBase
	{
	public:
		OG (SDL_Renderer*, unsigned, unsigned, CStateGame*);
		~OG ();
	
	protected:
		//Select a higher element
		void selectkUp ();
		
		//Select a lowev elemnt
		void selectDown ();

		virtual void draw ();
		
		//Update effect event
		//virtual void update ();

		// Set x Of begin text
		int setX ();

		//Iterator selected text
		std::vector<Engine::Text::COut*>::iterator	select;
		
		//Texts of menu
		std::vector<Engine::Text::COut*>textMenu;
	
	private:
		Engine::CSprite* background;
	};


	class CBaseGame :public OG
	{
	public:
		CBaseGame (SDL_Renderer*, int, int, CStateGame*);
		~CBaseGame ();

	protected:
		//Open selected menu
		virtual void doIt () = 0;

		//Update event effect
		virtual void update () = 0;
	};


	class CBaseEditor :public CBase
	{
	public:
		CBaseEditor (std::string, SDL_Renderer*, CMouse*, CBaseItems*, Engine::CSprite::KIND, int, int, int);
		~CBaseEditor ();

		void draw ();

		bool isOpen ()const
		{return open;}
		
		//Open menu category
		bool openCategory ();

		Engine::CSprite* selectObject ();
		Engine::CSprite::KIND getSpriteKind ();
	protected:
		Engine::CSprite* mainTexture;

		CBaseItems* item;

		bool open;
	};

	class CBaseOptions: public OG
	{
	public:
		CBaseOptions (SDL_Renderer*, unsigned, unsigned, CStateGame*);
		~CBaseOptions ();
	protected:
		virtual void doIt (File::CSave&) = 0;
		virtual void update (File::CSave&) = 0;
	};
}

#endif
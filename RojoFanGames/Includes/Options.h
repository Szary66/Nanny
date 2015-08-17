#ifndef OPTIONS_H
#define OPTIONS_H
#pragma once
#include "FileStream.h"
#include "BaseMenu.h"
namespace Options
{
	//Resolution open new menu and change change actual resolution
	class CResolution :private Menu::CBaseGame
	{
	public:
		CResolution (SDL_Renderer*, int, int);
		~CResolution (){}

		virtual void loop ();
		virtual void update ();

		std::string getMessage ()const;

		unsigned w;
		unsigned h;

		void loadSelect ();
	private:
		virtual void doIt ();

		bool open;
	};

	//Open new menu, chech full screen or window and save items
	class CGraphic :public Menu::CBaseOptions
	{
	public:
		CGraphic (SDL_Renderer*, int, int, File::CLoad&);
		~CGraphic ()
		{
			delete yesFullscreen;
			delete noFullscreen;
		}

		virtual void loop (File::CSave&);
	private:
		virtual void doIt (File::CSave&);
		virtual void update (File::CSave&);
		virtual void draw ();

		void setValue (int row = -1);

		void load (File::CLoad&);
		void save (File::CSave&);

		CResolution resolution;

		Engine::Text::COut* yesFullscreen;
		Engine::Text::COut* noFullscreen;

		std::vector<Engine::Text::COut*> value;

		bool open;
		bool fullscreen;

		int w;
		int h;
	};

	//abstact class, base for options and gameplay classes
	class CMain :private Menu::OG
	{
	public:
		CMain (SDL_Renderer*, CStateGame*, CStateGame::STATE, int, int);
		~CMain (){}

		void loop ();
	private:

		CStateGame* oState;
		const CStateGame::STATE const uState;
		void virtual doIt ();
		void virtual update ();
		
		CGraphic* graphic;
		
		File::CLoad load;
		File::CSave save;
	};

	// gamepla options, create new menu and chande tiles x and y on screend
	class CGameplay : public Menu::OG
	{
	public:
		CGameplay (SDL_Renderer*, unsigned, unsigned);
		~CGameplay (){};

		//player enter x tile
		void enterPlateX ();

		//player enter y tile
		void enterPlateY ();

		void setPlateX (unsigned x)
			{ xPlate = x;}
		void setPlateY (unsigned y)
			{ yPlate = y;}

		unsigned getPlateX ()const
			{return xPlate;}
		unsigned getPlateY ()const
			{return yPlate;}

		virtual void loop (File::CSave&);
		
	private:
		//handle the event
		virtual void doIt (File::CSave&);
		virtual void update (File::CSave&);
		
		void save (File::CSave&)const;
		void load (File::CLoad&);
		
		unsigned xPlate, yPlate;

		bool quit;
	};
}
#endif
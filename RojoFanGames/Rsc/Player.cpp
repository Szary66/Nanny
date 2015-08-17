#include "Player.h"


CPlayer::CPlayer (CKeyboard* event, int speed, SDL_Renderer* rend, CStateGame* state, int* xCamera, int* yCamera)
:newEvent (event), speed (speed), boy (new Engine::CSprite ("../Date/tom.png", rend, 100, 100, 80, 60, xCamera, yCamera, 4, 4, Engine::CSprite::HUMAN, 0)), down (boy, &this->speed), up (boy, &this->speed), left (boy, &this->speed), right (boy, &this->speed), stay (boy), state (state)
{
	newEvent->pressed = false;
	move = &stay;
}


CPlayer::~CPlayer ()
{
	delete boy;
}


void CPlayer::update ()
{
	if ( newEvent->isPressed() )
	{
		if ( newEvent->getEvent ()->key.keysym.sym != lastEvent.getEvent ()->key.keysym.sym || newEvent->pressed == false)
		{
			newEvent->pressed = true;
			switch ( newEvent->getEvent ()->key.keysym.sym )
			{
			case SDLK_DOWN:
				move = &down;
				break;
			case SDLK_UP:
				move = &up;
				break;
			case SDLK_LEFT:
				move = &left;
				break;
			case SDLK_RIGHT:
				move = &right;
				break;
			case SDLK_ESCAPE:
				state->state = CStateGame::pauseGame;
				break;
			default:
				break;
			}
			lastEvent = *newEvent;
		}
	}
	else
	{
		move = &stay;
		newEvent->pressed = false;
	}
	move->move ();
}
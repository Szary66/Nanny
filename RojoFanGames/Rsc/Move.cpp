#include "Move.h"


CMove::CMove (){}


CMove::~CMove (){}


CMoveDown::CMoveDown (Engine::CSprite* player, int* speed)
:player (player), speed(speed){}


void CMoveDown::move ()
{
	player->rectSprite.y += *speed;
	player->setAnimation (0, 200.0f);
}


CMoveUp::CMoveUp (Engine::CSprite* player, int* speed)
:player(player), speed(speed){}


void CMoveUp::move ()
{
	player->rectSprite.y -= *speed;
	player->setAnimation (3, 200.0f);
}


CMoveLeft::CMoveLeft (Engine::CSprite* player, int* speed)
:player (player), speed(speed){}


void CMoveLeft::move ()
{
	player->rectSprite.x -= *speed;
	player->setAnimation (1, 200.0f);
}


CMoveRight::CMoveRight (Engine::CSprite* player, int* speed)
:player (player), speed(speed){}


void CMoveRight::move ()
{
	player->rectSprite.x += *speed;
	player->setAnimation (2, 200.0f);
}


CStay::CStay (Engine::CSprite* player)
:player (player){}


void CStay::move ()
{
	player->stopAnimation ();
}


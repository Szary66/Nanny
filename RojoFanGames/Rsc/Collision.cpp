#include "Collision.h"


CCollision::CCollision ()
{
}


CCollision::~CCollision ()
{
}


bool CCollision::mauseCollision (CMouse* mouse, const SDL_Rect rect)const
{
	std::cout << mouse << "\t" << mouse->getMouseX () << ", " << mouse->getMouseY () << std::endl;
	if ( mouse->getMouseX () >= rect.x && mouse->getMouseX () <= rect.x + rect.w )
	{
		if ( mouse->getMouseY () >= rect.y && mouse->getMouseY() <= rect.y + rect.h )
			return true;
		else
			return false;
	}
	else
		return false;
}


bool CCollision::TextureCollision (const SDL_Rect rect_1, const SDL_Rect rect_2)const
{
	return ( sqrt (pow (rect_1.x - rect_2.x, 2) + pow (rect_1.y - rect_2.y, 2)) <= sqrt (pow (rect_1.h + rect_2.h, 2) + pow (rect_1.w + rect_2.w, 2)) )
		? true : false;
}
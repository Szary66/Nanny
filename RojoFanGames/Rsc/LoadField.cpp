#include "LoadField.h"
using namespace File;
using namespace Load;

CLoadField::CLoadField (std::string file)
:fin (file.c_str (), std::ios::in | std::ios::binary)
{}


CLoadField::~CLoadField ()
{
	if ( fin.is_open () )
		fin.close ();
}


bool CLoadField::open (std::string file)
{
	if ( fin.is_open () )
		fin.close ();

	fin.open (file.c_str (), std::ios::in | std::ios::binary);
	
	if ( fin.is_open () )
	{
		this->file = file;
		return true;
	}
	else
		return false;
}


bool CLoadField::isOpen ()const
{
	return fin.is_open ();
}


bool CLoadField::loadHurdle ()
{
	bool hurdle;
	fin.read (( char* ) &hurdle, sizeof hurdle);
	
	return hurdle;
}


bool CLoadField::loadSubstratum ()
{
	bool substratum;
	fin.read (( char* ) &substratum, sizeof substratum);

	return substratum;
}


void CLoadField::loadNumberTexture (Engine::CSprite::KIND &kind, int &IDTexture)
{
	if ( fin.good () )
	{
		fin.read (( char* ) &kind, sizeof kind);
		fin.read (( char* ) &IDTexture, sizeof IDTexture);
	}
}


void CLoadField::loadRect (SDL_Rect &rect)
{
	fin.read (( char* ) &rect, sizeof rect);
}


void CLoadField::close ()
{
	fin.close ();
}


void CLoadField::loadPlates (int &x, int&y)
{
	fin.read (( char* ) &x, sizeof x);
	fin.read (( char* ) &y, sizeof y);
}
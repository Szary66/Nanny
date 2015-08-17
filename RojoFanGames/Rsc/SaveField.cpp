#include "SaveField.h"
using namespace File;
using namespace Save;


CSaveField::CSaveField (std::string file)
:fout (file.c_str (), std::ios::binary | std::ios::out)
{}


CSaveField::~CSaveField ()
{
	if ( fout.is_open () )
		fout.close ();
}


bool CSaveField::open (std::string file)
{
	if ( fout.is_open () )
		fout.close ();

	fout.open (file.c_str (), std::ios::binary | std::ios::out);
	if ( fout.is_open () )
	{
		this->file = file;
		return true;
	}
	else
		return false;
}


bool CSaveField::isOpen ()const
{
	return fout.is_open ();
}


void CSaveField::saveHurdle (bool &hurdle)
{
	fout.write (( char* ) &hurdle, sizeof hurdle);
}


void CSaveField::saveSubstratum (bool &substratum)
{
	fout.write (( char* ) &substratum, sizeof substratum);
}


void CSaveField::saveRect (SDL_Rect &rect)
{
	fout.write (( char* ) &rect, sizeof rect);
}


void CSaveField::savePlates (int &x, int &y)
{
	fout.write (( char* ) &x, sizeof x);
	fout.write (( char* ) &y, sizeof y);
}


void CSaveField::saveNumberTexture (Engine::CSprite::KIND &kind, int &ID)
{
	fout.write (( char* ) &kind, sizeof kind);
	fout.write (( char* ) &ID, sizeof ID);
}


void CSaveField::close ()
{
	fout.close ();
}
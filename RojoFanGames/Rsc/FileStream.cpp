#include "stdafx.h"
#include "FileStream.h"
using namespace File;

//LOAD ***********************************************************************************************************
CLoad::CLoad (std::string addresFile)
: address (addresFile)
{}


CLoad::~CLoad ()
{}


void CLoad::open (std::string addressFile)
{
	if ( address != addressFile )
	{
		address = addressFile;
		fin.open (addressFile.c_str ());
	}
}


void CLoad::bufforOnLine (int line, FIND findFrom)
{
	switch ( findFrom )
	{
	case FROM_BEGIN:
		fin.seekg (line, std::ios_base::beg);
		break;
	case FROM_END:
		fin.seekg (line, std::ios_base::end);
		break;
	case THISLINE:
		fin.seekg (line + 1);
		break;
	default:
		fin.seekg (line, std::ios_base::cur);
		break;
	}
}


//SAVE ********************************************************************************************************
CSave::CSave (std::string addressFile)
: address (addressFile)
{}


CSave::~CSave ()
{}


void CSave::open (std::string addressFile)
{
	if ( addressFile != address && addressFile != "" )
	{
		address = addressFile;
		fout.open (address.c_str ());
	}
	else if ( addressFile == "" && !isOpen())
	{
		fout.open (address.c_str ());
	}
}


void CSave::bufforOnLine (int line, FIND findFrom)
{
	switch ( findFrom )
	{
	case FROM_BEGIN:
		fout.seekp (+line, std::ios_base::beg);
		break;
	case FROM_END:
		fout.seekp (-line, std::ios_base::end);
		break;
	case THISLINE:
		fout.seekp (line + 1);
		break;
	default:
		if ( line < 0 )
			fout.seekp (-line, std::ios_base::cur);
		else
			fout.seekp (+line, std::ios_base::cur);
		break;
	}
}


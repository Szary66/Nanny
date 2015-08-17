#ifndef FILE_H
#define FILE_H
#pragma once
#include <fstream>
namespace File
{
	//
	enum FIND
	{
		FROM_BEGIN, FROM_END, FROM_ACTUALPOSSITION, THISLINE
	};

	//Basic load class
	class CLoad
	{
	public:
		CLoad (std::string);
		~CLoad ();

		//set point on byte file
		void bufforOnLine (int, FIND findFrom);
		void  open (std::string addressFile = "");
		void close ()
			{fin.close();}

		bool isOpen ()const
			{return fin.is_open();}
		
		template<class T>
		void read (T *item)
		{
			fin.read (( char* ) &item, sizeof item);
		}
	private:
		std::ifstream fin;
		std::string address;
	};

	//Basic save class
	class CSave
	{
	public:
		CSave (std::string);
		~CSave ();

		//Set buffor on byte file
		void bufforOnLine (int line, FIND findFrom);
		template <class T>
		void write (T &item)
		{
			fout.write (( char* ) &item, sizeof item);
		}

		void open (std::string addressFile = "");
		void close ()
			{fout.close();}
		bool isOpen ()const
			{return fout.is_open();}

	private:
		std::ofstream fout;
		std::string address;
	};
}

#endif
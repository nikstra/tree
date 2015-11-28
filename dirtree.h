////////////////////////////////////////////////////////////////////////////////
//
// FILE:
//	dirtree.h
//
// DESCRIPTION:
//	Definition of CDirTree class.
//
// AUTHOR:
//	Niklas Strand
//
// DATE:
//	99-12-05
//
// CHANGES:
//      2014-11-21
//      Made some changes so that the code compiles on a modern system. For
//      example adding "using namespace std;" and changing init list for
//      CDirTree's constructor.
//

#ifndef _DIRTREE_H
#define _DIRTREE_H

#include <string>
#include <cstring>
#include <list>
#include "bitmask.h"

using namespace std; // Added 2014-11-21.

////////////////////////////////////////////////////////////////////////////////
// Constant strings to make up the vertical lines in the tree.

const char BAR[]	= "|   ";
const char NOBAR[]	= "    ";

////////////////////////////////////////////////////////////////////////////////
//
// CLASS:	CDirTree
//
// PURPOSE:	Scans the directory structure and prints a tree graph
//		on the screen.
//

class CDirTree
{
public:
	// Changed init list to new standard 2014-11-21.
	//CDirTree() : dirline( "+---" )
	CDirTree() :
		dirline({ '+', '-', '-', '-', 0 }),
		opt({ "", 0, 0, 0, 0, 0 })
   	{
		/* strcpy( dirline, "+---" ); */
 		/* opt.help = 0;
 		opt.ver  = 0;
		opt.sort = 0;
		opt.all  = 0;
		opt.file = 0; */
	}
	int scan( string inpath, int level = 0 );

	struct _opt // Contains all command line options.
	{
	        string path;
	        unsigned int help	: 1;
	        unsigned int ver	: 1;
	        unsigned int sort	: 1;
	        unsigned int all	: 1;
	        unsigned int file	: 1;
	} opt;

protected:
	bool is_dots( const string &str );
 	bool is_hidden( const string &name );
	void print_file( list<string> &fname_list, int level );

	CBitMask bm;
	char dirline[5];

};

#endif // _DIRTREE_H


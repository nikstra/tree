////////////////////////////////////////////////////////////////////////////////
//
// FILE:
//	tree.cpp
//
// DESCRIPTION:
//	Defines the main function, processes command line arguments
//	and prints usage and info.
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
//      example adding "using namespace std;" and changing some #include lines.
//

#include <linux/limits.h>
#include <iostream> // Changed from iostream.h 2014-11-21.
#include <unistd.h>
#include <string>
#include <string.h>
#include "bitmask.h"
#include "dirtree.h"

using namespace std; // Added 2014-11-21.

// String with the version number.
const char ver[] = "1.3 alpha";

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	void usage()
//
// PURPOSE:	Print a simple help message.
//

void usage()
{
	cerr << "\nUSAGE:\ttree [-afs] [path]\n"
		<< "\ttree -v\n"
		<< "\ttree -h\n" << endl;

	cerr << "\t-a\tshow hidden directories ( files )\n"
		<< "\t-f\tshow files, by default only directories are shown\n"
		<< "\t-s\tsort output alphabetically\n"
		<< "\t-v\tshow version information\n"
		<< "\t-h\tshow this help\n" << endl;
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	void version()
//
// PURPOSE:	Print version info.
//

void version()
{
	cerr << "\ntree\nVersion " << ver << endl;
	cerr << "Copyright Niklas Strand\n" << endl;
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	int main( int argc, char *argv[] )
//
// PURPOSE:	The main() function.
//

int main( int argc, char *argv[] )
{
	CDirTree tree;

	// Process the command line args.
	for( int i = 0; i < argc; ++i )
	{
		if( argv[i][0] == '-' )
		{
			for( int j = 1; j < strlen( argv[i] ); ++j )
			{
				switch( argv[i][j] )
				{
				case 'v':
					( argc > 2 ) || ( argv[i][j +1] != 0 )
					? usage() : version(); 
				 	return 1;
 				case 'a':
					tree.opt.all = true;
					break;
				case 'f':
					tree.opt.file = true;
					break;
				case 's':
					tree.opt.sort = true;
	 				break;
	 			case 'h':
				default:
					usage();
					return 1;
				}
			}
		}
		else
		{
			( i > 0 ) ? tree.opt.path = argv[i]
				: tree.opt.path = ".";
		}
	}

	if( tree.opt.path == "." )
	{
		char buf[PATH_MAX];
		getcwd( buf, PATH_MAX );
		tree.opt.path = buf;
	}
	cout << endl << tree.opt.path;

	// If path not ending with a slash, add one.
	if( tree.opt.path[tree.opt.path.length() - 1] != '/' )
 		cout << "/";
	cout << endl;

	// Call the scan() function to do the actual work.
	if( tree.scan( tree.opt.path ))
		cerr << "Could not open specified directory!" << endl;

	return 0;
}


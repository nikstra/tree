////////////////////////////////////////////////////////////////////////////////
//
// FILE:
//	dirtree.cpp
//
// DESCRIPTION:
//	Defines the member functions of the CDirTree class.
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

#include <iostream> // Changed from iostream.h 2014-11-21.
#include <string>
#include <list>
#include <linux/limits.h> // Added for MAX_PATH 2014-11-21.
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "dirtree.h"

using namespace std; // Added 2014-11-21.

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	void CDirTree::print_file( list<string> &, int )
//
// PURPOSE:	Prints the filenames and the appropriata vertical bars
//		to make up the tree. Last it prints a blank line to
//		separate the files from the dirs printed after.
//

void CDirTree::print_file( list<string> &fname_list, int level )
{
	int i;
	list<string>::iterator fitr;
	for( fitr = fname_list.begin(); fitr != fname_list.end(); ++fitr )
	{
		// Print vertical bars before the filename.
		for( i = 0; i <= level; ++i )
		{
			if( bm.IsSet( i ))
				cout << BAR;
			else
				cout << NOBAR;
		}

		// Print the file name.
		cout << *fitr << endl;
	}

	// Print a blank line with only the vertical bars.
	for( i = 0; i <= level; ++i )
	{
		if( bm.IsSet( i ))
			cout << BAR;
		else
			cout << NOBAR;
	}
	cout << endl;
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	bool CDirTree::is_dots( string & )
//
// PURPOSE:	Returns true it the string passed are a dot or double dots.
//

bool CDirTree::is_dots( const string &str )
{
	return str == "." || str == "..";
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	bool CDirTree::is_hidden( string & )
//
// PURPOSE:	Returns true it the string passed begins with a dot.
//

bool CDirTree::is_hidden( const string &name )
{
	return name[0] == '.';
}

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	int CDirTree::scan( string, int )
//
// PURPOSE:	Scans the directory structure and prints a tree graph
//		with the dir and/or file names.
//

int CDirTree::scan( string inpath, int level /* = 0 */ ) // Commented out the default value 2014-11-21.
{
	DIR *dirp;
	if(( dirp = opendir( inpath.c_str())) == NULL )
		return 1;

	// If the last char of inpaht isn't a slash, add one.
	if( inpath[inpath.length() - 1] != '/' )
		inpath += "/";

	dirent *dp;
	struct stat st;
	list<string> fname_list;
	list<string> dname_list;

	// Scan the dir structure.
	while(( dp = readdir( dirp )) != NULL )
	{
		// Get info about the file or dir.
		lstat( string( inpath + dp->d_name ).c_str(), &st );

		// Is it a hidden file and should we display hidden files.
		if( !is_hidden( dp->d_name ) || opt.all )
		{
			// If it's a dir, add it to the dir list,
			// if it's a file and we should display files,
			// add it to the file list.
 			if( S_ISDIR( st.st_mode ))
			{
				// Don't add "." or ".." dirs.
				if( !is_dots( dp->d_name ))
					dname_list.push_front( dp->d_name );
			}
			else if( opt.file )
			{
				// If the file is a link, append an @.
				fname_list.push_front(
					S_ISLNK( st.st_mode )
					? string( dp->d_name ) + "@"
					: dp->d_name );
 		 	}
 		}
	}
	closedir( dirp );

	// If there are subdirs, set the bit so that we can print
	// the branch infront of the filenames.
	if( dname_list.size())
		bm.SetBit( level );

	// Sort the lists, depends on the -s switch.
	if( opt.sort )
	{
		fname_list.sort();
		dname_list.sort();
	}

	// Print the files and tree graphics.
	print_file( fname_list, level );

	// Done with the files, free some memory.
	fname_list.clear();

	// Print dirname and call scan() recursively.
	list<string>::iterator ditr;
	for( ditr = dname_list.begin(); ditr != dname_list.end(); ++ditr )
	{
		// If it's the last dir, change the beginning of the dirline.
		if( dname_list.back() == *ditr )
		{
			bm.ClearBit( level );
			dirline[0] = '\\';
		}
		else
		{
			dirline[0] = '+';
		}

		// Print vertical bars before the dirname.
		for( int i = 0; i <= ( level -1 ); ++i )
		{
			if( bm.IsSet( i ))
				cout << BAR;
			else
				cout << NOBAR;
		}
		// Print the dirname.
		cout << dirline << *ditr << "/" << endl;

		// Call this function recursively.
		scan( inpath + *ditr, level + 1 );
	}

	bm.ClearBit( level );
	
	return 0;
}


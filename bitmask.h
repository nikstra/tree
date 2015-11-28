////////////////////////////////////////////////////////////////////////////////
//
// FILE:
//	BitMask.h
//
// DESCRIPTION:
//	Declaration of class CBitMask.
//
// AUTHOR:
//	Niklas Strand
//
// DATE:
//	99-12-02
//
// CHANGES:
//      2014-11-21
//      Made some changes so that the code compiles on a modern system. For
//      example adding "using namespace std;".
//

#ifndef _BITMASK_H
#define _BITMASK_H

#include <list>

using namespace std; // Added 2014-11-21.

////////////////////////////////////////////////////////////////////////////////
// A shorter name for the list.

typedef list<unsigned int> bflist;

////////////////////////////////////////////////////////////////////////////////
//
// CLASS:	CBitMask
//
// PURPOSE:	Manages a bit field of unlimited length.
//

class CBitMask
{
public:
	CBitMask();
	bool IsSet( int pos );
	void SetBit( int pos );
	void ClearBit( int pos, bool clean = false );
	int GetFieldSize();
	void ClearUnused();

protected:
	bflist bitlist;
	const unsigned int one;
};

#endif // _BITMASK_H

////////////////////////////////////////////////////////////////////////////////
//
// FILE:
//	BitMask.cpp
//
// DESCRIPTION:
//	Definition of class CBitMask member functions.
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

#include "bitmask.h"

using namespace std; // Added 2014-11-21.

////////////////////////////////////////////////////////////////////////////////
//
// FUNCTION:	CBitMask::CBitMask()
//
// PURPOSE:	The constructor, initializes the list and the const member.
//

CBitMask::CBitMask() : one( 1 )
{
	bitlist.push_front( 0 );
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	bool CBitMask::IsSet( int )
//
// PURPOSE:	Returns true if the bit at pos is set.
//

bool CBitMask::IsSet( int pos )
{
	if( pos > ( GetFieldSize() -1 ))
		return false;

	bflist::iterator itr = bitlist.end();
	for( int i = 0; i <= ( pos / ( sizeof( int ) * 8 )); ++i )
		--itr;
	return *itr & ( one << ( pos % ( sizeof( int ) * 8 )));
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	void CBitMask::SetBit( int )
//
// PURPOSE:	Sets the bit at pos, it grows the list if necessary.
//

void CBitMask::SetBit( int pos )
{
	while( pos > ( GetFieldSize() -1 ))
		bitlist.push_front( 0 );
	bflist::iterator itr = bitlist.end();
	for( int i = 0; i <= ( pos / ( sizeof( int ) * 8 )); ++i )
		--itr;
	*itr |= one << ( pos % ( sizeof( int ) * 8 ));
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	void CBitMask::ClearBit( int, bool )
//
// PURPOSE:	Clears the bit at pos. If clean is true it calls
//		the ClearUnused() function.
//

void CBitMask::ClearBit( int pos, bool clean /*= false*/ )
{
	if( pos > ( GetFieldSize() -1 ))
		return;
	bflist::iterator itr = bitlist.end();
	for( int i = 0; i <= ( pos / ( sizeof( int ) * 8 )); ++i )
		--itr;
	*itr &= ~( one << ( pos % ( sizeof( int ) * 8 )));
	if( clean )
		ClearUnused();
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	int CBitMask::GetFieldSize()
//
// PURPOSE:	Returns the size of the bit field in number of bits.
//

int CBitMask::GetFieldSize()
{
	return bitlist.size() * sizeof( int ) * 8;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	void CBitMask::ClearUnused()
//
// PURPOSE:	Removes the upper part ( MSB ) of the bit field list
//		if all the bits are zero.
//

void CBitMask::ClearUnused()
{
	while( *bitlist.begin() == 0 && bitlist.begin() != bitlist.end())
		bitlist.pop_front();
}


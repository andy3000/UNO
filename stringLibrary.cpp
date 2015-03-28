#include <iostream>
#include "stringLibrary.h"

using namespace std;

const char NULL_CHAR = '\0';

void copyString( char* destPointer, const char* sourcePointer )
{
		
	// while string does not reach the end
	while( *sourcePointer != NULL_CHAR )
	{
		// copy source string to destination string
		*destPointer = *sourcePointer;
		sourcePointer++;
		destPointer++;
	}
	
	// place null char at the end of string
	*destPointer = NULL_CHAR;
	
}

int stringLength( char* sourcePointer )
{
	// initialize variables
	int index = 0;
	
	// increment while end of string is not reached
	while( *sourcePointer != NULL_CHAR )
	{
		sourcePointer++;
		index++;
	}
		
	// return string length
	return index;
}

void concatString( char* destPointer, char* sourcePointer )
{
	int destIndex = stringLength( destPointer );
	
	for( int i = 0; i < destIndex; i++ )
	{
		destPointer++;
	}

	while( *sourcePointer != NULL_CHAR )
	   {
			*destPointer = *sourcePointer;

			destPointer++;
			sourcePointer++;
	   }

	destPointer = NULL_CHAR;
}
   
bool compareStrings( char* one, const char* other )
{
	while( *one == *other )
	{
		if( *one == NULL_CHAR || *other == NULL_CHAR )
		{
			break;
		}
		
		one++;
		other++;
	
	}
	
	if( *one == NULL_CHAR && *other == NULL_CHAR )
	{
		return true;
	}
	else
	{
		return false;
	}

}   

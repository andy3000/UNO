#include <iostream>
#include "StackP.h"

using namespace std;

template <typename T>
Stack<T>::Stack( int arraySize )
{
	maxSize = arraySize;
	top = 0;
	actual = 0;
	data = new T[ arraySize ];
}

template <typename T>
Stack<T>::Stack( const Stack<T> &s )
{
	maxSize = s.maxSize;
	top = s.top;
	actual = s.actual;
	data = new T[ s.maxSize ];
	
	if( !s.empty() )
	{
		for( int i = 0; i < s.actual; i++ )
		{
			data[ i ] = s.data[ i ];
		}
	}
}

template <typename T>
Stack<T>::~Stack()
{
	maxSize = 0;
	top = 0;
	actual = 0;
	delete[]data;
}

template <typename T>
Stack<T>& Stack<T>::operator=( const Stack &s )
{	
	if( !s.empty() )
	{
		if( this == &s )
		{
			cout << "ERROR: CAN'T COPY THE SAME STACK!" << endl;
		}
		else
		{
			maxSize = s.maxSize;
			top = s.top;
			actual = s.actual;
			
			delete[]data;
			data = new T[ maxSize ];
			
			for( int i = 0; i < s.actual; i++ )
			{
				data[ i ] = s.data[ i ];
			}
		}			
	}
	else
	{
		cout << "ERROR: STACK IS EMPTY CAN'T ASSIGN!" << endl;
	}
	
	return *this;
}

template <typename T>
bool Stack<T>::full()const
{
	return ( actual == maxSize );
}

template <typename T>
bool Stack<T>::empty()const
{
	return ( actual == 0 );
}

template <typename T>
bool Stack<T>::push( T item )
{
	
	if( full() )
	{
		cout << "STACK IS FULL!" << endl;
		return false;
	}
	else
	{		
		for( int i = ( actual - 1 ); i >= 0; i-- )
		{
			data[ i + 1 ] = data[ i ];
		}

		data[ top ] = item;
		actual++;
		return true;
	}
}

template <typename T>
bool Stack<T>::pop( T &item )
{		
	if( empty() )
	{
		cout << "STACK IS EMPTY!" << endl;
		return false;
	}
	else
	{
		item = data[ top ];
		actual--;
		
		for( int i = 0; i < actual; i++ )
		{
			data[ i ] = data[ i + 1 ];
		}
		return true;
	}
}

template <typename T>
bool Stack<T>::clear()
{
	if( empty() )
	{
		return false;
	}
		
	actual = 0;
	return true;	
}

template <typename T>
ostream& operator<<( ostream &out, const Stack<T> &source )
{
	if( source.empty() )
	{
		out << "STACK IS EMPTY!" << endl;
	}
	else
	{
		for( int i = 0; i < source.actual; i++ )
		{
			if( i == 0 )
			{
				out << "===================" << endl;
				out << "[" << source.data[ i ] << "]";
				out << "===================" << endl;
			}
			else
			{
				out << "===================" << endl;
				out << source.data[ i ];
				out << "===================" << endl;
			}
		}
	}
	
	return out;
}

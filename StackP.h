#ifndef __STACKP_H_
#define __STACKP_H_
#include <iostream>

using namespace std;

template <typename T>
class Stack;

template <typename T>
ostream& operator<<( ostream&, const Stack<T> & );

template <typename T>
class Stack
{
	public:
	
		Stack( int = 108 );
		Stack( const Stack & );
		~Stack();
		
		bool push( T );
		bool pop( T & );
		bool empty() const;
		bool full() const;
		bool clear();
		
		Stack<T>& operator=( const Stack & );
		friend ostream& operator<< <>( ostream&, const Stack<T> & );
		
	private:
	
		int maxSize;
		int actual;
		int top;
		T* data;	
};

#endif

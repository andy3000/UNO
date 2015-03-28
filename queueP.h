#ifndef __QUEUEP_H_
#define __QUEUEP_H_
#include <iostream>
#include "listP.h"

using namespace std;

template <typename T>
class Queue
{
	public:
	
		Queue( int = 0 );
		Queue( const Queue & );
		~Queue();
		
		bool enqueue( T );
        bool dequeue( T & );
		bool empty() const;
		bool full() const;
		bool clear();
		
		Queue<T>& operator=( const Queue & );
		bool operator==( const Queue & ) const;
		friend ostream& operator<< <>( ostream&, const Queue<T> & );
		
	private:
	
		Node<T>* front;
		Node<T>* rear;
};

#endif

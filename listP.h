#ifndef __LISTP_H_
#define __LISTP_H_
#include <iostream>
#include <cstdlib>

using namespace std;

template <typename T>
class List;

template <typename T>
class Node
{
	private:
	
		Node( T, Node* );
		T data;
		Node* next;
};

template <typename T>
class List
{

	public:
	
		List( int = 0 );
		List( const List & );
		List<T>& operator=( const List & );
		~List();
		
		bool gotoBeginning();
		bool gotoEnd();
		bool gotoNext();
		bool gotoPrior();
		bool insertAfter( T );
		bool insertBefore( T );
		bool remove( T & );
		bool replace( T );
		bool getCursor( T & ) const;
		bool empty() const;
		bool full() const;
		bool clear();
		
		void sortOne();
		
	private:
	
		Node<T>* head;
		Node<T>* cursor;
};

#endif

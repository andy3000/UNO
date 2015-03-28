#include <iostream>
#include "ListLinked.h"

using namespace std;

template <typename T>
Node<T>::Node( T item, Node* location )
{
	data = item;
	next = location;
}

template <typename T>
List<T>::List( int ignore )
{
	head = NULL;
	cursor = NULL;
}

template <typename T>
List<T>::List( const List &source )
{
	// initialize variables
	Node<T>* sourceNode = source.head;
	Node<T>* tempNode;
	Node<T>* destNode;
	
	// if source list has been created then copy 
	if( sourceNode != NULL )
	{	
		// create head node & copy source data
		head = new Node<T>( sourceNode->data, NULL );
		
		// set head equal to destNode
		destNode = head;
		
		// move sourceNode to next node
		sourceNode = sourceNode->next;
		
		// if source cursor is equal to source head
		// then set cursor equal to head
		if( source.cursor == source.head )
		{
			cursor = head;
		}		
		
		// while last source node has not been copied
		while( sourceNode != NULL )
		{
			// create temp node & copy source data 
			tempNode = new Node<T>( sourceNode->data, NULL );
			
			// link last node to new node
			destNode->next = tempNode;
			
			// move pointer to new node
			destNode = tempNode;
			
			// if source node is equal to source's cursor
			// then make new node equal to cursor
			if( sourceNode == source.cursor )
			{
				cursor = tempNode;
			}

			// move to next node
			sourceNode = sourceNode->next;			
		}
		
	}
	// if source list is empty create new list 
	else
	{
		head = NULL;
		cursor = NULL;
	}

	destNode = NULL;
	tempNode = NULL;

}

template <typename T>
List<T>::~List()
{
	// initialize variables
	Node<T>* currentNode = head;
	Node<T>* tempNode;
	
	// if list has been created then delete nodes
	if( currentNode != NULL )
	{
		// point temp node to current node to be deallocated
		tempNode = currentNode;
		
		// move to next node to deallocate
		currentNode = currentNode->next;
		
		// deallocate node
		delete tempNode;
		
		// while last node has not been deallocated
		while( currentNode != NULL )
		{
			tempNode = currentNode;
			currentNode = currentNode->next;
			delete tempNode;
		}
	}
	
	head = NULL;
	cursor = NULL;
}

template <typename T>
List<T>& List<T>::operator=( const List<T> &source )
{
	// initialize variables
	Node<T>* sourceNode = source.head;
	Node<T>* tempNode;
	Node<T>* destNode = head;

	// if source is the same can't copy
	if( this == &source )
	{
		cout << "CAN'T DO IT MAN!" << endl;
	}
	// if source is empty then clear 
	else if( sourceNode == NULL )
	{
		clear();
	}
	// if source has list then copy over
	else
	{
		// clear destination list
		clear();
		
		// create head node & copy source data	
		head = new Node<T>( sourceNode->data, NULL );
		
		// set head equal to destNode		
		destNode = head;
		
		// move source node to next node
		sourceNode = sourceNode->next;
		
		// if source cursor is equal to source head
		// then make cursor equal to head
		if( source.cursor == source.head )
		{
			cursor = head;
		}
		
		// while last node has not been copied
		while( sourceNode != NULL )
		{
			// create temp node & copy source data 
			tempNode = new Node<T>( sourceNode->data, NULL );
			
			// link last node to new node
			destNode->next = tempNode;
			
			// move pointer to new node
			destNode = tempNode;
			
			// if source node is equal to source's cursor
			// then make new node equal to cursor
			if( sourceNode == source.cursor )
			{
				cursor = tempNode;
			}

			// move source node to next node
			sourceNode = sourceNode->next;			
		}
	}
	
	// return list
	return *this;
}

template <typename T>
bool List<T>::gotoBeginning()//////////////////////////check what if there is no nodes yet
{
	// if cursor is at head then return true
	if( cursor == head )
	{
		return true;
	}
	// else move cursor to head and return false
	else
	{
		cursor = head;
		return false;
	}
}

template <typename T>
bool List<T>::gotoEnd()//////////////////////////check what if there is no nodes yet
{
	// if cursor is at end return true
	if( cursor->next == NULL )
	{
		return false;
	}
	// if list is empty return false
	else if( empty() )
	{
		return false;
	}
	// else move cursor to the end of list
	else
	{
		while( cursor->next != NULL )
		{
			cursor = cursor->next;
		}
		
		return true;
	}
}

template <typename T>
bool List<T>::gotoNext()
{
	// if at the end of the list return false
	if( cursor->next == NULL )
	{
		return false;
	}
	// if list is empty return false
	else if( empty() )
	{
		return false;
	}
	// else move cursor to next node
	else
	{
		cursor = cursor->next;
		return true;
	}
}

template <typename T>
bool List<T>::gotoPrior()
{
	// initialize variables
	Node<T>* tempNode = head;
	
	// if cursor is at head return false
	if( cursor == head )
	{
		return false;
	}
	// if list is empty return false
	else if( empty() )
	{
		return false;
	}
	// else move cursor to prior node
	else
	{
		// while tempNode's next is not equal to cursor
		while( tempNode->next != cursor )
		{
			// move temp node to next node
			tempNode = tempNode->next;
		}
		
		// once tempNode's next points to cursor
		// set cursor equal to tempNode
		cursor = tempNode;
		
		return true;
	}
}

template <typename T>
bool List<T>::insertAfter( T item )
{
	// initialize variables
	Node<T>* tempNode;
	
	// if list has not been created, create a list
	// and store the item in first node
	if( head == NULL )
	{
		head = new Node<T>( item, NULL );
		cursor = head;
		return true;
	}
	// else create new node after cursor
	else
	{
		// create new tempNode with item and cursor next for it's next
		tempNode = new Node<T>( item, cursor->next );
		
		// link tempNode after the cursor
		cursor->next = tempNode;
		
		// move cursor to new node
		cursor = tempNode;
		
		tempNode = NULL;
		return true;
	}
}

template <typename T>
bool List<T>::insertBefore( T item )
{
	// initialize variables
	Node<T>* tempNode;
	
	// if list has not been created, create a list
	// and store the item in first node
	if( head == NULL )
	{
		head = new Node<T>( item, NULL );
		cursor = head;
		return true;
	}
	// if cursor is at first node then create node
	// and move head to the new node
	else if( cursor == head )
	{
		// create temp node with item and next equal to head
		tempNode = new Node<T>( item, head );
		
		// link head and temp node and set cursor to new node
		head = cursor = tempNode;
		return true;
	}
	// else create a new node before cursor
	else
	{
		// move cursor to prior node
		gotoPrior();
		
		// create temp node with item and next equal to cursor's next
		tempNode = new Node<T>( item, cursor->next );
		
		// link cursor and temp node
		cursor->next = tempNode;
		
		// move cursor to new node
		cursor = tempNode;
		
		return true;
	}		
}

template <typename T>
bool List<T>::remove( T &item )
{
	// initialize variables
	Node<T>* tempNode;
	
	// if empty return false
	if( empty() )
	{
		return false;
	}
	// if cursor is at the head remove item
	// and move cursor to new head
	else if( cursor == head )
	{
		// get item from cursor
		item = cursor->data;
		
		// move head to next node
		head = head->next;
		
		// delete node at cursor
		delete cursor;
		
		// move cursor to new head
		cursor = head;
		return true;
	}
	
	// if cursor is at last node
	else if( cursor->next == NULL )
	{
		// get item from cursor
		item = cursor->data;
		
		// tempNode points to cursor node
		tempNode = cursor;
		
		// go to prior node and make it new last node in list
		gotoPrior();
		cursor->next = NULL;
		
		// move cursor to the head
		cursor = head;
		
		// delete the previous last node
		delete tempNode;		
		
		return true;
	}
	
	// else remove node and link list
	else
	{
		// get item from cursor 
		item = cursor->data;
		
		// tempNode points to the cursor node
		tempNode = cursor;
		
		// go to prior node
		gotoPrior();
			
		// link prior node to the node after the node to be removed
		cursor->next = tempNode->next;
		
		// delete the temp node
		delete tempNode;
		
		return true;
	}
}

template <typename T>
bool List<T>::replace( T item )
{
	// if empty create new list with item
	if( empty() )
	{
		head = new Node<T>( item, NULL );
		cursor = head;
	}
	// else replace data with new item
	else
	{
		cursor->data = item;
	}
		
	return true;
	
}

template <typename T>
bool List<T>::getCursor( T &item ) const
{
	// if list empty return false
	if( empty() )
	{
		return false;
	}
	// else return item in cursor
	else
	{
		item = cursor->data;
		return true;
	}
}

template <typename T>
bool List<T>::empty() const
{
	return ( head == NULL );
}

template <typename T>
bool List<T>::full() const
{
	return false;
}

template <typename T>
bool List<T>::clear()
{
	// initialize variables
	Node<T>* nodePointer = head;
	Node<T>* deleteNode;
	
	// if list is empty return false
	if( empty() )
	{
		return false;
	}
	// if list exists then delete it node by node until end is reached	
	else if( nodePointer != NULL )
	{
		// tempNode points to first node to be deleted
		deleteNode = nodePointer;
		
		// move to next node
		nodePointer = nodePointer->next;
		
		// delete node
		delete deleteNode;
		
		// while last node has not been delete
		while( nodePointer != NULL )
		{
			// tempNode points to first node to be deleted
			deleteNode = nodePointer;
			
			// move to next node
			nodePointer = nodePointer->next;
			
			// delete node
			delete deleteNode;
		}
	}

	head = NULL;
	cursor = NULL;
	
	return true;
}

template <typename T>
void List<T>::sortOne()
{
	int numberOfNodes = 0;
	
	Node<T>* countNodes = head;
	Node<T>* currentNode;
	Node<T>* trailNode;
	Node<T>* tempNode;
	
	while( countNodes != NULL )
	{
		numberOfNodes++;
		countNodes = countNodes->next;
	}
	
	for( int i = 0; i < numberOfNodes; i++ )
	{
		currentNode = trailNode = head;
		
		while( currentNode->next != NULL )
		{						
			if( currentNode->data > currentNode->next->data )
			{
				tempNode = currentNode->next;
				currentNode->next = currentNode->next->next;
				tempNode->next = currentNode;
				
				if( currentNode == head )
				{
					head = trailNode = tempNode;
				}
				else
				{
					trailNode->next = tempNode;
				}
				
				currentNode = tempNode;
			}
			
			if( currentNode->data == 'c' )
			{
				tempNode = currentNode->next;
				currentNode->next = currentNode->next->next;
				tempNode->next = currentNode;
				
				if( currentNode == head )
				{
					head = trailNode = tempNode;
				}
				else
				{
					trailNode->next = tempNode;
				}
				
				currentNode = tempNode;
			}
			
			
			trailNode = currentNode;
			currentNode = currentNode->next;
		}
	}
	
	gotoBeginning();
}

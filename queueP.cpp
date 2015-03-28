#include <iostream>
#include "queueP.h"

template <typename T>
Queue<T>::Queue( int ignore )
{
	front = NULL;
	rear = NULL;
}

template <typename T>
Queue<T>::Queue( const Queue<T> &source )
{	
	// initialize variables
	Node<T>* sourceNode = source.front;
	Node<T>* tempNode;
	Node<T>* destNode;
	
	if( sourceNode != NULL )
	{
		front = new Node<T>( sourceNode->data, NULL );
		destNode = front;
		sourceNode = sourceNode->next;
		
		while( sourceNode != NULL )
		{
			tempNode = new Node<T>( sourceNode->data, NULL );
			destNode->next = tempNode;
			destNode = tempNode;
			sourceNode = sourceNode->next;
			
			if( sourceNode == NULL )
			{
				rear = destNode;
			}
		}
	}
	else
	{
		front = NULL;
		rear = NULL;
	}
}

template <typename T>
Queue<T>::~Queue()
{
	// initialize variables
	Node<T>* currentNode = front;
	Node<T>* tempNode;
	
	if( currentNode != NULL )
	{
		tempNode = currentNode;
		currentNode = currentNode->next;
		delete tempNode;
		
		while( currentNode != NULL )
		{
			tempNode = currentNode;
			currentNode = currentNode->next;
			delete tempNode;
		}
	}

	front = NULL;
	rear = NULL;
}

template <typename T>
bool Queue<T>::enqueue( T item )
{
	Node<T>* tempNode;
	
	tempNode = new Node<T>( item, NULL );
	
	if( empty() )
	{
		front = tempNode;
	}
	else
	{
		rear->next = tempNode;
	}
	
	rear = tempNode;
	
	return true;
}

template <typename T>
bool Queue<T>::dequeue( T &item )
{
	Node<T>* tempNode;
	
	if( empty() )
	{
		cout << "QUEUE IS EMPTY!" << endl;
		return false;
	}
	else
	{
		item = front->data;
		tempNode = front;
		front = front->next;
		
		if( front == NULL )
		{
			rear = NULL;
		}
		
		delete tempNode;
		return true;
	}
}

template <typename T>
bool Queue<T>::empty() const
{
	return ( front == NULL );
}

template <typename T>
bool Queue<T>::full() const
{
	return false;
}

template <typename T>
bool Queue<T>::clear()
{
	// initialize variables
	Node<T>* currentNode = front;
	Node<T>* tempNode;
	
	if( empty() )
	{
		return false;
	}
	else
	{
	
		if( currentNode != NULL )
		{
			tempNode = currentNode;
			currentNode = currentNode->next;
			delete tempNode;
			
			while( currentNode != NULL )
			{
				tempNode = currentNode;
				currentNode = currentNode->next;
				delete tempNode;
			}
		}

		front = NULL;
		rear = NULL;
	}
	
	return true;
}

template <typename T>
ostream& operator<<( ostream &out, const Queue<T> &source )
{
	Node<T>* temp = source.front;
	
	if( source.empty() )
	{
		out << "QUEUE IS EMPTY!" << endl;
	}
	else
	{
		out << "[" << temp->data << "]" << endl;
		
		temp = temp->next;

		while( temp != NULL )
		{
			if( temp == source.rear )
			{
				out << "|" << temp->data << "|" << endl;
			}
			else
			{
				out << temp->data << endl;
			}
			
			temp = temp->next;
		}
	}
	
	return out;
}

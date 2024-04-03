/*
* Author: Andrew Vu, Brian Macias Garcia
* Changelog:
* 1.Apr.2024 Created
*/

#pragma once
#include <iostream>
#include "DataTypes.h"

using namespace std;
using namespace DataTypes;

template <typename T>
class LinkedList2D
{
/*
* Author: Brian Macias Garcia
* ChangeLog:
* 26.Feb.2024 Created
* 29.Feb.2024 Copied from LinkedList2D
* 4.March.2024 Finalized
*/

/*
* Notes:
* 1) Optimize the findNode function to take advantage of the fact that their is a pointer to the last node and it doublylinked
* 2)
*/
public:
	LinkedList2D()
	{
	}

	LinkedList2D(const LinkedList2D<T>& list) // Create a new object of this with what is referenced
	{
		// See the equals operator for notes
		if (!list.first)
			return;

		first = new DoublyNode<T>{ nullptr, list.first->getData(), nullptr };
		DoublyNode<T>* temp = first;
		DoublyNode<T>* nextItem = list.first->getNext();
		for (int e = 1; e < list.size; e++)
		{
			temp->setNext(new DoublyNode<T>{ temp, nextItem->getData(), nullptr });
			temp = temp->getNext();
			nextItem = nextItem->getNext();
		}

		last = temp; // assign last

		size = list.size;
	}

	LinkedList2D<T>& operator=(const LinkedList2D<T>& list)
	{
		if (!list.first) // "IT'S FUC**** RAW, GET OUT!" - Gordon Ramsey
			return *this;

		for (int e = 0; e < size; e++)
		{
			DoublyNode<T>* del{ first };
			first = first->getNext();
			delete del;
		}

		first = new DoublyNode<T>{ nullptr, list.first->getData(), nullptr }; // Create the head node
		DoublyNode<T>* temp = first; // set the node mover to head
		DoublyNode<T>* nextItem = list.first->getNext(); // set the next node to pull data from
		for (int e = 1; e < list.size; e++)
		{
			temp->setNext(new DoublyNode<T>{ temp, nextItem->getData(), nullptr }); // Create the next new node.
			temp = temp->getNext(); // set the next node to be edited
			nextItem = nextItem->getNext(); // also move a node in the referenced list
		}

		last = temp; // assign last

		size = list.size; // set the size ones

		return *this;
	}

	void prepend(T item)
	{
		DoublyNode<T>* newNode = new DoublyNode<T>{ nullptr, item, first };

		first = newNode;

		size++;
	}

	void append(T item)
	{
		DoublyNode<T>* newNode = new DoublyNode<T>{ last, item, nullptr }; // Create node

		if (size == 0) // Checks
		{
			first = newNode;
			size++;
			return;
		}

		//findNode(size - 1)->setNext(newNode);
		last->setNext(newNode);

		size++;
	}

	T get(int index)
	{
		return findNode(index)->getData();
	}

	void set(int index, T item)
	{
		findNode(index)->setData(item); // "Secrete" - IRS
	}

	int getSize()
	{
		return size;
	}

	void insert(int index, T item)
	{
		if (index == 0)
		{
			prepend(item);
			return;
		}

		DoublyNode<T>* node{ findNode(index - 1) }; // find that damm node

		DoublyNode<T>* insert = new DoublyNode<T>{ node, item, node->getNext() }; // create a new node pointing to the next node
		node->setNext(insert); // set this node to point to insert

		size++;
	}

	T remove(int index)
	{
		DoublyNode<T>* del{ nullptr };
		T value{ 0 };
		if (index == 0)
		{
			del = first;
			value = first->getData();
			first = first->getNext();
		}
		else
		{
			DoublyNode<T>* node{ findNode(index - 1) }; // get the one right before it
			value = node->getNext()->getData(); // get the value of the node to be deleted
			del = node->getNext();
			node->setNext(node->getNext()->getNext()); // set the this node to point to the node right after the one in front
			node->setPrevious(node);
		}

		delete del; // YOU ARE DED NO BIG SURPRISE
		size--;
		return value;
	}

	// Needs patching
	void removeAll(T value)
	{
		//DoublyNode<T>* last{ nullptr };
		DoublyNode<T>* current{ first };
		for (int e = 0; e < size; e++)
		{
			if (current->getData() == value)
			{
				DoublyNode<T>* del{ nullptr };
				if (current->previous) // Check for null ptr it is incase if the node were looking at is the first one in the their.
				{
					current->previous->next = current->next;
					current->next->previous = current->previous;
					del = current;
				}
				else
				{
					first = current->next;
					first->previous = nullptr;
					del = current;
				}
				// Keep last the same
				current = current->next; // Skip over the discarted node
				delete del; // Delete the node
				size--; // Decrement
			}
			else
			{
				last = current; // Current node becomes last known node
				current = current->getNext(); // Advance to the next
			}
		}

		//size = 0; 
	}

	~LinkedList2D()
	{
		for (int e = 0; e < size; e++)
		{
			DoublyNode<T>* del{ first };
			first = first->getNext();
			delete del;
		}
	}
protected:
	int size{ 0 };
	DoublyNode<T>* first{ nullptr };
	DoublyNode<T>* last{ nullptr };

	DoublyNode<T>* findNode(int index)
	{
		if (index >= size)
			return NULL;

		DoublyNode<T>* node = first;
		for (int i = 0; i < index; i++) // find that damm node
			node = node->getNext();

		return node;
	}

	template <typename T>
	friend ostream& operator<<(ostream& out, const LinkedList2D<T>& list);

};

template <typename T>
ostream& operator<<(ostream& out, const LinkedList2D<T>& list)
{
	DoublyNode<T>* node = list.first;
	cout << "[";
	for (int e = 0; e < list.size - 1; e++)
	{
		cout << node->getData() << ", ";
		node = node->getNext();
	}
	if (node)
		cout << node->getData();
	cout << "]";

	return out;
}


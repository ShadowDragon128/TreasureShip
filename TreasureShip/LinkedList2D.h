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
public:
	LinkedList2D()
	{
	}

	LinkedList2D(const LinkedList2D<T>& list) // Create a new object of this with what is referenced
	{
		// See the equals operator for notes
		if (!list.front)
			return;

		front = new Node<T>{ list.front->getData(), list.front->getNext() };
		Node<T>* temp = front;
		Node<T>* nextItem = list.front->getNext();
		for (int e = 1; e < list.size; e++)
		{
			temp->setNext(new Node<T>{ nextItem->getData(), nullptr });
			temp = temp->getNext();
			nextItem = nextItem->getNext();
		}

		size = list.size;
	}

	LinkedList2D<T>& operator=(const LinkedList2D<T>& list)
	{
		if (!list.front) // "IT'S FUC**** RAW, GET OUT!" - Gordon Ramsey
			return *this;

		for (int e = 0; e < size; e++)
		{
			Node<T>* del{ front };
			front = front->getNext();
			delete del;
		}

		front = new Node<T>{ list.front->getData(), list.front->getNext() }; // Create the head node
		Node<T>* temp = front; // set the node mover to head
		Node<T>* nextItem = list.front->getNext(); // set the next node to pull data from
		for (int e = 1; e < list.size; e++)
		{
			temp->setNext(new Node<T>{ nextItem->getData(), nullptr }); // Create the next new node.
			temp = temp->getNext(); // set the next node to be edited
			nextItem = nextItem->getNext(); // also move a node in the referenced list
		}

		size = list.size; // set the size ones

		return *this;
	}

	void prepend(T item)
	{
		Node<T>* newNode = new Node<T>{ item, front };

		front = newNode;

		size++;
	}

	void append(T item)
	{
		Node<T>* newNode = new Node<T>{ item, nullptr }; // Create node

		if (size == 0) // Checks
		{
			front = newNode;
			size++;
			return;
		}

		findNode<T>(size - 1)->setNext(newNode);

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
			//Node<T>* insert = new Node<T>{ item, front };
			//front = insert;
			//size++;
			prepend(item);
			return;
		}

		Node<T>* node{ findNode(index - 1) }; // find that damm node

		Node<T>* insert = new Node<T>{ item, node->getNext() }; // create a new node pointing to the next node
		node->setNext(insert); // set this node to point to insert

		size++;
	}

	T remove(int index)
	{
		Node<T>* del{ nullptr };
		T value{ 0 };
		if (index == 0)
		{
			del = front;
			value = front->getData();
			front = front->getNext();
		}
		else
		{
			Node<T>* node{ findNode(index - 1) }; // get the one right before it
			value = node->getNext()->getData(); // get the value of the node to be deleted
			del = node->getNext();
			node->setNext(node->getNext()->getNext()); // set the this node to point to the node right after the one in front
		}

		delete del; // YOU ARE DED NO BIG SURPRISE
		size--;
		return value;
	}

	void removeAll(T value)
	{
		Node<T>* last{ nullptr };
		Node<T>* current{ front };
		for (int e = 0; e < size; e++)
		{
			if (current->getData() == value)
			{
				Node<T>* del{ nullptr };
				if (last) // Check for null ptr it is incase if the node were looking at is the first one in the their.
				{
					last->setNext(current->getNext());
					del = current;
				}
				else
				{
					front = current->getNext();
					del = current;
				}
				// Keep last the same
				current = current->getNext(); // Skip over the discarted node
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
			Node<T>* del{ front };
			front = front->getNext();
			delete del;
		}
	}
private:
	int size{ 0 };
	Node<T>* front{ nullptr };

	Node<T>* findNode(int index)
	{
		if (index >= size)
			return NULL;

		Node<T>* node = front;
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
	Node<T>* node = list.front;
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


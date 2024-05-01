/*
* Author: Andrew Vu, Brian Macias Garcia
* Changelog:
* 1.Apr.2024 Copy of Brian's LinkedList class
* 4.April.2024 Modified to use doubly linked lists
* 25 Apr. 2024 Copied over
*/

#pragma once
#include <iostream>
#include "DataTypes.h"

using namespace std;
using namespace DataTypes;

template <typename T>
class LinkedList
{
/*
* Notes:
* 1) Optimize the findNode function to take advantage of the fact their's pointers to the last node as its doublylinked
* 2) 
*/
public:
	LinkedList()
	{
	}

	LinkedList(const LinkedList<T>& list) // Create a new object of this with what is referenced
	{
		// See the equals operator for notes
		if (!list.first)
			return;

		first = new DoublyNode<T>{ nullptr, list.first->getData(), nullptr };
		DoublyNode<T>* temp = first;
		DoublyNode<T>* nextItem = list.first->getNext();
		for (int e = 1; e < list.size; e++)
		{
			temp->setNext(new DoublyNode<T>{ temp, nextItem->data, nullptr });
			temp = temp->getNext();
			nextItem = nextItem->getNext();
		}

		last = temp; // assign last

		size = list.size;
	}

	LinkedList<T>& operator=(const LinkedList<T>& list)
	{
		if (!list.first) // 
			return *this;

		for (int e = 0; e < size; e++)
		{
			DoublyNode<T>* del{ first };
			first = first->getNext();
			delete del;
		}

		first = new DoublyNode<T>{ nullptr, list.first->data, nullptr }; // Create the head node
		DoublyNode<T>* temp = first; // set the node mover to head
		DoublyNode<T>* nextItem = list.first->next; // set the next node to pull data from
		for (int e = 1; e < list.size; e++)
		{
			temp->setNext(new DoublyNode<T>{ temp, nextItem->data, nullptr }); // Create the next new node.
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
			last = newNode;
			size++;
			return;
		}

		//findNode(size - 1)->setNext(newNode);
		last->setNext(newNode);
		last = newNode;

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

		DoublyNode<T>* node{ findNode(index - 1) }; // find that node
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
			DoublyNode<T>* node{ findNode(index) };
			value = node->getData();
			del = node;
			node->getPrevious()->setNext(node->getNext());
			node->getNext()->setPrevious(node->getPrevious());

			//DoublyNode<T>* node{ findNode(index - 1) }; // get the one right before it
			//value = node->next->data; // get the value of the node to be deleted
			//del = node->next;
			//node->next = node->next->next; // set the this node to point to the node right after the one in front
			//node->previous = node;
		}

		delete del; // YOU ARE DED NO BIG SURPRISE
		size--;
		return value;
	}

	void removeAll(T value)
	{
		//DoublyNode<T>* last{ nullptr };
		DoublyNode<T>* current{ first };
		for (int e = 0; e < size; e++)
		{
			if (current->getData() == value)
			{
				DoublyNode<T>* del{ nullptr };
				if (current->getPrevious()) // Check for null ptr it is incase if the node were looking at is the first one in the their.
				{
					current->getPrevious()->setNext(current->getNext()); // Set the previous node's next node to the currents next node
					current->getNext()->setPrevious(current->getPrevious()); // Set the next node's previous node to the currents previous node
					del = current; // Assign the node for deletion
				}
				else
				{
					first = current->getNext(); // Set the head node to the next over
					first->setPrevious(nullptr); // Deassociate the previous node
					del = current;
				}
				// Keep last the same
				current = current->getNext(); // Advance
				delete del; // Delete the node
				size--; // Decrement
			}
			else
			{
				current = current->getNext(); // Advance to the next
			}
		}

		//size = 0; 
	}

	~LinkedList()
	{
		if (first)
		{
			for (int e = 0; e < size; e++)
			{
				DoublyNode<T>* del{ first };
				first = first->getNext();
				delete del;
			}

			first = nullptr;
			last = nullptr;
		}
	}

protected:
	int size{ 0 };
	DoublyNode<T>* first{ nullptr };
	DoublyNode<T>* last{ nullptr };

	DoublyNode<T>* findNode(int index)
	{
		if (index >= size)
			return last;

		if (index < 0)
			return first;

		DoublyNode<T>* node = first;
		for (int i = 0; i < index; i++) // find that damm node
			node = node->next;

		return node;
	}

	template <typename T>
	friend ostream& operator<<(ostream& out, const LinkedList<T>& list);

};

template <typename T>
ostream& operator<<(ostream& out, const LinkedList<T>& list)
{
	DoublyNode<T>* node = list.first;
	out << "[";
	for (int e = 0; e < list.size - 1; e++)
	{
		out << node->getData() << ", ";
		node = node->getNext();
	}
	if (node)
		out << node->getData();
	out << "]";

	return out;
}


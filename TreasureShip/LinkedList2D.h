/*
* Author: Andrew Vu, Brian Macias Garcia
* Changelog:
* 1.Apr.2024 Created
*/

#pragma once
#include "LinkedList.h"
#include "DataTypes.h"

using namespace DataTypes;

// Incomplete System

template <typename T>
class LinkedList2D : private LinkedList<T>
{
public:
	LinkedList2D() : LinkedList<T>() {
	}

	LinkedList2D(const LinkedList2D<T>& list) : LinkedList<T>() {
		if (!list.headList)
			return;
		
		headList = new DoublyNode<LinkedList<T>*>{ nullptr, new LinkedList<T>{ list.first }, nullptr }; // Create the first node to hold the firs list
		DoublyNode<LinkedList<T>*>* temp = headList; // staring node
		DoublyNode<LinkedList<T>*>* nextItem = list.headList->getNext(); // go to the next list to copy
		for (int x = 0; x < xSize; x++)
		{
			temp->setNext(new DoublyNode<LinkedList<T>*>{ temp, new LinkedList<T>{ nextItem->data }, nullptr }); // set the next node to this and this is a copy node of a list
			temp = temp->getNext(); // move over a node list
			nextItem = nextItem->getNext(); // get the newly created node
		}

		// create the last node sometime

		xSize = list.size;
	}

	LinkedList2D<T>& operator=(const LinkedList2D<T>& list) // Incomplete
	{
		if (!list.headList)
			return;

		for (int e = 0; e < xSize; e++)
		{
			DoublyNode<LinkedList<T>*>* del{ headList };
			for (int g = 0; g < static_cast<LinkedList<T>*>(headList->getData())->getSize(); g++) { // Everything is fine HOOMEEESs

			}
			headList = headList->getNext();
			delete del;
		}

		headList = new DoublyNode<LinkedList<T>*>{ nullptr, new LinkedList<T>{ list.first }, nullptr }; // Create the first node to hold the firs list
		DoublyNode<LinkedList<T>*>* temp = headList; // staring node
		DoublyNode<LinkedList<T>*>* nextItem = list.headList->getNext(); // go to the next list to copy
		for (int x = 0; x < xSize; x++)
		{
			temp->setNext(new DoublyNode<LinkedList<T>*>{ temp, new LinkedList<T>{ nextItem->data }, nullptr }); // set the next node to this and this is a copy node of a list
			temp = temp->getNext(); // move over a node list
			nextItem = nextItem->getNext(); // get the newly created node
		}

		// create the last node sometime

		xSize = list.size;
	}

	void prepend(T item, int index)
	{
		findList(index)->prepend(item);
	}

	void append(T item, int index)
	{
		findList(index)->append(item);
	}

	T get(Point<int> point)
	{
		return findNode(point)->getData();
	}

	void set(Point<int> point, T item)
	{
		findNode(point)->setData(item);
	}

	int getSize()
	{
		return xSize;
	}

	void insert(Point<int> point, T item)
	{
		findList(point.X)->insert(point.Y);
	}

	T remove(Point<int> point)
	{
		return findList(point.X)->remove(point.Y);
	}

	// Look through all the list 
	void removeAll(T value)
	{
		DoublyNode<LinkedList<T>*>* currentList = headList;
		for (int e = 0; e < xSize; e++)
		{
			//LinkedList<T>* s = currentList->getData();
			//s->removeAll(value);
			static_cast<LinkedList<T>*>(currentList->getData())->removeAll(value); // YOur fine
		}
	}

	~LinkedList2D()
	{
		if (headList)
		{
			DoublyNode<T>* first = headList;
			for (int x = 0; x < xSize; x++)
			{
				DoublyNode<T>* temp = first;
				first = first->getNext();
				delete temp;
			}
		}
	}

protected:
	DoublyNode<LinkedList<T>*>* headList;
	int xSize{ 0 };

	LinkedList<T>* findList(int index)
	{
		if (index >= xSize)
			return NULL;

		DoublyNode<LinkedList<T>*>* xAxisNode = headList; // Find X list

		//int i, e;
		//if (index < (xSize / 2))
		//{
		//	i{ 0 };
		//	e{ 1 };
		//}
		//else
		//{
		//	i{ xSize };
		//	e{ -1 };
		//}

		for (int i = 0; i < index; i++) {
			xAxisNode = xAxisNode->getNext();
		}

		return xAxisNode->getData(); // Get the pointer for the List
	}

	DoublyNode<T>* findNode(Point<int> point)
	{
		return findList(point.X)->findNode(point.Y); // Find Y
	}
};


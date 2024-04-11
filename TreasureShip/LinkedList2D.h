/*
* Author: Andrew Vu, Brian Macias Garcia
* Changelog:
* 1.Apr.2024 Created
*/

#pragma once
#include "LinkedList.h"
#include "DataTypes.h"

using namespace DataTypes;

template <typename T>
class LinkedList2D : private LinkedList<T>
{
public:
	LinkedList2D() : LinkedList<T>() {
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


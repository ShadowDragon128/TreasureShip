#pragma once
#include "LinkedList2D.h"
#include "DataTypes.h"

using namespace DataTypes;

template <typename T>
class LinkedList3D : private LinkedList2D<T>
{
public:
	LinkedList3D() : LinkedList2D<T>() {
	}

	void prepend(T item, int index)
	{

	}

	void append(T item, int index)
	{

	}

	T get(Point<int> point)
	{
		return findNode(point)->data;
	}

	void set(Point<int> point, T item)
	{
		findNode(point)->data = item;
	}

	int getSize()
	{
		return xSize;
	}

	void insert(Point<int> point, T item)
	{

	}

	T remove(Point<int> point)
	{

	}

	void removeAll(T value)
	{

	}

protected:
	Node<LinkedList2D<T>>* headList;
	int xSize{ 0 };

	Node<T>* findNode(Point<int> point)
	{
		if (point.X >= size)
			return NULL; // Sup

		Node<LinkedList2D<T>>* xAxisNode = headList; // Find X list
		for (int i = 0; i < point.X; i++) {
			xAxisNode = xAxisNode->getNext();
		}
		
		LinkedList2D<T>* xAxisList = xAxisNode->data; // Get the pointer for the List

		return xAxisList->findNode(point.Y); // Find Y
	}
};


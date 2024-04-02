#pragma once
#include "LinkedList2D.h"
#include "DataTypes.h"

using namespace DataTypes;

template <typename T>
class LinkedList3D
{
public:
	LinkedList3D() {
	}

	T get(Point<int> point)
	{
		return findNode(point)->data;
	}

	void set(Point<int> point, T item)
	{
		findNode(point)->setData(item);
	}

private:
	Node<LinkedList2D<T>>* headList;
	int size{ 0 };

	Node<T>* findNode(Point<int> point)
	{
		if (point.X >= size)
			return NULL;

		Node<LinkedList2D<T>>* xAxisNode = headList; // Find X list
		for (int i = 0; i < point.X; i++) {
			xAxisNode = xAxisNode->getNext();
		}
		
		LinkedList2D<T>* xAxisList = xAxisNode->data; // Get the pointer for the List

		if (point.Y >= xAxisList->size)
			return NULL;

		Node<T>* yAxisNode = xAxisList->front; // Find Y
		for (int i = 0; i < point.Y; i++) {
			yAxisNode = yAxisNode->getNext();
		}

		return yAxisNode;
	}
};


/*
* Author: Andrew Vu, Brian Macias Garcia
* Changelog:
* 1.Apr.2024 Created
*/

#pragma once
#include "LinkedList.h"
#include "DataTypes.h"
#include "LinkedList2D.h"
#include <iostream>

template <typename T>
class LinkedListMatrix
{	
public:
	LinkedListMatrix(Size<int> dimension) {
		this->dimension = dimension;
		Initialize();
	}

	LinkedListMatrix(int x, int y)
	{
		this->dimension = Size<int>(x, y);
		Initialize();
	}

	T get(Point<int> point)
	{
		return findNode(point)->getData();
	}

	T get(int x, int y)
	{
		return findNode(x, y)->getData();
	}

	void set(Point<int> point, T item)
	{
		findNode(point)->setData(item);
	}

	void set(int x, int y, T item)
	{
		findNode(x, y)->setData(item);
	}

	Size<int> getDimensions()
	{
		return dimension;
	}

	// It just made it easier to do it with in the class
	void printMatrix(T xMarker, T tMarker)
	{
		QuadlyNode<T>* XLine = leftTop;
		QuadlyNode<T>* YLine = leftTop;
		for (int y = 0; y < dimension.Y; y++)
		{
			cout << "|";
			for (int x = 0; x < dimension.X - 1; x++)
			{
				T temp = XLine->getData();
				if (temp == xMarker)
				{
					cout << "X, ";
				}
				else if (temp == tMarker)
				{
					cout << "T, ";
				}
				else
				{
					cout << "-, ";
				}
				XLine = XLine->getNext();
			}
			T temp = XLine->getData();
			if (temp == xMarker)
			{
				cout << "X|" << endl;
			}
			else if (temp == tMarker)
			{
				cout << "T|" << endl;
			}
			else
			{
				cout << "-|" << endl;
			}
			XLine = YLine->getDown();
			YLine = XLine;
		}
	}

	template <typename T>
	friend ostream& operator<<(ostream& out, const LinkedListMatrix<T> matrix);

private:
	QuadlyNode<T>* findNode(Point<int> point)
	{
		if (!dimension.isPointInRange(point))
			return nullptr;

		QuadlyNode<T>* node{ leftTop };
		for (int y = 0; y < point.Y; y++)
			node = node->getDown();

		for (int x = 0; x < point.X; x++)
			node = node->getNext();

		return node;
	}
	QuadlyNode<T>* findNode(int x, int y)
	{
		if (!dimension.isPointInRange(x, y))
			return nullptr;

		QuadlyNode<T>* node{ leftTop };
		for (int _y = 0; _y < y; _y++)
			node = node->getDown();

		for (int _x = 0; _x < x; _x++)
			node = node->getNext();

		return node;
	}
	void Initialize()
	{
		leftTop = new QuadlyNode<T>{ nullptr, nullptr, 0, nullptr, nullptr };
		QuadlyNode<T>* currentItem = leftTop;
		QuadlyNode<T>* currentLine = currentItem;
		QuadlyNode<T>* previousLineNode = nullptr;
		for (int y = 0; y < dimension.Y; y++)
		{
			for (int x = 1; x < dimension.X; x++)
			{
				currentItem->setNext(new QuadlyNode<T>{ nullptr, currentItem, 0, nullptr, nullptr }); // Debug Data Included

				if (y > 0)
				{
					currentItem->setUp(previousLineNode);
					previousLineNode->setDown(currentItem);
					previousLineNode = previousLineNode->getNext();
				}

				currentItem = currentItem->getNext();
			}

			if (y - 1 != dimension.Y)
			{
				previousLineNode = currentLine;
				currentLine = new QuadlyNode<T>{ previousLineNode, nullptr, 0, nullptr, nullptr }; // Create the next line
				currentItem = currentLine;
				previousLineNode->setDown(currentLine);
			}
		}

		rightBottom = currentItem;
	}
	Size<int> dimension;
	QuadlyNode<T>* lastAccess; // idk, it just there look AT ME MENACINGLY!
	QuadlyNode<T>* leftTop;
	QuadlyNode<T>* rightBottom;
};

template <typename T>
ostream& operator<<(ostream& out, const LinkedListMatrix<T> matrix)
{
	QuadlyNode<T>* XLine = matrix.leftTop;
	QuadlyNode<T>* YLine = matrix.leftTop;
	for (int y = 0; y < matrix.dimension.Y; y++)
	{
		out << "[";
		for (int x = 0; x < matrix.dimension.X - 1; x++)
		{
			out << XLine->getData() << ", ";
			XLine = XLine->getNext();
		}
		out << XLine->getData() << "]" << endl;
		XLine = YLine->getDown();
		YLine = XLine;
	}

	return out;
}


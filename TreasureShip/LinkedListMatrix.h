#pragma once
#include "LinkedList2D.h"
#include "DataTypes.h"
#include "LinkedList3D.h"

template <typename T>
class LinkedListMatrix : public LinkedList3D<T>
{	
public:
	LinkedListMatrix(Size<int> size) : LinkedList3D<T>() {

	}
};


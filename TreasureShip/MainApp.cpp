/*
* Author: Andrew Vu, Brian Macias Garcia
* Changelog:
* 1.Apr.2024 Created
*/

#include "LinkedList2D.h"
#include "LinkedListMatrix.h"
#include "DataTypes.h"

bool moveAndCheck(LinkedListMatrix<int>* matrix,int x, int y) {
	if (matrix->get(x, y) == 999) {
		cout << "Found a treasure at the location (" << x << "," << y << ")" << endl;
		cout << "Your ship move to:  (" << x << "," << y << ")" << endl;
		return true;
	}
	else {
		cout << "Couldn't find the treasure, try next time! " << endl;
		cout << "Your ship move to:  (" << x << "," << y << ")" << endl;
		return false;
	}
}


int main() {
	LinkedList<int>* f = new LinkedList<int>();

	for (int e = 0; e < 10; e++) {
		f->append(e << e); //Create 
	}

	LinkedList2D<int>* l = new LinkedList2D<int>();

	l->removeAll(0);

	cout << *f << endl;

	delete f;

	LinkedListMatrix<int>* o = new LinkedListMatrix<int>(Size<int>(5, 5));


	o->set(Point<int>(3, 3), 5);
	LinkedListMatrix<int>* anObj = new LinkedListMatrix<int>(Size<int>(5,5));
	//Treasure location:
	anObj->set(Point<int>(1, 1), 999);
	anObj->set(Point<int>(2, 4), 999);
	anObj->set(Point<int>(3, 1), 999);
	anObj->set(Point<int>(4, 4), 999);
	anObj->set(Point<int>(0, 1), 999);
	//Ship location:
	anObj->set(Point<int>(3, 1), 555);
	cout << "You want to move it! " << endl;
	
	cout << o->get(Point<int>(3, 3)) << endl;
	cout << anObj->get(Point<int>(1, 1));
	cout << anObj->get(Point<int>(2, 4));
	cout << anObj->get(Point<int>(3, 1));
	cout << anObj->get(Point<int>(4, 4));
	cout << anObj->get(Point<int>(0, 1)) << endl;
	cout << *o <<endl;
	cout << *anObj;
}
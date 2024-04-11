/*
* Author: Andrew Vu, Brian Macias Garcia
* Changelog:
* 1.Apr.2024 Created
*/

#include "LinkedList2D.h"
#include "LinkedListMatrix.h"
#include "DataTypes.h"

int main() {
	LinkedList<int>* f = new LinkedList<int>();

	for (int e = 0; e < 10; e++) {
		f->append(e << e);
	}

	LinkedList2D<int>* l = new LinkedList2D<int>();

	l->removeAll(0);

	cout << *f << endl;

	delete f;

	LinkedListMatrix<int>* o = new LinkedListMatrix<int>(Size<int>(10, 10));

	o->set(Point<int>(3, 3), 5);

	cout << o->get(Point<int>(3, 3)) << endl;

	cout << *o;
}
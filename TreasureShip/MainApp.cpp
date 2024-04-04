/*
* Author: Andrew Vu, Brian Macias Garcia
* Changelog:
* 1.Apr.2024 Created
*/

#include "LinkedList3D.h"

int main() {
	LinkedList2D<int>* f = new LinkedList2D<int>();

	for (int e = 0; e < 10; e++) {
		f->append(e << e);
	}

	cout << *f << endl;

	delete f;
}
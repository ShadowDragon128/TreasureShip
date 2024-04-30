/*
* Author: Andrew Vu, Brian Macias Garcia
* Changelog:
* 1.Apr.2024 Created
*/

#include "LinkedList2D.h"
#include "LinkedListMatrix.h"
#include "DataTypes.h"
#include <cstdlib>
#include <ctime>
//Genenrate random X value
int ranX() {
	int xVal = rand() % 5;
	return xVal;
}
//Genenrate random Y value
int ranY() {
	int yVal = rand() % 5;
	return yVal;
}

//Check if we can find the treasure
bool moveAndCheck(LinkedListMatrix<int>* matrix,int x, int y) {
	/*cout << "Call" << endl;
	cout << matrix->get(x, y) << endl;*/
	if (matrix->get(x, y) == 9) {
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
	srand(time(nullptr));
	LinkedList<int>* f = new LinkedList<int>();
	for (int e = 0; e < 10; e++) {
		f->append(e << e); //Create 
	}

	LinkedList2D<int>* l = new LinkedList2D<int>();

	l->removeAll(0);

	cout << *f << endl;

	delete f;

	LinkedListMatrix<int>* o = new LinkedListMatrix<int>(Size<int>(5, 5));


	//o->set(Point<int>(3, 3), 5);
	int x_ColSize = 5;
	int y_RowSize = 5;
	//Create 5x5 matrix
	LinkedListMatrix<int>* anObj = new LinkedListMatrix<int>(Size<int>(x_ColSize, y_RowSize));
	//Treasure location, we assign 9 as the value of the tresure
	cout << "Created 5 random treasures in 5 different locations, go and find them: " << endl;
	int counter = 5;
	for (int k = 0; k < counter; k++) {
		int ranX_val = ranX();
		int ranY_val = ranY();
		while (ranX_val == 3 && ranY_val == 1) {
			ranX_val = ranX();
			ranX_val = ranY();
		}
		cout << "Treasure created at (" << ranX_val << "," << ranY_val << ")" << endl;
		anObj->set(Point<int>(ranX_val, ranY_val), 9);
		//cout << anObj->get(Point<int>(ranX_val, ranY_val)) << endl;
	}
	//Ship location:
	cout << "Your ship is currently at (3,1): " << endl;
	Point<int>(3, 1);
	//cout << o->get(Point<int>(3, 3)) << endl;
	/*cout << anObj->get(Point<int>(1, 1));
	cout << anObj->get(Point<int>(2, 4));
	cout << anObj->get(Point<int>(3, 1));
	cout << anObj->get(Point<int>(4, 4));
	cout << anObj->get(Point<int>(0, 1));*/
	cout << *anObj << endl;
	int x, y = 0;
	while (counter != 0) {
		while (true) {
			try {
				cout << "Enter x value (0-4): ";
				if (!(cin >> x)) {
					throw runtime_error("Invalid input. Please enter an integer.");
				}
				if (x < 0 || x > 4) {
					throw out_of_range("Value of x must be between 0 and 4.");
				}

				cout << "Enter y value (0-4): ";
				if (!(cin >> y)) {
					throw runtime_error("Invalid input. Please enter an integer.");
				}
				if (y < 0 || y > 4) {
					throw out_of_range("Value of y must be between 0 and 4.");
				}

				//Both x and y are valid
				break; // Exit the loop since we have valid input
			}
			catch (const exception& e) {
				cerr << "Error: " << e.what() << std::endl;
				cin.clear(); // Clear the error flag on cin
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
			}
		}

		//cout << x << ", " << y << endl;
		//4 is the value if we can find a treasure 
		if (moveAndCheck(anObj, x, y) == true) {
			anObj->set(Point<int>(x, y), 4);
			counter--;
		}
		//5 is the value if we can't find a treasure, this is for tracing the location of the ship
		else {
			anObj->set(Point<int>(x, y), 5);
		}
		//Print the matrix after moving
		cout << *anObj;
	}
	cout << "You won!" << endl;
}
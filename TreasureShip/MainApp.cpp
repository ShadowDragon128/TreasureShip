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
#include <Windows.h>
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
		//cout << "Your ship move to:  (" << x << "," << y << ")" << endl;
		return true;
	}
	else {
		//cout << "Your ship move to:  (" << x << "," << y << ")" << endl;
		return false;
	}
}

#undef max() // Windows I tell ya

int main() {
	srand(time(nullptr));
	HANDLE streamOut = GetStdHandle(STD_OUTPUT_HANDLE); // Get console output stream
	CONSOLE_SCREEN_BUFFER_INFO conSBI;
	GetConsoleScreenBufferInfo(streamOut, &conSBI); // Get console info
	SetConsoleTitleW(L"TreasureShip v1"); // set console title

	cout << "TreasureShip\nBy Brian Macias Garcia and Andrew Vu" << endl << endl;

	Size<int> matrixSize{5, 5};
	//Create 5x5 matrix
	LinkedListMatrix<int>* anObj = new LinkedListMatrix<int>(matrixSize);
	//Treasure location, we assign 9 as the value of the tresure
	int counter = 5;
	Point<int>* rngVal = new Point<int>[counter]; // This is how we know if a spot has been used twice

	for (int k = 0; k < counter; k++) {
		int ranX_val = ranX();
		int ranY_val = ranY();
		rngVal[k] = new Point<int>(ranX_val, ranY_val);

		int l = k;
		for (int p = 0; p < k; p++) // Check for duplicates
		{
			if (rngVal[p] == rngVal[k])
			{
				k--; // or else
				break;
			}
		}

		if (l == k) // set the point if no duplicates are found
		{
			anObj->set(rngVal[k], 9);
		}
	}

	//cout << *anObj << endl;
	int x, y = 0;
	while (counter != 0) {
		while (true) {
			try {
				cout << "Enter x value (0-4): ";
				if (!(cin >> x)) {
					MessageBox(NULL, TEXT("Invalid input. Please enter an integer."), TEXT("TreasureShip"), MB_ICONERROR);
					throw runtime_error("Invalid input. Please enter an integer.");
				}
				if (x < 0 || x > 4) {
					MessageBox(NULL, TEXT("Value of x must be between 0 and 4."), TEXT("TreasureShip"), MB_ICONERROR);
					throw out_of_range("Value of x must be between 0 and 4.");
				}

				cout << "Enter y value (0-4): ";
				if (!(cin >> y)) {
					MessageBox(NULL, TEXT("Invalid input. Please enter an integer."), TEXT("TreasureShip"), MB_ICONERROR);
					throw runtime_error("Invalid input. Please enter an integer.");
				}
				if (y < 0 || y > 4) {
					MessageBox(NULL, TEXT("Value of y must be between 0 and 4."), TEXT("TreasureShip"), MB_ICONERROR);
					throw out_of_range("Value of y must be between 0 and 4.");
				}

				//Both x and y are valid
				break; // Exit the loop since we have valid input
			}
			catch (const exception& e) {
				SetConsoleTextAttribute(streamOut, FOREGROUND_RED |
					FOREGROUND_INTENSITY);
				cerr << "Error: " << e.what() << std::endl;
				cin.clear(); // Clear the error flag on cin
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
				SetConsoleTextAttribute(streamOut, conSBI.wAttributes);
			}
		}
		cout << endl;

		//4 is the value if we can find a treasure 
		if (moveAndCheck(anObj, x, y) == true) {
			anObj->set(x, y, 4);
			counter--;
			SetConsoleTextAttribute(streamOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Set text color to green
			cout << "Found a treasure at the location (" << x << "," << y << ")" << endl;
			cout << counter << " more to go!" << endl;
			SetConsoleTextAttribute(streamOut, conSBI.wAttributes); // Restore original color
		}
		//5 is the value if we can't find a treasure, this is for tracing the location of the ship
		else{
			anObj->set(x, y, 5);
			SetConsoleTextAttribute(streamOut, FOREGROUND_RED | FOREGROUND_INTENSITY); // Set text color to red
			cout << "Couldn't find the treasure, try next time! " << endl;
			SetConsoleTextAttribute(streamOut, conSBI.wAttributes); // Restore original color
		}
		//Print the matrix after moving
		anObj->printMatrix(5, 4);
		cout << endl;
	}
	cout << "You won!" << endl;
}
#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

using namespace std;

// Define a node structure for the linked list
struct Node {
	int data;
	Node* next;
};

// Define a class for the 2D Linked List
class MatrixLinkedList {
private:
	Node* columns[5]; // Array to hold the heads of each column
	int shipRow;      // Row position of the ship
	int shipColumn;   // Column position of the ship
	int treasuresFound; // Number of treasures found

public:
	// Constructor to initialize the linked list
	MatrixLinkedList() {
		// Initialize all columns to nullptr
		for (int i = 0; i < 5; ++i)
			columns[i] = nullptr;
		shipRow = 0;    // Ship row position
		shipColumn = 2; // Ship column position
		treasuresFound = 0; // No treasures found initially
	}

	// Function to insert a value at the end of a column
	void insert(int column, int data) {
		Node* newNode = new Node();
		newNode->data = data;
		newNode->next = nullptr;

		// If column is empty, insert as the head
		if (columns[column] == nullptr) {
			columns[column] = newNode;
		}
		else {
			// Otherwise, traverse to the end and insert
			Node* temp = columns[column];
			while (temp->next != nullptr) {
				temp = temp->next;
			}
			temp->next = newNode;
		}
	}

	// Function to display the matrix
	void display() {
		char rowLabel = 'a';
		for (int i = 0; i < 5; ++i) {
			Node* temp = columns[i];
			cout << "[ ";
			for (int j = 0; j < 5; ++j) {
				if (rowLabel - 'a' == shipRow && j == shipColumn) {
					cout << rowLabel << j << "_S"; // Ship
				}
				else {
					bool isTreasure = false;
					while (temp != nullptr) {
						if (temp->data == i * 5 + j + 1) {
							cout << rowLabel << j << "_X"; // Treasure
							isTreasure = true;
							break;
						}
						temp = temp->next;
					}
					if (!isTreasure) {
						cout << rowLabel << j << " "; // Empty space
					}
					temp = columns[i];
				}
				if (j < 4) cout << "| ";
			}
			cout << "]\n";
			++rowLabel;
		}
	}

	// Function to insert treasures at specific locations
	//void insertTreasures() {
	//    // Define predetermined locations for treasures
	//    int treasureLocations[5][2] = {
	//        {0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}
	//    };

	//    // Insert treasures at predetermined locations
	//    for (int i = 0; i < 5; ++i) {
	//        insert(treasureLocations[i][1], treasureLocations[i][0] * 5 + treasureLocations[i][1] + 1);
	//    }
	//}
	// Function to check if the treasure already exists at the given position
	bool checkDuplicateTreasure(int treasure) {
		for (int i = 0; i < 5; ++i) {
			Node* temp = columns[i];
			while (temp != nullptr) {
				if (temp->data == treasure)
					return true; // Treasure already exists at this position
				temp = temp->next;
			}
		}
		return false; // No duplicate treasure found
	}


	void insertTreasures() {
		srand(time(0)); // Seed for random number generation
		// Insert 5 treasures at random locations
		for (int i = 0; i < 5; ++i) {
			int column, row;
			do {
				column = rand() % 5; // Random column index (0 to 4)
				row = rand() % 5;    // Random row index (0 to 4)
			} while (columns[column] != nullptr && checkDuplicateTreasure(row * 5 + column + 1));
			insert(column, row * 5 + column + 1); // Insert treasure at (row, column)
		}
	}

	// Function to move the ship to a specific location
	void moveShip(char row, int column) {
		int newRow = row - 'a';
		if (newRow >= 0 && newRow < 5 && column >= 0 && column < 5) {
			shipRow = newRow;
			shipColumn = column;
		}
	}

	// Function to check if the ship has found a treasure
	bool checkTreasureFound() {
		Node* temp = columns[shipColumn];
		while (temp != nullptr) {
			if (temp->data == shipRow * 5 + shipColumn + 1) {
				temp->data = -1; // Mark treasure as found (-1)
				treasuresFound++; // Increment treasures found count
				return true;
			}
			temp = temp->next;
		}
		return false; // No treasure found at the ship's position
	}

	// Function to check if all treasures are found
	bool allTreasuresFound() {
		return treasuresFound == 5;
	}

	// Function to get the ship's row position
	int getShipRow() {
		return shipRow;
	}

	// Function to get the ship's column position
	int getShipColumn() {
		return shipColumn;
	}
};

int main() {
	MatrixLinkedList matrix;

	// Inserting treasures at predetermined locations
	matrix.insertTreasures();
	matrix.insertTreasures();
	matrix.insertTreasures();
	matrix.insertTreasures();
	matrix.insertTreasures();

	// Display the matrix with treasures and ship
	cout << "Initial Matrix with Treasures and Ship:\n";
	matrix.display();
	cout << endl;

	// Game loop
	while (!matrix.allTreasuresFound()) {
		// Display the matrix with ship and treasures
		cout << "Ship's Position: (" << static_cast<char>('a' + matrix.getShipRow()) << matrix.getShipColumn() << ")\n";
		matrix.display();
		cout << endl;

		// Ask the user for a move
		char row;
		int column;
		cout << "Enter row (a-e) and column (0-4) to move the ship: ";
		cin >> row >> column;

		// Move the ship
		matrix.moveShip(row, column);

		// Check if the ship has found a treasure
		if (matrix.checkTreasureFound()) {
			cout << "Treasure found!\n";
		}
	}

	// Display the final matrix
	cout << "All treasures found! Final matrix:\n";
	matrix.display();

	return 0;
}

/*
* Author: Andrew Vu, Brian Macias Garcia
* Changelog:
* 1.Apr.2024 Created
* 25 Apr. 2024 Copied over
*/

#pragma once
namespace DataTypes
{
	typedef unsigned long long ulong;
	typedef unsigned int uint;
	typedef unsigned short ushort;
	typedef unsigned char byte;
	typedef signed char sbyte;

	template <typename T>
	class Node {
	public:
		Node(T data, Node* front) {
			this->data = data;
			this->next = front;
		}
		~Node() {
		}

		T getData() { return data; }

		Node* getNext() { return next; }

		void setData(T d) { data = d; }

		void setNext(Node* n) { next = n; }

	protected:
		T data;
		Node<T>* next;
	};

	template <typename T>
	class DoublyNode : protected Node<T> {
	public:
		DoublyNode(DoublyNode<T>* previous, T data, DoublyNode<T>* next) : Node<T>(data, next) {
			this->previous = previous;
		}

		T getData() { return this->data; }

		DoublyNode<T>* getNext() { return static_cast<DoublyNode<T>*>(this->next); } // Sussy
		DoublyNode<T>* getPrevious() { return this->previous; }

		void setData(T d) { this->data = d; }

		void setNext(DoublyNode<T>* n) { this->next = n; }
		void setPrevious(DoublyNode<T>* p) {this->previous = p; }
	protected:
		DoublyNode<T>* previous;
	};

	template <typename T>
	class QuadlyNode : protected DoublyNode<T> {
	public:
		QuadlyNode(QuadlyNode<T>* up, QuadlyNode<T>* back, T data, QuadlyNode<T>* next, QuadlyNode<T>* down) : DoublyNode<T>(back, data, next)
		{
			this->up = up;
			this->down = down;
		}

		T getData() { return this->data; }

		QuadlyNode<T>* getNext() { return static_cast<QuadlyNode<T>*>(this->next); } // Sussy
		QuadlyNode<T>* getPrevious() { return static_cast<QuadlyNode<T>*>(this->previous); } // Trust me =V
		QuadlyNode<T>* getUp() { return this->up; }
		QuadlyNode<T>* getDown() { return this->down; }

		void setData(T d) { this->data = d; }

		void setNext(QuadlyNode<T>* n) { this->next = n; }
		void setPrevious(QuadlyNode<T>* p) { this->previous = p; }
		void setUp(QuadlyNode<T>* u) { this->up = u; }
		void setDown(QuadlyNode<T>* d) { this->down = d; }

	protected:
		QuadlyNode<T>* up;
		QuadlyNode<T>* down;
	};

	template <typename T>
	struct Point
	{
	public:
		Point() {}

		Point(T X, T Y) {
			this->X = X;
			this->Y = Y;
		}

		bool isAxisInRange(Point<T> rect)
		{
			return X >= rect.X && Y >= rect.Y;
		}

		Point& operator=(const Point* other)
		{
			this->X = other->X;
			this->Y = other->Y;
			return *this;
		}

		friend bool operator!=(const Point<T>& one, const Point<T>& two)
		{
			return !(one.X == two.X && one.Y == two.Y);
		}

		friend bool operator==(const Point<T>& one, const Point<T>& two)
		{
			return one.X == two.X && one.Y == two.Y;
		}

		T X, Y;
	};

	template <typename T>
	struct Size
	{
		Size() {}

		Size(T X, T Y) {
			this->X = X;
			this->Y = Y;
		}

		T getArea() {
			return X * Y;
		}

		bool isSmaller(Size<T> rect)
		{
			return getArea() > rect.getArea();
		}

		bool isPointInRange(Point<T> point) // Why not?
		{
			return X >= point.X && Y >= point.Y;
		}

		bool isPointInRange(int x, int y) // Why not?
		{
			return X >= x && Y >= y;
		}

		T X, Y;
	};
};


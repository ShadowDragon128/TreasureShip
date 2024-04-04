/*
* Author: Andrew Vu, Brian Macias Garcia
* Changelog:
* 1.Apr.2024 Created
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
	class DoublyNode : public Node<T> {
	public:
		DoublyNode(DoublyNode<T>* previous, T data, DoublyNode<T>* next) : Node<T>(data, next) {
			this->previous = previous;
		}

		T getData() { return this->data; }
		DoublyNode<T>* getNext() { return static_cast<DoublyNode<T>*>(this->next); } // Sussy
		void setData(T d) { this->data = d; }
		void setNext(DoublyNode<T>* n) { this->next = n; }
		DoublyNode<T>* getPrevious() { return previous; }
		void setPrevious(DoublyNode<T>* p) { previous = p; }
	protected:
		DoublyNode<T>* previous;
	};

	template <typename T>
	struct Size
	{
	public:
		Size(T X, T Y) {	
			this->X = X;
			this->Y = Y;
		}
		T X;
		T Y;
	};

	template <typename T>
	struct Point : public Size<T>
	{
		Point(T X, T Y) : Size<T>(X, Y) {}
	};
};


/*
* Author: Andrew Vu, Brian Macias Garcia
* Changelog:
* 1.Apr.2024 Created
*/

#pragma once
namespace DataTypes
{
	template <typename T>
	class Node {
	public:
		Node(T data, Node* front) {
			this->data = data;
			this->front = front;
		}
		~Node() {

		}

		T getData() { return data; }
		Node* getNext() { return front; }
		void setData(T d) { data = d; }
		void setNext(Node* n) { front = n; }

	protected:
		T data;
		Node<T>* front;
	};

	template <typename T>
	class DoublyNode : public Node<T> {
	public:
		DoublyNode(Node<T>* back, T data, Node<T>* front) : Node<T>(data, front) {
			this->back = back;
		}
	protected:
		Node<T>* back;
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


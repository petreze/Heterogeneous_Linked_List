#pragma once
#include "Container.h"
#include <iostream>


template <typename T>
class Stack : public Container<T>
{
private:

	template <typename T>
	struct StackNode
	{
		T data;
		StackNode<T> *next;

		StackNode(const T& _data, StackNode* _next = nullptr) : data(_data), next(_next) {}
	};


	StackNode<T>* top;
	size_t size;


	void copy(const Stack<T>& other)
	{
		if (other.top == nullptr)
		{
			this->top = nullptr;
			this->size = 0;
			return;
		}

		this->top = new StackNode<T>(other.top->data, other.top->next);

		StackNode<T>* temp1 = this->top;
		StackNode<T>* temp2 = other.top;

		while (temp2)
		{
			temp1->next = new StackNode<T>(temp2->next->data, temp2->next->next);
			temp2 = temp2->next;
			temp1 = temp1->next;
		}
		this->size = other.size;
	}

	void erase()
	{
		while (!isEmpty())
		{
			this->remove();
		}
	}

public:

	Stack()
	{
		this->top = nullptr;
		this->size = 0;
	}

	Stack(const Stack<T>& other)
	{
		copy(other);
	}

	Stack<T>& operator=(const Stack& other)
	{
		if (this != other)
		{
			erase();
			copy(other);
		}
		return *this;
	}

	~Stack()
	{
		erase();
	}

	bool isEmpty()
	{
		return this->top == nullptr;
	}

	void add(const T& data)
	{
		StackNode<T>* toAdd = new StackNode<T>(data, this->top);

		if (toAdd)
		{
			this->top = toAdd;
			this->size++;
		}
	}

	void remove()
	{
		if (!isEmpty())
		{
			StackNode<T>* toRemove = top;
			top = top->next;
			delete toRemove;
			size--;
		}
	}

	T& getElement()
	{
		if (!isEmpty())
		{
			return this->top->data;
		}
		throw "Empty stack";
	}

	size_t getSize()
	{
		return this->size;
	}

	std::string getType()
	{
		return "stack";
	}

	void print()
	{
		if (isEmpty())
		{
			std::cout << "Empty stack" << std::endl;
		}
		else
		{
			StackNode<T> *current = top;
			while (current)
			{
				std::cout << current->data << " -> ";
				current = current->next;
			}
		}
	}

	bool member(const T& x)
	{
		StackNode<T>* temp = top;

		while (temp)
		{
			if (temp->data == x)
			{
				return true;
			}
			temp = temp->next;
		}
		return false;
	}

	void sort()
	{
		if (!isEmpty())
		{
			int counter = size;

			while (counter)
			{
				bool flagIsSorted = false;
				StackNode<T> *current = top;
				StackNode<T> *previous = current->next;

				while (previous != nullptr)
				{
					if (current->data > previous->data)
					{
						T tempData = current->data;
						current->data = previous->data;
						previous->data = tempData;

						flagIsSorted = true;
					}
					current = current->next;
					previous = previous->next;
				}
				counter--;

				if (!flagIsSorted)
				{
					break;
				}
			}
		}
	}

	bool findOnCondition(bool(*find)(const T&))
	{
		if (isEmpty())
			return false;

		StackNode<T>* current = this->top;

		while (current)
		{
			if (find(current->data))
				return true;

			current = current->next;
		}
		return false;
	}
};
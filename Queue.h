#pragma once
#include "Container.h"
#include <iostream>


template <typename T>
class Queue : public Container<T>
{
private:

	template <typename T>
	struct QueueNode
	{
		T data;
		QueueNode<T>* next;

		QueueNode(const T& _data, QueueNode* _next = nullptr) : data(_data), next(_next) {}
	};


	QueueNode<T>* front;
	QueueNode<T>* last;
	size_t size;


	void copy(const Queue<T>& other)
	{
		QueueNode<T>* temp = other.front;

		while (temp)
		{
			add(temp->data);
			temp = temp->next;
		}
	}

	void erase()
	{
		while (!isEmpty())
		{
			remove();
		}
	}

public:

	Queue()
	{
		this->front = nullptr;
		this->last = nullptr;
		this->size = 0;
	}

	Queue(const Queue& other)
	{
		copy(other);
	}

	Queue<T>& operator=(const Queue& other)
	{
		if (this != other)
		{
			erase();
			copy(other);
		}
		return *this;
	}

	~Queue()
	{
		erase();
	}

	void add(const T& data)
	{
		QueueNode<T>* toAdd = new QueueNode<T>(data);

		if (isEmpty())
		{
			this->front = toAdd;
			this->last = toAdd;
		}
		else
		{
			this->last->next = toAdd;
			this->last = toAdd;
		}
		size++;
	}

	void remove()
	{
		if (!isEmpty())
		{
			QueueNode<T>* toRemove = front;
			front = front->next;
			delete toRemove;
			size--;
		}
	}

	bool isEmpty()
	{
		return front == nullptr;
	}

	T& getElement()
	{
		if (this->front != nullptr)
		{
			return this->front->data;
		}
		throw "Empty queue";
	}

	T& back()
	{
		if (this->last != nullptr)
		{
			return this->last->data;
		}
		throw "Empty queue";
	}

	size_t getSize()
	{
		return this->size;
	}

	std::string getType()
	{
		return "queue";
	}

	void print()
	{
		if (isEmpty())
		{
			std::cout << "Empty queue" << std::endl;
		}
		else
		{
			QueueNode<T>* temp = front;

			while (temp)
			{
				std::cout << temp->data << " -> ";
				temp = temp->next;
			}
		}
	}

	bool member(const T& x)
	{
		QueueNode<T>* temp = front;

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
				QueueNode<T> *current = front;
				QueueNode<T> *previous = current->next;

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

				if (!flagIsSorted)  // if the flag is still false then not a single swap was made 
				{
					break;          // which means that the queue is already sorted and the loop can be exited
				}
			}
		}
	}

	bool findOnCondition(bool(*find)(const T&))
	{
		if (isEmpty())
			return false;

		QueueNode<T>* current = this->front;

		while (current)
		{
			if (find(current->data))
				return true;

			current = current->next;
		}
		return false;
	}
};
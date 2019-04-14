#pragma once
#include "Container.h"
#include <iostream>


template <typename T>
class DoubleLList : public Container<T>
{
private:

	template<typename T>
	struct DLLNode
	{
		T data;
		DLLNode<T>* next;
		DLLNode<T>* prev;

		DLLNode(const T& _data, DLLNode* _prev = nullptr, DLLNode* _next = nullptr) : data(_data), prev(_prev), next(_next) {}
	};


	DLLNode<T>* start;
	DLLNode<T>* end;
	size_t size;


	void copy(const DoubleLList& other)
	{
		DLLNode<T>* temp = other.start;

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

	DoubleLList()
	{
		start = nullptr;
		end = nullptr;
		size = 0;
	}

	DoubleLList(const DoubleLList& other)
	{
		copy(other);
	}

	DoubleLList<T>&	operator=(const DoubleLList& other)
	{
		if (this != other)
		{
			erase();
			copy(other);
		}
		return *this;
	}

	~DoubleLList()
	{
		erase();
	}

	void addToFront(const T& data)
	{
		DLLNode<T>* temp = new DLLNode<T>(data);

		if (isEmpty())
		{
			start = end = temp;
			temp->prev = nullptr;
			temp->next = nullptr;
		}
		else
		{
			temp->prev = nullptr;
			temp->next = start;
			start = temp;
		}
		size++;
	}

	void add(const T& data)
	{
		DLLNode<T>* temp = new DLLNode<T>(data);

		if (isEmpty())
		{
			start = end = temp;
			temp->prev = nullptr;
			temp->next = nullptr;
		}
		else
		{
			end->next = temp;
			temp->prev = end;
			temp->next = nullptr;
			end = temp;
		}
		size++;
	}

	void remove()
	{
		if (!isEmpty())
		{
			if (getSize() == 1)
			{
				delete start;
				start = nullptr;
			}
			else
			{
				DLLNode<T>* temp = start;
				start = start->next;
				delete temp;
				start->prev = nullptr;
			}

			size--;
		}
	}

	void removeFromBack()
	{
		if (!isEmpty())
		{
			DLLNode<T>* temp = end;
			end = temp->prev;
			delete temp;
			end->next = nullptr;
			size--;
		}
	}

	size_t getSize()
	{
		return this->size;
	}

	std::string getType()
	{
		return "list";
	}

	T& getElement()
	{
		if (this->start != nullptr)
		{
			return this->start->data;
		}
		throw "Empty list";
	}

	bool isEmpty()
	{
		return start == nullptr;
	}

	void print()
	{
		if (isEmpty())
		{
			std::cout << "Empty list" << std::endl;
		}
		else
		{
			DLLNode<T>* temp = start;

			while (temp)
			{
				std::cout << temp->data << " ->";
				temp = temp->next;
			}
		}
	}

	bool member(const T&x)
	{
		DLLNode<T>* temp = this->start;

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
				DLLNode<T> *current = start;
				DLLNode<T> *previous = current->next;

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
					break;			// which means that the list is already sorted and the loop can be exited
				}
			}
		}
	}

	bool findOnCondition(bool(*find)(const T&))
	{
		if (isEmpty())
			return false;

		DLLNode<T>* current = this->start;

		while (current)
		{
			if (find(current->data))
				return true;

			current = current->next;
		}
		return false;
	}
};
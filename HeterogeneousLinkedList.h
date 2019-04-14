#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Stack.h"
#include "Queue.h"
#include "DoubleLinkedList.h"


template<typename T>
struct Element
{
	Container<T>* con;
	Element<T>* next;

	Element(Container<T>* _con, Element<T>* _next) : con(_con), next(_next) {}
};


template<class T>
class HeterogeneousLList
{
	Element<T>* start;
	size_t size;

public:
	
	HeterogeneousLList()
	{
		start = nullptr;
		size = 0;
	}

	HeterogeneousLList(std::ifstream& file, int n)
	{
		while (n)
		{
			std::string str;
			std::stringstream ss;
			getline(file, str);
			ss << str;

			std::string type;
			ss >> type;
			int number;

			if (type == "stack")
			{
				Stack<T>* myStack = new Stack<int>;

				while (ss >> number)
				{
					myStack->add(number);
				}
				pushCont(myStack);
			}
			else if (type == "queue")
			{
				Queue<T>* myQueue = new Queue<int>;

				while (ss >> number)
				{
					myQueue->add(number);
				}
				pushCont(myQueue);
			}
			else if (type == "list")
			{
				DoubleLList<T>* myDList = new DoubleLList<int>;

				while (ss >> number)
				{
					myDList->add(number);
				}
				pushCont(myDList);
			}
			n--;
		}
		file.close();
	}

	~HeterogeneousLList()
	{
		eraseCont();
	}

	void pushCont(Container<T>* container)
	{
		Element<T>* temp = new Element<T>(container, nullptr);

		if (!start)
		{
			start = temp;
		}
		else
		{
			Element<T>* current = this->start;

			while (current)
			{
				if (!current->next)
				{
					current->next = temp;
					break;
				}

				current = current->next;
			}
		}

		size++;
	}

	void eraseCont()
	{
		if (!isListEmpty())
		{
			Element<T>* temp = start->next;
			delete start;
			start = temp;
			size--;
		}
	}

	bool isListEmpty()
	{
		return start == nullptr;
	}

	bool isInTheList(const T& x)
	{
		Element<T>* current = this->start;

		while (current)
		{
			if (current->con->member(x))
			{
				return true;
			}
			current = current->next;
		}
		return false;
	}

	void loadBalancing(const T& x)
	{
		Element<T>* minSize = this->start;
		Element<T>* current = this->start;

		while (current)
		{
			if (minSize->con->getSize() > current->con->getSize())
			{
				minSize = current;
			}
			current = current->next;
		}
		minSize->con->add(x);
	}

	void removeOnCondition(bool(*remove)(const T&))
	{
		if (!isListEmpty())
		{
			Element<T>* current = this->start;

			while (current)
			{
				if (current->con->getType() == "stack")
				{
					Stack<T>* stack = new Stack<int>;

					while (!current->con->isEmpty())
					{
						if (!remove(current->con->getElement()))			// Ако елементът НЕ отговаря на условието го добавяме в стека.
						{
							stack->add(current->con->getElement());
						}
						current->con->remove();						// Изпразваме контейнера.
					}
					while (!stack->isEmpty())
					{
						current->con->add(stack->getElement());		// Добавяме всички елементи от стека във вече празния контейнер.
						stack->remove();							// (така изтриваме елементите, които отговарят на условието)
					}
				}
				else if (current->con->getType() == "queue")
				{
					Queue<T>* queue = new Queue<int>;
					while (!current->con->isEmpty())
					{
						if (!remove(current->con->getElement()))
						{
							queue->add(current->con->getElement());
						}
						current->con->remove();
					}
					while (!queue->isEmpty())
					{
						current->con->add(queue->getElement());
						queue->remove();
					}
				}
				else if (current->con->getType() == "list")
				{
					DoubleLList<T>* dllist = new DoubleLList<int>;
					while (!current->con->isEmpty())
					{
						if (!remove(current->con->getElement()))
						{
							dllist->add(current->con->getElement());
						}
						current->con->remove();
					}
					while (!dllist->isEmpty())
					{
						current->con->add(dllist->getElement());
						dllist->remove();
					}
				}
				current = current->next;
			}
		}
	}

	void sortList()
	{
		if (!isListEmpty())
		{
			Element<T>* current = this->start;

			while (current)
			{
				current->con->sort();
				current = current->next;
			}
		}
	}

	void printList()
	{
		if (!isListEmpty())
		{
			Element<T>* current = this->start;
			int numberCont = 1;

			while (current)
			{
				std::cout << "Container number " << numberCont << ":" << std::endl;
				current->con->print();
				std::cout << std::endl;
				current = current->next;
				numberCont++;
			}
		}
	}

	void writing(std::ofstream& file)
	{
		if (!isListEmpty())
		{
			Element<T>* current = this->start;

			while (current)
			{
				file << current->con->getType() << " ";

				while (!current->con->isEmpty())
				{
					file << current->con->getElement() << " ";
					current->con->remove();
				}
				file << std::endl;
				current = current->next;
			}
			file.close();
		}
	}
};
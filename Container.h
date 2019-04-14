#pragma once
#include <string>


template <typename T>
class Container
{
public:

	virtual bool member(const T&) = 0;
	virtual void add(const T&) = 0;
	virtual void remove() = 0;
	virtual bool findOnCondition(bool(*find)(const T&)) = 0;
	virtual bool isEmpty() = 0;
	virtual void print() = 0;
	virtual size_t getSize() = 0;
	virtual std::string getType() = 0;
	virtual T& getElement() = 0;
	virtual void sort() = 0;
};

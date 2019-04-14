#include <iostream>
#include <fstream>
#include "HeterogeneousLinkedList.h"
#include "Container.h"
#include "Queue.h"
#include "Stack.h"
#include "DoubleLinkedList.h"


template<typename T>
bool isDividedBy3(const T& x)
{
	return x % 3 == 0;
}

template <typename T>
bool smallerThan10(const T& x)
{
	return x < 10;
}

int main()
{
	int n;
	std::cout << "Please enter the number of the containers: ";
	std::cin >> n;
	std::ifstream input("reading.txt");
	HeterogeneousLList<int> h(input, n);
	std::cout << h.isInTheList(5) << std::endl;
	std::cout << h.isInTheList(13) << std::endl;
	std::cout << h.isInTheList(0) << std::endl;
	std::cout << h.isInTheList(53) << std::endl;
	h.loadBalancing(7);
	h.sortList();
	h.printList();

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	h.removeOnCondition(smallerThan10);
	h.printList();
	std::ofstream output("writing.txt");
	h.writing(output);

	system("pause");
	return 0;
}


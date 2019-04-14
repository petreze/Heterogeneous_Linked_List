#pragma once
#include "Container.h"


template <typename T>
class BSTree : public Container<T>
{
private:

	template <typename T>
	struct BSTNode
	{
		T data;
		BSTNode<T>* left;
		BSTNode<T>* right;

		BSTNode(const T& _data, BSTNode<T>* _left = nullptr, BSTNode<T>* _right = nullptr) : data(_data), left(_left), right(_right) {}
	};


	BSTNode<T>* root;
	size_t size;


	void init()
	{
		this->root = nullptr;
		this->size = 0;
	}

	BSTNode<T>* copyHelper(BSTNode<T>* node)
	{
		if (node = nullptr)
		{
			return nullptr;
		}
		return new BSTNode<T>(node->data, 
			copyHelper(node->left), 
			copyHelper(node->right));
	}

	void copy(const BSTree<T>& other)
	{
		this->size = other.size;
		this->root = copyHelper(other.root);
	}

	void deleteSubTree(BSTNode<T>* node)
	{
		if (node == nullptr)
		{
			return;
		}
		deleteSubTree(node->left);
		deleteSubTree(node->right);
		delete node;
		
		size = 0;
	}

	void erase()
	{
		deleteSubTree(this->root);
	}

	void addHelper(const T& x, BSTNode<T>*& root)
	{
		if (root == nullptr)
		{
			root = new BSTNode<T>(x, nullptr, nullptr);
			size++;
		}
		else if (x > root->data)
		{
			addHelper(x, root->right);
		}
		else if (x < root->data)
		{
			addHelper(x, root->left);
		}
		return;
	}

	void removeHelper(BSTNode<T>*& root)
	{
		BSTNode<T>* temp = nullptr;

		if (root)
		{
			while (root->left->left != nullptr)
				root = root->left;
			// now we are on the smallest element
			if (root->left->right != nullptr)				// but we still have to check if it has a right children
			{												// if it has we do the connections with the current root
				temp = root->left;
				root->left = root->left->right;
				delete temp;
			}
			else											// if the minimum doesn't have any children, we just delete it.
			{
				temp = root->left;
				root->left = nullptr;
				delete temp;
			}
		}
	}

	bool memberHelper(BSTNode<T>* root, const T& x)
	{
		if (root == nullptr)
		{
			return false;
		}
		else if (x == root->data)
		{
			return true;
		}
		else if (x < root->data)
		{
			return findHelper(x, root->left);
		}
		else if (x > root->data)
		{
			return findHelper(x, root->right);
		}
	}

	void printHelper(BSTNode<T>* root)
	{
		if (isEmpty())
		{
			std::cout << "Empty tree" << std::endl;
		}

		if (root->left)
			printHelper(root->left);

		std::cout << root->data << ", ";

		if (root->right)
			printHelper(root->right);
	}

public:

	BSTree()
	{
		init();
	}

	BSTree(const BSTree<T>& other)
	{
		init();
		copy(other);
	}

	BSTree<T>& operator=(const BSTree<T>& other)
	{
		if (this != &other)
		{
			erase();
			init();
			copy(other);
		}

		return *this;
	}

	~BSTree()
	{
		erase();
	}

	void add(const T& data)
	{
		return addHelper(data, this->root);
	}

	void remove()
	{
		removeHelper(this->root);
	}

	T& getElement()
	{
		if (this->root != nullptr)
		{
			return this->root->data;
		}
		throw "Empty tree";
	}

	bool isEmpty()
	{
		return this->root == nullptr;
	}

	size_t getSize()
	{
		return this->size;
	}

	std::string getType()
	{
		return "tree";
	}

	void print()
	{
		printHelper(this->root);
	}

	bool member(const T& x)
	{
		return memberHelper(this->root, x);
	}

	void sort()
	{
		// The structure is Binary Search Tree so it's already sorted.
	}

	bool findOnConditionHelper(BSTNode<T>* root, bool(*find)(const T&))
	{
		if (isEmpty())
		{
			return false;
		}

		BSTNode<T>* current = this->root;

		if (find(current->data))
			return true;

		return findOnConditionHelper(root->left, find) ||
			findOnConditionHelper(root->right, find) || false;
	}

	bool findOnCondition(bool(*find)(const T&))
	{
		return findOnConditionHelper(this->root, find);
	}
};
#pragma once
#include<iostream>


template<class T>
class BiTNode
{
public:
	BiTNode();
	BiTNode(T item, BiTNode<T>* left = NULL, BiTNode<T>* right = NULL);
	~BiTNode() {};
	BiTNode<T>& operator=(const BiTNode<T>& node);
	bool isLeaf();

	T data;
	BiTNode<T>* leftChild;
	BiTNode<T>* rightChild;
};

template<class T>
BiTNode<T>::BiTNode()
{
	leftChild = NULL;
	rightChild = NULL;
}
template<class T>
BiTNode<T>::BiTNode(T item, BiTNode<T>* left, BiTNode<T>* right)
{
	data = item;
	leftChild = left;
	rightChild = right;
}
template<class T>
BiTNode<T>& BiTNode<T>:: operator=(const BiTNode<T>& node)
{
	data = node.data;
	leftChild = node.leftChild;
	rightChild = node.rightChild;
}
template<class T>
bool BiTNode<T>::isLeaf()
{
	if (leftChild == NULL && rightChild == NULL)
		return true;
	else
		return false;
}

template<class T>
class AVLTree
{
public:
	AVLTree();
	AVLTree(const AVLTree<T>&t);
	~AVLTree() { destroy(root); };
	AVLTree& operator=(const AVLTree<T>& t);
	void insert(T item);
	void remove(T item);
	void print();//按顺序输出（中序遍历）
	void printTree();//打印一个横过来的树
	bool search(T item);
private:
	BiTNode<T>* root;
	void insert(BiTNode<T>*& node, T item);
	void remove(BiTNode<T>*& node, T item);
	void print(BiTNode<T>* node);
	void printTree(BiTNode<T>* node, int level);
	int height(BiTNode<T>* node);
	//LL指的是插入的位置在node的左孩子的左边，RR为右孩子的右边，LR为左孩子的右边，RL为右孩子的左边
	void LL(BiTNode<T>*& node);//从左向右旋(右旋)
	void RR(BiTNode<T>*& node);//从右向左旋(左旋)
	void LR(BiTNode<T>*& node);//先对左孩子左旋，而后对node右旋
	void RL(BiTNode<T>*& node);//先对右孩子右旋，而后对node左旋，解决一些情况，eg 7(右为)10(左为)9，直接RR没用，用RR/RL与树的结构有关
	void destroy(BiTNode<T>* node);
	void Copy(BiTNode<T>*& r, BiTNode<T>* t);//树t拷贝给树r
};

template<class T>
AVLTree<T>::AVLTree()
{
	root = NULL;
}
template<class T>
AVLTree<T>::AVLTree(const AVLTree<T>& t)
{
	root = NULL;
	Copy(root, t.root);
}
template<class T>
void AVLTree<T>::Copy(BiTNode<T>*& r, BiTNode<T>* t)
{
	BiTNode<T>* ptr = t;
	if (ptr == NULL)
	{
		return;
	}
	r = new BiTNode<T>(ptr->data);
	Copy(r->leftChild, ptr->leftChild);
	Copy(r->rightChild, ptr->rightChild);
}
template<class T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree<T>& t)
{
	if (this == &t)
		return *this;
	destroy(root);
	Copy(root, t.root);
	return *this;
}
template<class T>
void AVLTree<T>::insert(T item)
{
	if (search(item))
		return;
	insert(root, item);
}
template<class T>
void AVLTree<T>::insert(BiTNode<T>*& node, T item)
{
	if (node == NULL)
	{
		node = new BiTNode<T>(item);
		return;
	}
	if (item < node->data)
	{
		insert(node->leftChild, item);
		if (height(node->leftChild) - height(node->rightChild) == 2)
		{
			if (item < node->leftChild->data)
				LL(node);
			else
				LR(node);
		}
	}
	else if (item > node->data)
	{
		insert(node->rightChild, item);
		if (height(node->rightChild) - height(node->leftChild) == 2)
		{
			if (item > node->rightChild->data)
				RR(node);
			else
				RL(node);
		}
	}
}
template<class T>
void AVLTree<T>::remove(T item)
{
	if (!search(item))
		return;
	remove(root, item);
}
template<class T>
void AVLTree<T>::remove(BiTNode<T>*& node, T item)
{
	if (node == NULL)
		return;
	if (item < node->data)
	{
		remove(node->leftChild, item);
		if (height(node->rightChild) - height(node->leftChild) == 2)
		{
			if (height(node->rightChild->leftChild) > height(node->rightChild->rightChild))
				RL(node);
			else
				RR(node);
		}
	}
	else if (item > node->data)
	{
		remove(node->rightChild, item);
		if (height(node->leftChild) - height(node->rightChild) == 2)
		{
			if (height(node->leftChild->rightChild) > height(node->leftChild->leftChild))
				LR(node);
			else
				LL(node);
		}
	}
	else
	{
		if (node->leftChild != NULL && node->rightChild != NULL)
		{
			BiTNode<T>* temp = node->rightChild;
			while (temp->leftChild != NULL)
				temp = temp->leftChild;
			node->data = temp->data;
			remove(node->rightChild, temp->data);
			if (height(node->leftChild) - height(node->rightChild) == 2)
			{
				if (height(node->leftChild->rightChild) > height(node->leftChild->leftChild))
					LR(node);
				else
					LL(node);
			}
		}
		else
		{
			BiTNode<T>* temp = node;
			node = (node->leftChild != NULL) ? node->leftChild : node->rightChild;
			delete temp;
		}
	}
}
template<class T>
void AVLTree<T>::print()
{
	print(root);
}
template<class T>
void AVLTree<T>::print(BiTNode<T>* node)
{
	if (node == NULL)
		return;
	print(node->leftChild);
	std::cout << node->data << " ";
	print(node->rightChild);
}
template<class T>
void AVLTree<T>::printTree()
{
	printTree(root, 0);
}
template<class T>
void AVLTree<T>::printTree(BiTNode<T>* node, int level)
{
	if (node == NULL)
		return;
	printTree(node->rightChild, level + 1);
	for (int i = 0; i < level; i++)
		std::cout << "   ";
	std::cout << node->data << std::endl;
	printTree(node->leftChild, level + 1);
}
template<class T>
int AVLTree<T>::height(BiTNode<T>* node)
{
	if (node == NULL)
		return 0;
	int leftHeight = height(node->leftChild);
	int rightHeight = height(node->rightChild);
	return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}
template<class T>
void AVLTree<T>::LL(BiTNode<T>*& node)//从左向右旋
{
	BiTNode<T>* temp = node->leftChild;
	node->leftChild = temp->rightChild;
	temp->rightChild = node;
	node = temp;
}
template<class T>
void AVLTree<T>::RR(BiTNode<T>*& node)//从右向左旋
{
	BiTNode<T>* temp = node->rightChild;
	node->rightChild = temp->leftChild;
	temp->leftChild = node;
	node = temp;
}
template<class T>
void AVLTree<T>::LR(BiTNode<T>*& node)
{
	RR(node->leftChild);
	LL(node);
}
template<class T>
void AVLTree<T>::RL(BiTNode<T>*& node)
{
	LL(node->rightChild);
	RR(node);
}
template<class T>
void AVLTree<T>::destroy(BiTNode<T>* node)
{
	if (node == NULL)
		return;
	destroy(node->leftChild);
	destroy(node->rightChild);
	delete node;
}
template<class T>
bool AVLTree<T>::search(T item)
{
	BiTNode<T>* p = this->root;
	while (p != NULL)
	{
		if (p->data == item)
			return true;
		else if (p->data > item)
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	return false;
}

//int main()
//{
//	AVLTree<int> tree;
//	tree.insert(3);
//	tree.insert(2);
//	tree.insert(1);
//	tree.insert(4);
//	tree.insert(5);
//	tree.insert(6);
//	tree.insert(7);
//	tree.insert(10);
//	tree.insert(9);
//	tree.insert(8);
//	tree.print();
//	std::cout << std::endl;
//	tree.printTree();
//	std::cout << std::endl;
//	tree.remove(5);
//	tree.print();
//	std::cout << std::endl;
//	tree.printTree();
//	std::cout << std::endl;
//	tree.remove(3);
//	tree.print();
//	std::cout << std::endl;
//	tree.printTree();
//	std::cout << std::endl;
//	tree.remove(7);
//	tree.print();
//	std::cout << std::endl;
//	tree.printTree();
//	std::cout << std::endl;
//	tree.remove(2);
//	tree.print();
//	std::cout << std::endl;
//	tree.printTree();
//	std::cout << std::endl;
//	tree.remove(4);
//	tree.print();
//	std::cout << std::endl;
//	tree.printTree();
//	std::cout << std::endl;
//	tree.remove(6);
//	tree.print();
//	std::cout << std::endl;
//	tree.printTree();
//	std::cout << std::endl;
//	tree.remove(8);
//	tree.print();
//	std::cout << std::endl;
//	tree.printTree();
//	std::cout << std::endl;
//	tree.remove(1);
//	tree.print();
//	std::cout << std::endl;
//	tree.printTree();
//	std::cout << std::endl;
//	tree.remove(9);
//	tree.print();
//	std::cout << std::endl;
//	tree.printTree();
//	std::cout << std::endl;
//	return 0;
//}
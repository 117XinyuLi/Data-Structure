#pragma once
#include"BinaryTree.hpp"


template<class T>
class BinarySearchTree :public BinaryTree<T>
{
public:
	BinarySearchTree();
	BinarySearchTree(BinaryTreeNode<T>* root);
	BinarySearchTree(const BinarySearchTree<T>& t);
	~BinarySearchTree();
	BinarySearchTree<T>& operator=(const BinarySearchTree<T>& t);
	
	void createTree(T end);//end表示输入结束，而后直接创建查找树
	void createTree(std::vector<T>  data,T end);
	void createTree(const T& data, BinaryTreeNode<T>* leftTree, BinaryTreeNode<T>* rightTree);
	void createTreeByLevel(T flag, T end);//对输入的数据直接形成查找树,不按层序构建树
	int getHeight() const;
	int getSize() const;
	bool isEmpty() const;
	BinaryTreeNode<T>* getRoot() const;
	BinaryTreeNode<T>* Parent(BinaryTreeNode<T>* current);
	BinaryTreeNode<T>* LeftChild(BinaryTreeNode<T>* current);
	BinaryTreeNode<T>* RightChild(BinaryTreeNode<T>* current);
	BinaryTreeNode<T>* LeftSibling(BinaryTreeNode<T>* current);
	BinaryTreeNode<T>* RightSibling(BinaryTreeNode<T>* current);
	void preOrder();
	void inOrder();
	void postOrder();
	void levelOrder();
	void preOrderNonRecursive() const;
	void postOrderNonRecursive() const;
	void inOrderNonRecursive() const;
	
	bool search(T item);
	void insert(T item);
	void remove(T item);
	void destroy();
	
	//root继承于BinaryTree使用时用this->root,或加父类作用域
	
};

template<class T>
BinarySearchTree<T>::BinarySearchTree()
{
	this->root = NULL;
}
template<class T>
BinarySearchTree<T>::BinarySearchTree(BinaryTreeNode<T>* r)
{
	this->root = r;
}
template<class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& t)
{
	this->root = NULL;
	BinaryTree<T>::Copy(this->root, t.root);
}
template<class T>
BinarySearchTree<T>::~BinarySearchTree()
{
	destroy();
}
template<class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T>& t)
{
	if (this != &t)
	{
		destroy();
		this->Copy(this->root, t.root);
	}
	return *this;
	
}
template<class T>
void BinarySearchTree<T>::createTree(T end)
{
	destroy();
	std::vector<T>nodeData;
	T item;
	while (true)
	{
		std::cin >> item;
		if (item == end)
			break;
		nodeData.push_back(item);
	}
	createTree(nodeData, end);
	
}
template<class T>
void BinarySearchTree<T>::createTree(std::vector<T> data, T end)
{
	destroy();
	for (auto i = data.begin(); i !=data.end(); i++)
	{
		insert(*i);
	}
}
template<class T>
void BinarySearchTree<T>::createTreeByLevel(T flag, T end)
{
	destroy();
	std::cout << "对输入的数据直接建立查找二叉树，不按层序构建二叉树，请输入数据：" << std::endl;
	createTree(end);
	
}
template<class T>
void BinarySearchTree<T>::createTree(const T& data, BinaryTreeNode<T>* leftTree, BinaryTreeNode<T>* rightTree)
{
	destroy();
	this->root = new BinaryTreeNode<T>(data, leftTree, rightTree);
}
template<class T>
int BinarySearchTree<T>::getHeight() const
{
	return BinaryTree<T>::getHeight(this->root);
}
template<class T>
int BinarySearchTree<T>::getSize() const
{
	return BinaryTree<T>::getSize(this->root);
}
template<class T>
bool BinarySearchTree<T>::isEmpty() const
{
	return this->root == NULL;
}
template<class T>
BinaryTreeNode<T>* BinarySearchTree<T>::getRoot() const
{
	return this->root;
}
template<class T>
BinaryTreeNode<T>* BinarySearchTree<T>::Parent(BinaryTreeNode<T>* current)
{
	BinaryTreeNode<T>* p = this->root;
	if (current == this->root)
		return NULL;
	if (p == NULL)
		return NULL;
	if (p->leftChild == current || p->rightChild == current)
		return p;
	return Parent(p->leftChild);
	return Parent(p->rightChild);
}
template<class T>
BinaryTreeNode<T>* BinarySearchTree<T>::LeftChild(BinaryTreeNode<T>* current)
{
	if (current == NULL)
		return NULL;
	else
		return current->leftChild;
}
template<class T>
BinaryTreeNode<T>* BinarySearchTree<T>::RightChild(BinaryTreeNode<T>* current)
{
	if (current == NULL)
		return NULL;
	else
		return current->rightChild;
}
template<class T>
BinaryTreeNode<T>* BinarySearchTree<T>::LeftSibling(BinaryTreeNode<T>* current)
{
	BinaryTreeNode<T>* p = Parent(current);
	if (p == NULL)
		return NULL;
	if (p->leftChild == current)
		return p->rightChild;
	else
		return p->leftChild;
}
template<class T>
BinaryTreeNode<T>* BinarySearchTree<T>::RightSibling(BinaryTreeNode<T>* current)
{
	BinaryTreeNode<T>* p = Parent(current);
	if (p == NULL)
		return NULL;
	if (p->rightChild == current)
		return p->leftChild;
	else
		return p->rightChild;
}
template<class T>
static void printNode(BinaryTreeNode<T>*t)
{
	std::cout << t->data << " ";
	
}
template<class T>
void BinarySearchTree<T>::preOrder()
{
	BinaryTree<T>::preOrder(this->root, printNode);
	std::cout << std::endl;
	
}
template<class T>
void BinarySearchTree<T>::inOrder()
{
	BinaryTree<T>::inOrder(this->root, printNode);
	std::cout << std::endl;
}
template<class T>
void BinarySearchTree<T>::postOrder()
{
	BinaryTree<T>::postOrder(this->root, printNode);
	std::cout << std::endl;
}
template<class T>
void BinarySearchTree<T>::preOrderNonRecursive() const
{
	std::stack<BinaryTreeNode<T>*> s;
	BinaryTreeNode<T>* p = this->root;
	while (p != NULL || !s.empty())
	{
		if (p != NULL)
		{
			std::cout << p->data << " ";
			s.push(p);
			p = p->leftChild;
		}
		else
		{
			p = s.top();
			s.pop();
			p = p->rightChild;
		}
	}
	std::cout << std::endl;
}
template<class T>
void BinarySearchTree<T>::inOrderNonRecursive() const
{
	std::stack<BinaryTreeNode<T>*> s;
	BinaryTreeNode<T>* p = this->root;
	while (p != NULL || !s.empty())
	{
		if (p != NULL)
		{
			s.push(p);
			p = p->leftChild;
		}
		else
		{
			p = s.top();
			std::cout << p->data << " ";
			s.pop();
			p = p->rightChild;
		}
	}
	std::cout << std::endl;
}
template<class T>
void BinarySearchTree<T>::postOrderNonRecursive() const
{
	std::stack<BinaryTreeNode<T>*> s;
	BinaryTreeNode<T>* p = this->root;
	BinaryTreeNode<T>* q = NULL;
	while (p != NULL || !s.empty())
	{
		if (p != NULL)
		{
			s.push(p);
			p = p->leftChild;
		}
		else
		{
			p = s.top();
			if (p->rightChild != NULL && p->rightChild != q)
			{
				p = p->rightChild;
				s.push(p);
				p = p->leftChild;
			}
			else
			{
				p = s.top();
				s.pop();
				std::cout << p->data << " ";
				q = p;
				p = NULL;
			}
		}
	}
	std::cout << std::endl;
}
template<class T>
bool BinarySearchTree<T>::search(T item)
{
	BinaryTreeNode<T>* p = this->root;
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
template<class T>
void BinarySearchTree<T>::insert(T item)
{
	BinaryTreeNode<T>* p = this->root;
	BinaryTreeNode<T>* q = NULL;
	if (search(T))
	{
		std::cout << "此元素已在树中" << std::endl;
		return;
	}
	while (p != NULL)
	{
		q = p;
		if (p->data > item)
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	BinaryTreeNode<T>* newNode = new BinaryTreeNode<T>(item);
	if (q == NULL)
		this->root = newNode;
	else if (q->data > item)
		q->leftChild = newNode;
	else
		q->rightChild = newNode;
}
template<class T>
void BinarySearchTree<T>::remove(T item)
{
	BinaryTreeNode<T>* p = this->root;
	if (!p)
	{
		std::cout << "树为空" << std::endl;
		return;
	}
	BinaryTreeNode<T>* q = NULL;
	while (p != NULL && p->data != item)
	{
		q = p;
		if (p->data > item)
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	if (p == NULL)
	{
		std::cout << "无此元素" << std::endl;
		return;
	}
	if (p->leftChild == NULL && p->rightChild == NULL)
	{
		if (q == NULL)
			this->root = NULL;
		else if (q->leftChild == p)
			q->leftChild = NULL;
		else
			q->rightChild = NULL;
		delete p;
	}
	else if (p->leftChild == NULL || p->rightChild == NULL)
	{
		BinaryTreeNode<T>* child = p->leftChild == NULL ? p->rightChild : p->leftChild;
		if (q == NULL)
			this->root = child;
		else if (q->leftChild == p)
			q->leftChild = child;
		else
			q->rightChild = child;
		delete p;
	}
	else
	{
		BinaryTreeNode<T>* s = p->rightChild;
		BinaryTreeNode<T>* r = p;
		while (s->leftChild != NULL)
		{
			r = s;
			s = s->leftChild;
		}
		p->data = s->data;
		if (r == p)
			r->rightChild = s->rightChild;
		else
			r->leftChild = s->rightChild;
		delete s;
	}
}
template<class T>
void BinarySearchTree<T>::destroy()
{
	BinaryTreeNode<T>* p = this->root;
	std::stack<BinaryTreeNode<T>*> s;
	while (p != NULL || !s.empty())
	{
		if (p != NULL)
		{
			s.push(p);
			p = p->leftChild;
		}
		else
		{
			p = s.top();
			s.pop();
			BinaryTreeNode<T>* q = p;
			p = p->rightChild;
			delete q;
		}
	}
	this->root = NULL;
}
template<class T>
void BinarySearchTree<T>::levelOrder()
{
	BinaryTreeNode<T>* p = this->root;
	if (!p)
	{
		return;
	}
	std::queue<BinaryTreeNode<T>*> q;
	q.push(p);
	while (!q.empty())
	{
		
		p = q.front();
		q.pop();
		std::cout << p->data << " ";
		if (p->leftChild != NULL)
			q.push(p->leftChild);
		if (p->rightChild != NULL)
			q.push(p->rightChild);
	}
	std::cout << std::endl;
}



//int main()
//{
//	BinarySearchTree<char> t;
//	t.createTree('#');
//	BinarySearchTree<char>t2 = t;
//	t = t2;
//	
//	t2.preOrderNonRecursive();
//	
//	
//	return 0;
//}
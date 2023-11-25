#pragma once
#include<iostream>
#include<stack>
#include<queue>
#include<string>
#include<vector>

//using namespace std;

template<class T>
class BinaryTreeNode
{
public:
	BinaryTreeNode();
	BinaryTreeNode(T item, BinaryTreeNode<T>* left = NULL, BinaryTreeNode<T>* right = NULL);
	~BinaryTreeNode() {};
	BinaryTreeNode<T>& operator=(const BinaryTreeNode<T>& node);
	bool isLeaf();

	T data;
	BinaryTreeNode<T>* leftChild;
	BinaryTreeNode<T>* rightChild;
};

template<class T>
BinaryTreeNode<T>::BinaryTreeNode()
{
	leftChild = NULL;
	rightChild = NULL;
}
template<class T>
BinaryTreeNode<T>::BinaryTreeNode(T item, BinaryTreeNode<T>* left, BinaryTreeNode<T>* right)
{
	data = item;
	leftChild = left;
	rightChild = right;
}
template<class T>
BinaryTreeNode<T>& BinaryTreeNode<T>:: operator=(const BinaryTreeNode<T>& node)
{
	data = node.data;
	leftChild = node.leftChild;
	rightChild = node.rightChild;
}
template<class T>
bool BinaryTreeNode<T>::isLeaf()
{
	if (leftChild == NULL && rightChild == NULL)
		return true;
	else
		return false;
}

template<class T>
class BinarySearchTree;
template<class T>
class BinaryTree
{
	friend class BinarySearchTree<T>;
public:
	BinaryTree();
	BinaryTree(BinaryTreeNode<T>* root);
	BinaryTree(const BinaryTree<T>& t);
	~BinaryTree();

	virtual void createTree(T flag);//输入flag代表构建空指针,按前序遍历输入
	virtual void createTree(const T& data, BinaryTreeNode<T>* leftTree, BinaryTreeNode<T>* rightTree);
	virtual void createTreeByLevel(T flag,T end);//按层次遍历输入，flag表示空指针，end表示输入结束
	BinaryTree& operator=(const BinaryTree<T>& t);
	
	virtual void destroy();

	virtual int getHeight() const;
	virtual int getSize() const;
	
	virtual bool isEmpty() const;
	virtual BinaryTreeNode<T>* getRoot() const;
	
	virtual BinaryTreeNode<T>* Parent(BinaryTreeNode<T>* current);
	virtual BinaryTreeNode<T>* LeftChild(BinaryTreeNode<T>* current);
	virtual BinaryTreeNode<T>* RightChild(BinaryTreeNode<T>* current);
	virtual BinaryTreeNode<T>* LeftSibling(BinaryTreeNode<T>* current);
	virtual BinaryTreeNode<T>* RightSibling(BinaryTreeNode<T>* current);
	
	virtual void preOrder();
	virtual void inOrder();
	virtual void postOrder();
	virtual void preOrderNonRecursive() const;
	virtual void postOrderNonRecursive() const;
	virtual void inOrderNonRecursive() const;
	virtual void levelOrder(void(*func)(BinaryTreeNode<T>*));

	void Copy(BinaryTreeNode<T>*& r, BinaryTreeNode<T>* t);//树t拷贝给树r
	void visit(BinaryTreeNode<T>* t) { std::cout << t->data << " "; }
	void preOrder(BinaryTreeNode<T>* t, void(*func)(BinaryTreeNode<T>*));
	void inOrder(BinaryTreeNode<T>* t, void(*func)(BinaryTreeNode<T>*));
	void postOrder(BinaryTreeNode<T>* t, void(*func)(BinaryTreeNode<T>*));
	
protected:
	BinaryTreeNode<T>* root;
private:
	
	void createTree(BinaryTreeNode<T>*& t, T flag);
	int getHeight(BinaryTreeNode<T>* t) const;
	int getSize(BinaryTreeNode<T>* t) const;
	void destroy(BinaryTreeNode<T>*& t);

};

template<class T>
BinaryTree<T>::BinaryTree()
{
	root = NULL;
}
template<class T>
BinaryTree<T>::BinaryTree(BinaryTreeNode<T>* r)
{
	root = r;
}
template<class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& t)
{
	root = NULL;
	Copy(root, t.root);
}
template<class T>
BinaryTree<T>& BinaryTree<T>:: operator=(const BinaryTree<T>& t)
{
	destroy();
	root = NULL;
	Copy(root, t.root);
	return *this;
}
template<class T>
void BinaryTree<T>::Copy(BinaryTreeNode<T>*& r, BinaryTreeNode<T>* t)
{
	BinaryTreeNode<T>* ptr = t;
	if (ptr == NULL)
	{
		return;
	}
	r = new BinaryTreeNode<T>(ptr->data);
	Copy(r->leftChild, ptr->leftChild);
	Copy(r->rightChild, ptr->rightChild);
}
template<class T>
BinaryTree<T>::~BinaryTree()
{
	destroy(root);
}
template<class T>
bool BinaryTree<T>::isEmpty() const
{
	return root == NULL;
}
template<class T>
void BinaryTree<T>::preOrder()
{
	preOrder(root, NULL);
	std::cout << std::endl;
}
template<class T>
void BinaryTree<T>::preOrder(BinaryTreeNode<T>* t, void(*func)(BinaryTreeNode<T>*))
{
	if (t != NULL)
	{
		if (func == NULL)
			visit(t);
		else
			(*func)(t);
		preOrder(t->leftChild, func);
		preOrder(t->rightChild, func);
	}
}
template<class T>
void BinaryTree<T>::inOrder()
{
	inOrder(root, NULL);
	std::cout << std::endl;
}
template<class T>
void BinaryTree<T>::inOrder(BinaryTreeNode<T>* t, void(*func)(BinaryTreeNode<T>*))
{
	if (t != NULL)
	{
		inOrder(t->leftChild, func);
		//cout << t->data << " ";
		if (func == NULL)
			visit(t);
		else
			(*func)(t);
		inOrder(t->rightChild, func);
	}
}
template<class T>
void BinaryTree<T>::postOrder()
{
	postOrder(root, NULL);
	std::cout << std::endl;
}
template<class T>
void BinaryTree<T>::postOrder(BinaryTreeNode<T>* t, void(*func)(BinaryTreeNode<T>*))
{
	if (t != NULL)
	{
		postOrder(t->leftChild, func);
		postOrder(t->rightChild, func);
		//cout << t->data << " ";
		if (func == NULL)
			visit(t);
		else
			(*func)(t);
	}
}
template<class T>
int BinaryTree<T>::getHeight() const
{
	return getHeight(root);
}
template<class T>
int BinaryTree<T>::getHeight(BinaryTreeNode<T>* t) const
{
	if (t == NULL)
		return 0;
	else
	{
		int i = getHeight(t->leftChild);
		int j = getHeight(t->rightChild);
		return (i < j) ? j + 1 : i + 1;
	}
}
template<class T>
int BinaryTree<T>::getSize() const
{
	return getSize(root);
}
template<class T>
int BinaryTree<T>::getSize(BinaryTreeNode<T>* t) const
{
	if (t == NULL)
		return 0;
	else
		return 1 + getSize(t->leftChild) + getSize(t->rightChild);
}
template<class T>
BinaryTreeNode<T>* BinaryTree<T>::getRoot() const
{
	return root;
}
template<class T>
void BinaryTree<T>::destroy()
{
	destroy(root);
}
template<class T>
void BinaryTree<T>::destroy(BinaryTreeNode<T>*& t)
{
	if (t == NULL)
		return;
	if (t->leftChild != NULL)
		destroy(t->leftChild);
	if (t->rightChild != NULL)
		destroy(t->rightChild);
	delete t;
	t = NULL;
}
template<class T>
void BinaryTree<T>::createTree(T flag)
{
	createTree(root, flag);
}
template<class T>
void BinaryTree<T>::createTree(BinaryTreeNode<T>*& t, T flag)
{
	destroy();
	T item;
	std::cin >> item;
	if (item == flag)
		t = NULL;
	else
	{
		t = new BinaryTreeNode<T>(item);
		createTree(t->leftChild, flag);
		createTree(t->rightChild, flag);
	}
}
template<class T>
void BinaryTree<T>::createTreeByLevel(T flag,T end)
{
	destroy();
	std::vector<T>str;
	T item;
	while (true)
	{
		std::cin >> item;
		if (item == end)
			break;
		str.push_back(item);
	}
	if (str[0] == flag)
	{
		root = NULL;
		return;
	}
	
	std::queue<BinaryTreeNode<T>*>q;
	root = new BinaryTreeNode<T>(str[0]);

	BinaryTreeNode<T>* p = root;
	int ptr = 1;
	q.push(p);
	
	

	while (!q.empty())
	{
		p = q.front();
		q.pop();
		if (p)
		{
			if (ptr<str.size() && str[ptr] != flag)
			{
				p->leftChild = new BinaryTreeNode<T>(str[ptr]);
				q.push(p->leftChild);
			}
			else
			{
				p->leftChild = NULL;
			}
		}
		ptr++;
		if (p)
		{
			if (ptr < str.size() && str[ptr] != flag)
			{
				p->rightChild = new BinaryTreeNode<T>(str[ptr]);
				q.push(p->rightChild);
			}
			else
			{
				p->rightChild = NULL;
			}
		}
		ptr++;
	}
	
}
template<class T>
BinaryTreeNode<T>* BinaryTree<T>::Parent(BinaryTreeNode<T>* current)
{
	BinaryTreeNode<T>* p = root;
	if (current == root)
		return NULL;
	if (p == NULL)
		return NULL;
	if (p->leftChild == current || p->rightChild == current)
		return p;
	return Parent(p->leftChild);
	return Parent(p->rightChild);
}
template<class T>
BinaryTreeNode<T>* BinaryTree<T>::LeftChild(BinaryTreeNode<T>* current)
{
	if (current == NULL)
		return NULL;
	else
		return current->leftChild;
}
template<class T>
BinaryTreeNode<T>* BinaryTree<T>::RightChild(BinaryTreeNode<T>* current)
{
	if (current == NULL)
		return NULL;
	else
		return current->rightChild;
}
template<class T>
BinaryTreeNode<T>* BinaryTree<T>::LeftSibling(BinaryTreeNode<T>* current)
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
BinaryTreeNode<T>* BinaryTree<T>::RightSibling(BinaryTreeNode<T>* current)
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
void BinaryTree<T>::preOrderNonRecursive() const
{
	std::stack<BinaryTreeNode<T>*> s;
	BinaryTreeNode<T>* p = root;
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
void BinaryTree<T>::inOrderNonRecursive() const
{
	std::stack<BinaryTreeNode<T>*> s;
	BinaryTreeNode<T>* p = root;
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
void BinaryTree<T>::postOrderNonRecursive() const
{
	std::stack<BinaryTreeNode<T>*> s;
	BinaryTreeNode<T>* p = root;
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
void BinaryTree<T>::levelOrder(void(*func)(BinaryTreeNode<T>*))
{
	std::queue<BinaryTreeNode<T>*> q;
	BinaryTreeNode<T>* p = root;
	if (p != NULL)
		q.push(p);
	while (!q.empty())
	{
		p = q.front();
		q.pop();
		//cout << p->data << " ";
		if (func == NULL)
			visit(p);
		else
			func(p);
		if (p->leftChild != NULL)
			q.push(p->leftChild);
		if (p->rightChild != NULL)
			q.push(p->rightChild);
	}
	std::cout << std::endl;
}
template<class T>
void BinaryTree<T>::createTree(const T& data, BinaryTreeNode<T>* leftTree, BinaryTreeNode<T>* rightTree)
{
	destroy();
	root = new BinaryTreeNode<T>(data, leftTree, rightTree);
}

//int main()
//{
//	BinaryTree<char> tree;
//	std::cout << "Please input the data of the tree, end with #:" << std::endl;
//	tree.createTree('#');
//	BinaryTree<char>t2 = tree;
//	//tree.preOrder();
//	//std::cout << std::endl;
//	t2.preOrder();
//
//	tree = t2;
//	tree.preOrder();
//
//	return 0;
//}
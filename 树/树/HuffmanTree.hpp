#include<iostream>
#include<queue>
#include<vector>
#include<map>
typedef std:: vector<bool> Huff_Code;

//using namespace std;

template<class T>
class HuffmanTree;
template<class T>
class HuffmanTreeNode
{
	friend class HuffmanTree<T>;
public:
	HuffmanTreeNode();
	HuffmanTreeNode(T item, int weight, HuffmanTreeNode<T>* left = NULL, HuffmanTreeNode<T>* right = NULL);
	~HuffmanTreeNode() {};
	HuffmanTreeNode<T>& operator=(const HuffmanTreeNode<T>& node);
	bool isLeaf();
	int getWeight() { return weight; };
	T getData() { return data; };
	HuffmanTreeNode<T>* left() const { return leftChild; };
	HuffmanTreeNode<T>* right() const { return rightChild; };
	void setLeft(HuffmanTreeNode<T>* b) { leftChild = b; };
	void setRight(HuffmanTreeNode<T>* b) { rightChild = b; };
	void setData(T newData) { data = newData; };
private:
	T data;
	int weight;
	HuffmanTreeNode<T>* leftChild;
	HuffmanTreeNode<T>* rightChild;
};
template<class T>
HuffmanTreeNode<T>::HuffmanTreeNode()
{
	data = 0;
	weight = 0;
	leftChild = NULL;
	rightChild = NULL;
}
template<class T>
HuffmanTreeNode<T>::HuffmanTreeNode(T item, int weight, HuffmanTreeNode<T>* left, HuffmanTreeNode<T>* right)
{
	data = item;
	this->weight = weight;
	leftChild = left;
	rightChild = right;
}
template<class T>
HuffmanTreeNode<T>& HuffmanTreeNode<T>:: operator=(const HuffmanTreeNode<T>& node)
{
	if (&node==this)
	{
		return *this;
	}
	data = node.data;
	weight = node.weight;
	leftChild = node.leftChild;
	rightChild = node.rightChild;
	return *this;
}
template<class T>
bool HuffmanTreeNode<T>::isLeaf()
{
	if (leftChild == NULL && rightChild == NULL)
		return true;
	else
		return false;
}
template<class T>
class HuffmanTree
{
public:
	HuffmanTree();
	HuffmanTree(HuffmanTreeNode<T>* root);
	HuffmanTree(const HuffmanTree<T>& t);
	~HuffmanTree();
	HuffmanTree<T>& operator=(const HuffmanTree<T>& t);
	void createHuffmanTree(T* x, int* w, int n);//x是存字符的数组，w是权重，n是个数
	void preOrder();
	void inOrder();
	void postOrder();
	void levelOrder();
	int getHeight();
	int getSize();
	HuffmanTreeNode<T>* getRoot();
	void destroy();
	void preOrder(HuffmanTreeNode<T>* subTree);
	void inOrder(HuffmanTreeNode<T>* subTree);
	void postOrder(HuffmanTreeNode<T>* subTree);
	void levelOrder(HuffmanTreeNode<T>* subTree);
	int getHeight(HuffmanTreeNode<T>* subTree);
	int getSize(HuffmanTreeNode<T>* subTree);
	void destroy(HuffmanTreeNode<T>*& subTree);
	
	void createHuffmanTree(std::map<char, Huff_Code>decodeMap);
	std::map<char, Huff_Code> Huffman_Code();
	void Huffman_Code(HuffmanTreeNode<T>* r,Huff_Code curcode);
	Huff_Code enHuffmanCode(const T* x, int size);
	std::vector<T> deHuffmanCode(Huff_Code decode);

private:
	bool isSingleNode;//只有一个节点时特殊处理
	std::map<char, Huff_Code>Huff_Dic;
	HuffmanTreeNode<T>* root;
	void Copy(HuffmanTreeNode<T>*& r, HuffmanTreeNode<T>* t);
};

template<class T>
HuffmanTree<T>::HuffmanTree()
{
	root = NULL;
	isSingleNode = false;
}
template<class T>
HuffmanTree<T>::HuffmanTree(HuffmanTreeNode<T>* root)
{
	this->root = root;
	isSingleNode = false;
}
template<class T>
HuffmanTree<T>::HuffmanTree(const HuffmanTree<T>& t)
{
	root = NULL;
	isSingleNode = t.isSingleNode;
	Copy(root, t.root);
}
template<class T>
void HuffmanTree<T>::Copy(HuffmanTreeNode<T>*& r, HuffmanTreeNode<T>* t)
{
	HuffmanTreeNode<T>* ptr = t;
	if (ptr == NULL)
	{
		return;
	}
	r = new HuffmanTreeNode<T>(ptr->data);
	Copy(r->leftChild, ptr->leftChild);
	Copy(r->rightChild, ptr->rightChild);
}
template<class T>
HuffmanTree<T>::~HuffmanTree()
{
	destroy(root);
}
template<class T>
HuffmanTree<T>& HuffmanTree<T>::operator=(const HuffmanTree<T>& t)
{
	if (&t == this)
	{
		return *this;
	}
	destroy(root);
	root = NULL;
	isSingleNode = t.isSingleNode;
	Copy(root, t.root);
	return *this;
}
template<class T>
void HuffmanTree<T>::createHuffmanTree(T* x, int* w, int n)
{
	destroy(root);
	HuffmanTreeNode<T>** p = new HuffmanTreeNode<T>*[n];
	for (int i = 0; i < n; i++)
	{
		p[i] = new HuffmanTreeNode<T>(x[i], w[i]);
	}
	int min1Index=-1, min2Index=-1 ;
	HuffmanTreeNode<T>* min1=NULL, * min2=NULL;
	if (n == 1)
	{
		root = p[0];
		isSingleNode = true;
		delete[]p;
		return;
	}
	for (int i = 0; i < n - 1; i++)
	{
		min1Index = -1;
		min2Index = -1;
		for (int j = 0; j < n; j++)
		{
			if (p[j] != NULL)
			{
				if (min1Index == -1)
				{
					min1Index = j;
					min1 = p[j];
				}
				else
				{
					if (p[j]->weight < min1->weight)
					{
						min2Index = min1Index;
						min2 = min1;
						min1Index = j;
						min1 = p[j];
					}
					else
					{
						if (min2Index == -1)
						{
							min2Index = j;
							min2 = p[j];
						}
						else
						{
							if (p[j]->weight < min2->weight)
							{
								min2Index = j;
								min2 = p[j];
							}
						}
					}
				}
			}
		}
		p[min1Index] = new HuffmanTreeNode<T>('*', min1->weight + min2->weight, min1, min2);
		p[min2Index] = NULL;
	}
	root = p[min1Index];
	delete[] p;
}
template<class T>
void HuffmanTree<T>::preOrder()
{
	preOrder(root);
}
template<class T>
void HuffmanTree<T>::inOrder()
{
	inOrder(root);
}
template<class T>
void HuffmanTree<T>::postOrder()
{
	postOrder(root);
}
template<class T>
void HuffmanTree<T>::levelOrder()
{
	levelOrder(root);
}
template<class T>
int HuffmanTree<T>::getHeight()
{
	return getHeight(root);
}
template<class T>
int HuffmanTree<T>::getSize()
{
	return getSize(root);
}
template<class T>
HuffmanTreeNode<T>* HuffmanTree<T>::getRoot()
{
	return root;
}
template<class T>
void HuffmanTree<T>::destroy()
{
	destroy(root);
}
template<class T>
void HuffmanTree<T>::preOrder(HuffmanTreeNode<T>* subTree)
{
	if (subTree != NULL)
	{
		std::cout << subTree->data << " ";
		preOrder(subTree->leftChild);
		preOrder(subTree->rightChild);
	}
}
template<class T>
void HuffmanTree<T>::inOrder(HuffmanTreeNode<T>* subTree)
{
	if (subTree != NULL)
	{
		inOrder(subTree->leftChild);
		std::cout << subTree->data << " ";
		inOrder(subTree->rightChild);
	}
}
template<class T>
void HuffmanTree<T>::postOrder(HuffmanTreeNode<T>* subTree)
{
	if (subTree != NULL)
	{
		postOrder(subTree->leftChild);
		postOrder(subTree->rightChild);
		std::cout << subTree->data << " ";
	}
}
template<class T>
void HuffmanTree<T>::levelOrder(HuffmanTreeNode<T>* subTree)
{
	std::queue<HuffmanTreeNode<T>*> q;
	HuffmanTreeNode<T>* p = root;
	if (p != NULL)
		q.push(p);
	while (!q.empty())
	{
		p = q.front();
		q.pop();
		std::cout << p->data << ":" << p->weight << " ";
		if (p->leftChild != NULL)
			q.push(p->leftChild);
		if (p->rightChild != NULL)
			q.push(p->rightChild);
	}
}
template<class T>
int HuffmanTree<T>::getHeight(HuffmanTreeNode<T>* subTree)
{
	if (subTree == NULL)
	{
		return 0;
	}
	else
	{
		int i = getHeight(subTree->leftChild);
		int j = getHeight(subTree->rightChild);
		return (i < j) ? j + 1 : i + 1;
	}
}
template<class T>
int HuffmanTree<T>::getSize(HuffmanTreeNode<T>* subTree)
{
	if (subTree == NULL)
	{
		return 0;
	}
	else
	{
		return 1 + getSize(subTree->leftChild) + getSize(subTree->rightChild);
	}
}
template<class T>
void HuffmanTree<T>::destroy(HuffmanTreeNode<T>*& subTree)
{
	if (subTree == NULL)
		return;
	if (subTree->leftChild != NULL)
		destroy(subTree->leftChild);
	if (subTree->rightChild != NULL)
		destroy(subTree->rightChild);
	delete subTree;
	subTree = NULL;
}
template<class T>
std::map<char, Huff_Code> HuffmanTree<T>::Huffman_Code()
{
	Huff_Code curcode;
	Huffman_Code(root, curcode);
	return Huff_Dic;
}
template<class T>
void HuffmanTree<T>::Huffman_Code(HuffmanTreeNode<T>*r,Huff_Code curcode)
{
	if (isSingleNode)
	{
		curcode.push_back(false);
		Huff_Dic[r->data] = curcode;
		return;
	}
	if (r->isLeaf())
	{
		Huff_Dic[r->getData()] = curcode;
		return;
	}
	Huff_Code lcode = curcode;
	Huff_Code rcode = curcode;
	lcode.push_back(false);
	rcode.push_back(true);
	Huffman_Code(r->left(), lcode);
	Huffman_Code(r->right(), rcode);
}
template<class T>
Huff_Code HuffmanTree<T>::enHuffmanCode(const T* x,int size)
{
	Huff_Code ret;
	for (int i = 0; i < size; i++)
	{
		Huff_Code code=Huff_Dic[x[i]];
		for (auto it = code.begin(); it!=code.end(); it++)
		{
			ret.push_back(*it);
		}
		
	}
	return ret;
}
template<class T>
std::vector<T> HuffmanTree<T>::deHuffmanCode(Huff_Code decode)
{
	std::vector<T> ret;
	HuffmanTreeNode<T>* p = root;
	for (auto it = decode.begin(); it != decode.end(); it++)
	{
		if (p->isLeaf())
		{
			ret.push_back(p->data);
			p = root;
		}
		
		if (!isSingleNode)
		{
			if (*it == false)
			{
				p = p->leftChild;
			}
			else
			{
				p = p->rightChild;
			}
		}

	}
	if (p->isLeaf())
	{
		ret.push_back(p->data);
	}
	return ret;
}
template<class T>
void HuffmanTree<T>::createHuffmanTree(std::map<char, Huff_Code>decodeMap)
{
	destroy(root);
	Huff_Dic = decodeMap;
	if (decodeMap.size() == 1)
	{
		isSingleNode = true;
		root = new HuffmanTreeNode<T>(decodeMap.begin()->first, 0);
		return;
	}
	root = new HuffmanTreeNode<T>;
	for (auto it = decodeMap.begin(); it != decodeMap.end(); it++)
	{
		HuffmanTreeNode<T>* p = root;
		for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
		{
			if (*it2 == false)
			{
				if (p->leftChild == NULL)
				{
					p->leftChild = new HuffmanTreeNode<T>;
				}
				p = p->leftChild;
			}
			else
			{
				if (p->rightChild == NULL)
				{
					p->rightChild = new HuffmanTreeNode<T>;
				}
				p = p->rightChild;
			}
		}
		p->data = it->first;
		
	}
	
	
}


//int main()
//{
//	HuffmanTree<char> tree;
//	char str[11] = "ABCDEFGH";
//	int weight[256] = { 0 };
//	for (int i = 0; i < strlen(str); i++)
//	{
//		weight[i] = 1;
//	}
//	tree.createHuffmanTree(str, weight,strlen(str));
//	std::map<char, Huff_Code> Huff_Dic = tree.Huffman_Code();
//	for (auto i : Huff_Dic)
//	{
//		std::cout << i.first << ":";
//		for (auto j : i.second)
//		{
//			std::cout << j;
//		}
//		std::cout << std::endl;
//	}
//	return 0;
//	
//}

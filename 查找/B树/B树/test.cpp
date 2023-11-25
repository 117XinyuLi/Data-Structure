#include"BTree.hpp"
#include<iostream>

using namespace std;


int main()
{
	BTree <int, int, 3> t;
	
	t.Insert(make_pair(1, 1));
	t.Insert(make_pair(2, 2));
	t.Insert(make_pair(3, 3));
	
	
	return 0;
	
}
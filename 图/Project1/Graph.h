#pragma once
#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
#include"LinkList.hpp"
typedef struct
{
	int begin;
	int end;
	int weight;
}Edge;//边集数组
class Graphl;
class Graphm
{
	friend Graphl toGraphl(const Graphm& change);
	friend Graphm toGraphm(const Graphl& change);
private:
	int** matrix;
	int numVertex;
	int numEdge;
	int* inDegree;//图的顶点的入度数组
	int* outDegree;//图的顶点的出度数组
	bool* visited;
	std::vector<std::vector<int>>topoSortIndex;
	int Find(int* parent, int f);
	void TopoSortAll(int i, std::vector<int> path);

	//void sort(Edge edges[]);
	//void Swapn(Edge* edges, int i, int j);
public:
	Graphm(int numVert);
	~Graphm();
	Graphm(const Graphm& g);
	Graphm& operator=(const Graphm& g);
	Graphl to_Graphl();
	int VerticesNum();
	int EdgesNum();
	int firstAdj(int v);
	int nextAdj(int v, int w);
	void setEdge(int from, int to, int wt);
	void delEdge(int from, int to);
	bool isEdge(int i, int j);
	int weight(int v1, int v2);
	int getInDegree(int v);
	int getOutDegree(int v);
	void print();
	void DFS(int v);
	void DFSTraverse();
	void BFS(int v);
	void BFSTraverse();
	void MiniSpanTree_Prim();
	void MiniSpanTree_Kruskal();
	void DFS_for_judge_connected_graph(int v);
	bool is_connected_undirected_graph();
	void ShortestPath_Dijkstra(int v0, int* Patharc, int* ShortPathTable);
	void ShortestPath_Floyd(int** Patharc, int** ShortPathTable);
	bool TopologicalSort(std::vector<int>& path);
	void CriticalPath();

	std::vector<std::vector<int>> topoSortAll();




};

struct listUnit
{
	int vertex;//顶点,从0开始
	int weight;//一般大于0
};
class Graphl
{
	friend Graphl toGraphl(const Graphm& change);
	friend Graphm toGraphm(const Graphl& change);
private:
	LinkList<listUnit>* vexList;
	int numVertex;
	int numEdge;
	bool* visited;//Visit指针保存图的顶点的标志位数组
	int* InDegree;//InDegree指针保存图的顶点的入度数组
	int* OutDegree;//OutDegree指针保存图的顶点的出度数组
	bool is_connected_graph();
	void DFS_for_judge_connected_graph(int oneVex);
	bool TopologicalSort_for_Critical_Path(int* stack2, int& top2, int* etv);
public:
	int VerticesNum();//返回图的顶点数
	int EdgesNum();//返回图的边数
	Graphl(int numVert);
	~Graphl();
	Graphl(const Graphl& g);
	Graphl& operator=(const Graphl& g);
	Graphm to_Graphm();
	int weight(int from, int to);
	int FirstAdj(int oneVex);
	int NextAdj(int oneVex, int preVex);
	void setEdge(int from, int to, int weight);
	void delEdge(int from, int to);
	void setVex(int oneVex, int weight);
	void delVex(int oneVex);
	void print();
	void printWeight();
	void printInDegree();
	void printOutDegree();
	void DFS();
	void DFS(int oneVex, bool* visited);
	void BFS();
	void BFS(int oneVex, bool* visited);
	void MiniSpanTree_Prim();
	void MiniSpanTree_Kruskal();
	void ShortestPath_Dijkstra(int v0, int* Patharc, int* ShortPathTable);
	void ShortestPath_Floyd(int** Patharc, int** ShortPathTable);
	bool TopologicalSort(std::vector<int>& path);
	void CriticalPath();











};

inline Graphl toGraphl(const Graphm& change)
{

	Graphl g(change.numVertex);
	g.numVertex = change.numVertex;
	g.numEdge = 0;

	for (int i = 0; i < change.numVertex; i++)
	{
		for (int j = 0; j < change.numVertex; j++)
		{
			if (change.matrix[i][j] != 0)
			{
				g.setEdge(i, j, change.matrix[i][j]);
			}
		}
	}
	return g;
}
inline Graphm toGraphm(const Graphl& change)
{
	Graphm temp(change.numVertex);
	temp.numVertex = change.numVertex;
	temp.numEdge = change.numEdge;

	for (int i = 0; i < change.numVertex; i++)
	{
		Node<listUnit>* p = change.vexList[i].head;
		while (p->next != NULL)
		{
			temp.matrix[i][p->next->data.vertex] = p->next->data.weight;
			p = p->next;
		}
	}
	for (int i = 0; i < change.numVertex; i++)
	{
		temp.inDegree[i] = change.InDegree[i];
		temp.outDegree[i] = change.OutDegree[i];
	}
	return temp;

}
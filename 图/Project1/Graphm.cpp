#include"Graph.h"

Graphm::Graphm( int numVert)
{
	numVertex = numVert;
	numEdge = 0;
	matrix = new int* [numVertex];
	for (int i = 0; i < numVertex; i++)
	{
		matrix[i] = new int[numVertex];
		for (int j = 0; j < numVertex; j++)
			matrix[i][j] = 0;
	}
	inDegree = new int[numVertex];
	outDegree = new int[numVertex];
	visited = NULL;
	for (int i = 0; i < numVertex; i++)
	{
		inDegree[i] = 0;
		outDegree[i] = 0;
	}
}
Graphm::~Graphm()
{
	for (int i = 0; i < numVertex; i++)
		delete[] matrix[i];
	delete[] matrix;
	delete[] inDegree;
	delete[] visited;
	delete[] outDegree;
}
Graphm::Graphm(const Graphm& g)
{
	numVertex = g.numVertex;
	numEdge = g.numEdge;
	matrix = new int* [numVertex];
	for (int i = 0; i < numVertex; i++)
	{
		matrix[i] = new int[numVertex];
		for (int j = 0; j < numVertex; j++)
			matrix[i][j] = g.matrix[i][j];
	}
	inDegree = new int[numVertex];
	outDegree = new int[numVertex];
	for (int i = 0; i < numVertex; i++)
	{
		inDegree[i] = g.inDegree[i];
		outDegree[i] = g.outDegree[i];
	}
	visited = NULL;
}
Graphm& Graphm::operator=(const Graphm& g)
{
	if (this == &g)
		return *this;
	for (int i = 0; i < numVertex; i++)
		delete[] matrix[i];
	delete[] matrix;
	delete[] inDegree;
	delete[] visited;
	numVertex = g.numVertex;
	numEdge = g.numEdge;
	matrix = new int* [numVertex];
	for (int i = 0; i < numVertex; i++)
	{
		matrix[i] = new int[numVertex];
		for (int j = 0; j < numVertex; j++)
			matrix[i][j] = g.matrix[i][j];
	}
	inDegree = new int[numVertex];
	outDegree = new int[numVertex];
	for (int i = 0; i < numVertex; i++)
	{
		inDegree[i] = g.inDegree[i];
		outDegree[i] = g.outDegree[i];
	}
	visited = NULL;
	return *this;
}
Graphl Graphm::to_Graphl()
{
	return toGraphl(*this);
}
int Graphm::VerticesNum()
{
	return numVertex;
}
int Graphm::EdgesNum()
{
	return numEdge;
}
int Graphm::firstAdj(int v)//������v������ĵ�һ���ڽӵ�,v��Ϊ�ߵ����
{
	if (v < 0 || v >= numVertex)
	{
		std::cout << "���㷶Χ����" << std::endl;
		return -1;
	}
	for (int i = 0; i < numVertex; i++)
		if (matrix[v][i] != 0)
			return i;
	return -1;
}
int Graphm::nextAdj(int v, int w)//������v�����(v��Ϊ���)��w֮��(w+1��ʼ)����һ���ڽӵ�
{
	if (v < 0 || v >= numVertex || w < 0 || w >= numVertex)
	{
		std::cout << "���㷶Χ����" << std::endl;
		return -1;
	}
	for (int i = w + 1; i < numVertex; i++)
		if (matrix[v][i] != 0)
			return i;
	return -1;
}
void Graphm::setEdge(int from, int to, int wt)
{
	if (wt == 0 || from < 0 || to < 0 || from >= numVertex || to >= numVertex)
	{
		std::cout << "ȨֵΪ0�򶥵㷶Χ����" << std::endl;
		return;
	}
	if (matrix[from][to] == 0)
	{
		numEdge++;
		inDegree[to]++;
		outDegree[from]++;
	}
	matrix[from][to] = wt;
}
void Graphm::delEdge(int from, int to)
{
	if (from < 0 || to < 0 || from >= numVertex || to >= numVertex)
	{
		std::cout << "���㷶Χ����" << std::endl;
		return;
	}
	if (matrix[from][to] != 0)
	{
		numEdge--;
		inDegree[to]--;
		outDegree[from]--;
	}
	matrix[from][to] = 0;
}
bool Graphm::isEdge(int i, int j)
{
	return (matrix[i][j] != 0);
}
int Graphm::weight(int v1, int v2)
{
	return matrix[v1][v2];
}
int Graphm::getInDegree(int v)
{
	if (v < 0 || v >= numVertex)
	{
		std::cout << "���㷶Χ����" << std::endl;
		return -1;
	}
	return inDegree[v];
}
int Graphm::getOutDegree(int v)
{
	if (v < 0 || v >= numVertex)
	{
		std::cout << "���㷶Χ����" << std::endl;
		return -1;
	}
	return outDegree[v];
}
void Graphm::print()
{
	std::cout << "��ӡͼ��" << std::endl;
	for (int i = 0; i < numVertex; i++)
	{
		for (int j = 0; j < numVertex; j++)
			std::cout << matrix[i][j] << " ";
		std::cout << std::endl;
	}
}
void Graphm::DFS(int v)
{
	visited[v] = true;
	std::cout << v << " ";
	for (int w = 0; w < numVertex; w++)
	{
		if (matrix[v][w] != 0 && !visited[w])
			DFS(w);
	}
}
void Graphm::DFSTraverse()
{
	std::cout << "������ȱ�����" << std::endl;
	visited = new bool[numVertex];
	for (int i = 0; i < numVertex; i++)
		visited[i] = false;
	for (int i = 0; i < numVertex; i++)
		if (!visited[i])
			DFS(i);
	std::cout << std::endl;
	delete[] visited;
	visited = NULL;
}
void Graphm::BFS(int v)
{
	std::queue<int> q;
	q.push(v);
	visited[v] = true;
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		std::cout << v << " ";
		for (int w = 0; w < numVertex; w++)
		{
			if (matrix[v][w] != 0 && !visited[w])
			{
				q.push(w);
				visited[w] = true;
			}
		}
	}
}
void Graphm::BFSTraverse()
{
	std::cout << "������ȱ�����" << std::endl;
	visited = new bool[numVertex];
	for (int i = 0; i < numVertex; i++)
		visited[i] = false;
	for (int i = 0; i < numVertex; i++)
		if (!visited[i])
			BFS(i);
	std::cout << std::endl;
	delete[] visited;
	visited = NULL;
}
void Graphm::DFS_for_judge_connected_graph(int v)
{
	visited[v] = true;
	for (int w = 0; w < numVertex; w++)
	{
		if (matrix[v][w] != 0 && !visited[w])
			DFS_for_judge_connected_graph(w);
	}
}
bool Graphm::is_connected_undirected_graph()
{
	visited = new bool[numVertex];
	for (int i = 0; i < numVertex; i++)
	{
		visited[i] = false;
	}
	DFS_for_judge_connected_graph(0);
	for (int i = 0; i < numVertex; i++)
	{
		if (!visited[i])
		{
			std::cout << "��ͼ����ͨ" << std::endl;
			delete[] visited;
			visited = NULL;
			return false;
		}
	}
	delete[] visited;
	visited = NULL;
	for (int i = 0; i < numVertex; i++)
	{
		for (int j = 0; j < numVertex; j++)
		{
			if (i == j)
			{
				if (matrix[i][j] != 0)
				{
					std::cout << "ָ������Ľ��ȨֵӦΪ0" << std::endl;
					return false;
				}
			}
			else
			{
				if (matrix[i][j] != matrix[j][i])
				{

					std::cout << "��ͼ��������ͼ" << std::endl;
					return false;
				}
			}
			if (matrix[i][j] < 0)
			{
				std::cout << "Ȩֵ����Ϊ����" << std::endl;
				return false;
			}
		}
	}
	return true;
}
void Graphm::MiniSpanTree_Prim()
{
	if (!is_connected_undirected_graph())
	{
		return;
	}

	int **Prim_matrix=new int* [numVertex];
	for (int i = 0; i < numVertex; i++)
	{
		Prim_matrix[i] = new int[numVertex];
		for (int j = 0; j < numVertex; j++)
			Prim_matrix[i][j] = 0;
	}

	for (int i = 0; i < numVertex; i++)
	{
		for (int j = 0; j < numVertex;j++) 
		{
			if (i == j||matrix[i][j]!=0)
			{
				if (matrix[i][j] >= INT_MAX)
				{
					std::cout << "Ȩֵ̫��" << std::endl;
					return;
				}
				Prim_matrix[i][j] = matrix[i][j];
			}
			else
			{
				Prim_matrix[i][j] = INT_MAX;
			}
		}
	}
	

	/*for (int i = 0; i < numVertex; i++)
	{
		for (int j = 0; j < numVertex; j++)
		{
			std::cout << Prim_matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}*/
	
	std::cout<<"��ӡ��С��������"<<std::endl;
	int* lowcost = new int[numVertex];
	int* adjvex = new int[numVertex];
	int min, minid;
	lowcost[0] = 0;
	adjvex[0] = 0;
	for (int i = 1; i < numVertex; i++)
	{
		lowcost[i] = Prim_matrix[0][i];
		adjvex[i] = 0;
	}
	for (int i = 1; i < numVertex; i++)
	{
		min = INT_MAX;
		minid = 0;
		for (int j = 1; j < numVertex; j++)
		{
			if (lowcost[j] != 0 && lowcost[j] < min)
			{
				min = lowcost[j];
				minid = j;
			}
		}
		std::cout << "(" << adjvex[minid] << "," << minid << ") " << Prim_matrix[adjvex[minid]][minid] << std::endl;
		lowcost[minid] = 0;
		for (int j = 1; j < numVertex; j++)
		{
			if (lowcost[j] != 0 && Prim_matrix[minid][j] < lowcost[j])
			{
				lowcost[j] = Prim_matrix[minid][j];
				adjvex[j] = minid;
			}
		}
	}
	delete[] lowcost;
	delete[] adjvex;
	for (int i = 0; i < numVertex; i++)
		delete[] Prim_matrix[i];
	delete[] Prim_matrix;
}
//void Graphm::Swapn(Edge* edges, int i, int j)
//{
//	int temp;
//	temp = edges[i].begin;
//	edges[i].begin = edges[j].begin;
//	edges[j].begin = temp;
//	temp = edges[i].end;
//	edges[i].end = edges[j].end;
//	edges[j].end = temp;
//	temp = edges[i].weight;
//	edges[i].weight = edges[j].weight;
//	edges[j].weight = temp;
//}
//void Graphm::sort(Edge edges[])
//{
//	int i, j;
//	for (i = 0; i < numEdge/2; i++)
//	{
//		for (j = i + 1; j < numEdge/2; j++)
//		{
//			if (edges[i].weight > edges[j].weight)
//			{
//				Swapn(edges, i, j);
//			}
//		}
//	}
//	std::cout<<"Ȩ����֮���Ϊ:" << std::endl;
//	for (i = 0; i < numEdge/2; i++)
//	{
//		std::cout << "(" << edges[i].begin << "," << edges[i].end << ") " << edges[i].weight << std::endl;
//	}
//
//}
int Graphm::Find(int* parent, int f)
{
	while (parent[f] > 0)
	{
		f = parent[f];
	}
	return f;
}
static bool edge_cmp(Edge e1, Edge e2)
{
	return (e1.weight < e2.weight);
}
void Graphm::MiniSpanTree_Kruskal()
{
	if (!is_connected_undirected_graph())
	{
		return;
	}

	//��ͼ�����Ϊ����ͼ�����Ҫ������ͼʹ�ã�numEdgeҪ���Զ�

	int n=0, m=0;
	//int k = 0;
	int* parent=new int[numVertex];
	//Edge* edges = new Edge[numEdge/2];
	std::vector<Edge>edges;

	int** K_matrix = new int* [numVertex];
	for (int i = 0; i < numVertex; i++)
	{
		K_matrix[i] = new int[numVertex];
		for (int j = 0; j < numVertex; j++)
			K_matrix[i][j] = 0;
	}

	for (int i = 0; i < numVertex; i++)
	{
		for (int j = 0; j < numVertex; j++)
		{
			if (matrix[i][j] != 0)
			{
				if (matrix[i][j] >= INT_MAX)
				{
					std::cout << "Ȩֵ̫��" << std::endl;
					return;
				}
				K_matrix[i][j] = matrix[i][j];
			}
			else
			{
				K_matrix[i][j] = INT_MAX;
			}
		}
	}

	for (int i = 0; i < numVertex - 1; i++)
	{
		for (int j = i + 1; j < numVertex; j++)
		{
			if (K_matrix[i][j] < INT_MAX)
			{
				Edge temp={0};
				/*edges[k].begin = i;
				edges[k].end = j;
				edges[k].weight = K_matrix[i][j];*/
				temp.begin = i;
				temp.end = j;
				temp.weight = K_matrix[i][j];
				edges.push_back(temp);
				//k++;
			}
		}
	}
	//sort(edges);
	std::stable_sort(edges.begin(),edges.end(),edge_cmp);
	std::cout << "Ȩ����֮���Ϊ:" << std::endl;
	for (int i = 0; i < numEdge / 2; i++)
	{
		std::cout << "(" << edges[i].begin << "," << edges[i].end << ") " << edges[i].weight << std::endl;
	}

	

	for (int i = 0; i < numVertex; i++)
		parent[i] = 0;	

	std::cout << "��ӡ��С��������" << std::endl;
	for (int i = 0; i < numEdge/2; i++)	
	{
		n = Find(parent, edges[i].begin);
		m = Find(parent, edges[i].end);
		if (n != m) 
		{
			parent[n] = m;
			std::cout << "(" << edges[i].begin << "," << edges[i].end << ") " << edges[i].weight << std::endl;
		}
	}


	delete[]parent;
	//delete[]edges;
	for (int i = 0; i < numVertex; i++)
		delete[] K_matrix[i];
	delete[] K_matrix;
}
void Graphm::ShortestPath_Dijkstra(int v0, int* Patharc, int* ShortPathTable)
{
	/*  Dijkstra�㷨����������G��v0���㵽���ඥ��v�����·��Patharc[v]����Ȩ����ShortPathTable[v] */
	/*  Patharc[v]��ֵΪǰ�������±�,Ϊ-1��ʾǰ������Ϊv0,ShortPathTable[v]��ʾv0��v�����·�����Ⱥ� */
	
	
	if (!is_connected_undirected_graph())
	{
		std::cout << "��ʵͼ����ͨ��ͼ����Ҳ�ǿ��������·���ģ�����������д��" << std::endl;
		std::cout << "�ڸ��ӣ��Ժ��п�����������ܰ�����ô��������~��" << std::endl;
		return;
	}

	int** D_matrix = new int* [numVertex];
	for (int i = 0; i < numVertex; i++)
	{
		D_matrix[i] = new int[numVertex];
		for (int j = 0; j < numVertex; j++)
			D_matrix[i][j] = 0;
	}

	for (int i = 0; i < numVertex; i++)
	{
		for (int j = 0; j < numVertex; j++)
		{
			if ( matrix[i][j] != 0)
			{
				if (matrix[i][j]>=SHRT_MAX*10)
				{
					std::cout << "Ȩֵ̫��" << std::endl;
					return;
				}
				D_matrix[i][j] = matrix[i][j];
			}
			else
			{
				D_matrix[i][j] = SHRT_MAX*10;//̫��������Ϊ����
			}
		}
	}
	
	
	int  k, min;
	int* final = new int[numVertex];
	//int final[MAXVEX];
	for (int v = 0; v < numVertex; v++)   
	{
		final[v] = 0;			
		ShortPathTable[v] = D_matrix[v0][v];
		Patharc[v] = -1;
	}
	ShortPathTable[v0] = 0;
	final[v0] = 1;   
	
	for (int v = 1; v < numVertex; v++)
	{
		min = SHRT_MAX*10; //̫��������Ϊ����
		for (int w = 0; w < numVertex; w++) 
		{
			if (!final[w] && ShortPathTable[w] < min)
			{
				k = w;
				min = ShortPathTable[w];
			}
		}
		final[k] = 1;  
		for (int w = 0; w < numVertex; w++) 
		{
			if (!final[w] && (min + D_matrix[k][w] < ShortPathTable[w]))
			{ 
				ShortPathTable[w] = min + D_matrix[k][w];
				Patharc[w] = k;
			}
		}
	}
	
	delete[]final;
	for (int i = 0; i < numVertex; i++)
		delete[] D_matrix[i];
	delete[] D_matrix;

	
}
void Graphm::ShortestPath_Floyd(int** Patharc, int** ShortPathTable)
{
	/*  Floyd�㷨����������G�и�����v�����ඥ��w���·��P[v][w]����Ȩ����D[v][w] */

	if (!is_connected_undirected_graph())
	{
		std::cout << "��ʵͼ����ͨ��ͼ����Ҳ�ǿ��������·���ģ�����������д��" << std::endl;
		std::cout << "�ڸ��ӣ��Ժ��п�����������ܰ�����ô��������~��" << std::endl;
		return;
	}

	int** D_matrix = new int* [numVertex];
	for (int i = 0; i < numVertex; i++)
	{
		D_matrix[i] = new int[numVertex];
		for (int j = 0; j < numVertex; j++)
			D_matrix[i][j] = 0;
	}

	for (int i = 0; i < numVertex; i++)
	{
		for (int j = 0; j < numVertex; j++)
		{
			if (i==j||matrix[i][j] != 0)
			{
				if (matrix[i][j] >= SHRT_MAX * 10)
				{
					std::cout << "Ȩֵ̫��" << std::endl;
					return;
				}
				D_matrix[i][j] = matrix[i][j];
			}
			else
			{
				D_matrix[i][j] = SHRT_MAX * 10;//̫��������Ϊ����
			}
		}
	}

	for (int v = 0; v < numVertex; v++)
	{
		for (int w = 0; w < numVertex; w++)
		{
			ShortPathTable[v][w] = D_matrix[v][w];
			Patharc[v][w] = w;
		}
	}
	for (int k = 0; k < numVertex; k++)
	{
		for (int v = 0; v < numVertex; v++)
		{
			for (int w = 0; w < numVertex; w++)
			{
				if (ShortPathTable[v][w] > ShortPathTable[v][k] + ShortPathTable[k][w])
				{
					ShortPathTable[v][w] = ShortPathTable[v][k] + ShortPathTable[k][w];
					Patharc[v][w] = Patharc[v][k];
				}
			}
		}
	}
	
	for (int i = 0; i < numVertex; i++)
		delete[] D_matrix[i];
	delete[] D_matrix;
	
	int k;
	std::cout << "���������̾������£�" << std::endl;
	for (int v = 0; v < numVertex; v++)
	{
		for (int w = v + 1; w < numVertex; w++)
		{
			std::cout << "v" << v << "��v" << w << " weight:" << ShortPathTable[v][w]<<" ";
			k = Patharc[v][w];
			std::cout << " path: " << v ;
			while (k != w)
			{
				std::cout << "->" << k;
				k = Patharc[k][w];
			}
			std::cout << "->" << w << std::endl;
		}
	}
	
}
bool Graphm::TopologicalSort(std::vector<int>& path)
{
	return this->to_Graphl().TopologicalSort(path);
}
void Graphm::CriticalPath()
{
	this->to_Graphl().CriticalPath();
}

void Graphm::TopoSortAll(int i, std::vector<int> path)
{
	if (i == numVertex)
	{
		/*for (int j = 0; j < numVertex; j++)
			std::cout << path[j] << " ";
		std::cout << std::endl;*/
		topoSortIndex.push_back(path);
		return;
	}
	for (int j = 0; j < numVertex; j++)
	{
		if (inDegree[j] == 0)
		{
			inDegree[j] = -1;
			path.push_back(j);
			for (int k = 0; k < numVertex; k++)
			{
				if (matrix[j][k] > 0)
					inDegree[k]--;
			}
			TopoSortAll(i + 1, path);
			for (int k = 0; k < numVertex; k++)
			{
				if (matrix[j][k] > 0)
					inDegree[k]++;
			}
			inDegree[j] = 0;
			path.pop_back();
		}
	}
}
std::vector<std::vector<int>> Graphm::topoSortAll()
{
	std::vector<int>path;
	if (!TopologicalSort(path))
	{
		std::cout << "ͼ���л�·���޷�������������" << std::endl;
		topoSortIndex.clear();
		return topoSortIndex;
	}
	Graphm temp = *this;
	//for (int i = 0; i < numVertex; i++)
	//{
	//	if (inDegree[i] == 0)
	//	{
	//		//std::cout << "i=" << i << std::endl;
	//		std::vector<int> path;
	//		TopoSortAll(i, path);
	//	}
	//}
	std::vector<int> topoPath;
	TopoSortAll(0, topoPath);
	*this = temp;
	return topoSortIndex;
}



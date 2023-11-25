#include"Graph.h"

int Graphl:: VerticesNum() { return numVertex; }//返回图的顶点数
int Graphl::EdgesNum() { return numEdge; }//返回图的边数
Graphl::Graphl(int numVert)
{
	numVertex = numVert;
	numEdge = 0;
	vexList = new LinkList<listUnit>[numVertex];
	visited = NULL;
	InDegree = new int[numVertex];
	OutDegree = new int[numVertex];
	for (int i = 0; i < numVertex; i++)
	{
		vexList[i].head->data.vertex = i;
		vexList[i].head->data.weight = 0;
	}
	for (int i = 0; i < numVertex; i++)
	{
		InDegree[i] = 0;
		OutDegree[i] = 0;
	}
}
Graphl::~Graphl()
{
	for (int i = 0; i < numVertex; i++)
	{
		vexList[i].removeall();
	}

	delete[] vexList;
	delete[] visited;
	delete[] InDegree;
	delete[] OutDegree;
}
Graphl::Graphl(const Graphl& g)
{
	numVertex = g.numVertex;
	numEdge = g.numEdge;
	vexList = new LinkList<listUnit>[numVertex];
	visited = NULL;
	InDegree = new int[numVertex];
	OutDegree = new int[numVertex];
	for (int i = 0; i < numVertex; i++)
	{
		vexList[i].head->data.vertex = i;
		vexList[i].head->data.weight = 0;
	}
	for (int i = 0; i < numVertex; i++)
	{
		Node<listUnit>* p = g.vexList[i].head->next;
		while (p != NULL)
		{
			vexList[i].curr = vexList[i].tail;
			vexList[i].Insert(p->data);
			p = p->next;
		}
	}
	for (int i = 0; i < numVertex; i++)
	{
		InDegree[i] = g.InDegree[i];
		OutDegree[i] = g.OutDegree[i];
	}

}
Graphl& Graphl:: operator=(const Graphl& g)
{
	if (this == &g)
		return *this;
	for (int i = 0; i < numVertex; i++)
	{
		vexList[i].removeall();
	}
	delete[] vexList;
	delete[] visited;
	delete[] InDegree;
	delete[] OutDegree;
	numVertex = g.numVertex;
	numEdge = g.numEdge;
	vexList = new LinkList<listUnit>[numVertex];
	visited = NULL;
	InDegree = new int[numVertex];
	OutDegree = new int[numVertex];
	for (int i = 0; i < numVertex; i++)
	{
		vexList[i].head->data.vertex = i;
		vexList[i].head->data.weight = 0;
	}
	for (int i = 0; i < numVertex; i++)
	{
		Node<listUnit>* p = g.vexList[i].head->next;
		while (p != NULL)
		{
			vexList[i].curr = vexList[i].tail;
			vexList[i].Insert(p->data);
			p = p->next;
		}
	}
	for (int i = 0; i < numVertex; i++)
	{
		InDegree[i] = g.InDegree[i];
		OutDegree[i] = g.OutDegree[i];
	}
	return *this;


}
Graphm Graphl::to_Graphm()
{
	return toGraphm(*this);
}
int Graphl::weight(int from, int to)
{
	if (from < 0 || from >= numVertex || to < 0 || to >= numVertex)
	{
		std::cout << "顶点范围有误" << std::endl;
		return -1;
	}
	Node<listUnit>* temp = vexList[from].head;
	while (temp->next != NULL && temp->next->data.vertex != to)
	{
		temp = temp->next;
	}
	if (temp->next == NULL)
	{
		std::cout << "边不存在" << std::endl;
		return -1;
	}
	return temp->next->data.weight;

}
int Graphl::FirstAdj(int oneVex)
{
	if (oneVex < 0 || oneVex >= numVertex)
	{
		std::cout << "顶点范围有误" << std::endl;
		return -1;
	}
	if (vexList[oneVex].head->next == NULL)
	{
		return -1;
	}
	return vexList[oneVex].head->next->data.vertex;
}
int Graphl::NextAdj(int oneVex, int preVex)
{
	if (oneVex < 0 || oneVex >= numVertex || preVex < 0 || preVex >= numVertex)
	{
		std::cout << "顶点范围有误" << std::endl;
		return -1;
	}
	Node<listUnit>* temp = vexList[oneVex].head;
	while (temp->next != NULL && temp->next->data.vertex <= preVex)
	{
		temp = temp->next;
	}
	if (temp->next == NULL)
	{
		std::cout << "preVex的NextAdj边不存在" << std::endl;
		return -1;
	}
	if (temp->data.vertex != preVex)
	{
		std::cout << "preVex不在oneVex的边中" << std::endl;
		return -1;
	}
	return temp->next->data.vertex;
}
void Graphl::setEdge(int from, int to, int weight)//设置边
{
	if (from < 0 || from >= numVertex || to < 0 || to >= numVertex)
	{
		std::cout << "顶点范围有误" << std::endl;
		return;
	}
	Node<listUnit>* temp = vexList[from].head;
	while (temp->next != NULL && temp->next->data.vertex < to)
	{
		temp = temp->next;
	}
	if (temp->next == NULL)
	{
		temp->next = new Node<listUnit>;
		temp->next->data.vertex = to;
		temp->next->data.weight = weight;
		temp->next->next = NULL;
		InDegree[to]++;
		OutDegree[from]++;
		numEdge++;
		return;
	}
	if (temp->next->data.vertex == to)
	{
		temp->next->data.weight = weight;
		return;
	}
	if (temp->next->data.vertex > to)
	{
		Node<listUnit>* temp2 = temp->next;
		temp->next = new Node<listUnit>;
		temp->next->data.vertex = to;
		temp->next->data.weight = weight;
		temp->next->next = temp2;
		InDegree[to]++;
		OutDegree[from]++;
		numEdge++;
		return;
	}

}
void Graphl::delEdge(int from, int to)//删除边
{
	if (from < 0 || from >= numVertex || to < 0 || to >= numVertex)
	{
		std::cout << "顶点范围有误" << std::endl;
		return;
	}
	Node<listUnit>* temp = vexList[from].head;
	while (temp->next != NULL && temp->next->data.vertex < to)
	{
		temp = temp->next;
	}
	if (temp->next == NULL)
	{
		std::cout << "该边不存在" << std::endl;
		return;
	}
	if (temp->next->data.vertex == to)
	{
		Node<listUnit>* temp2 = temp->next;
		temp->next = temp->next->next;
		delete temp2;
		InDegree[to]--;
		OutDegree[from]--;
		numEdge--;
		return;
	}
	if (temp->next->data.vertex > to)
	{
		std::cout << "该边不存在" << std::endl;
		return;
	}

}
void Graphl::setVex(int oneVex, int weight)//设置顶点
{
	if (oneVex < 0 || oneVex >= numVertex)
	{
		std::cout << "顶点范围有误" << std::endl;
		return;
	}
	vexList[oneVex].head->data.weight = weight;
}
void Graphl::delVex(int oneVex)//删除顶点（清空此顶点及与此顶点连的边）
{
	if (oneVex < 0 || oneVex >= numVertex)
	{
		std::cout << "顶点范围有误" << std::endl;
		return;
	}
	for (int i = 0; i < numVertex; i++)
	{
		Node<listUnit>* temp = vexList[i].head;
		while (temp->next != NULL && temp->next->data.vertex < oneVex)
		{
			temp = temp->next;
		}
		if (temp->next == NULL)
		{
			continue;
		}
		if (temp->next->data.vertex == oneVex)
		{
			Node<listUnit>* temp2 = temp->next;
			temp->next = temp->next->next;
			delete temp2;
			OutDegree[i]--;
			numEdge--;
			continue;
		}
		if (temp->next->data.vertex > oneVex)
		{
			continue;
		}
	}
	Node<listUnit>* temp = vexList[oneVex].head;
	while (temp->next != NULL)
	{
		Node<listUnit>* temp2 = temp->next;
		temp->next = temp->next->next;
		delete temp2;
		numEdge--;
	}
	vexList[oneVex].head->next = NULL;
	InDegree[oneVex] = 0;
	OutDegree[oneVex] = 0;

}
void Graphl::print()//打印图
{
	std::cout << "打印图：" << std::endl;
	for (int i = 0; i < numVertex; i++)
	{
		std::cout << i << " : ";
		Node<listUnit>* temp = vexList[i].head;
		while (temp->next != NULL)
		{
			std::cout << temp->next->data.vertex << " ";
			temp = temp->next;
		}
		std::cout << std::endl;
	}
}
void Graphl::printWeight()//打印权重
{
	std::cout << "打印权重：" << std::endl;
	for (int i = 0; i < numVertex; i++)
	{
		std::cout << i << " : ";
		Node<listUnit>* temp = vexList[i].head;
		while (temp->next != NULL)
		{
			std::cout << temp->next->data.weight << " ";
			temp = temp->next;
		}
		std::cout << std::endl;
	}
}
void Graphl::printInDegree()//打印入度
{
	std::cout << "打印入度：" << std::endl;
	for (int i = 0; i < numVertex; i++)
	{
		std::cout << i << " : " << InDegree[i] << std::endl;
	}
}
void Graphl::printOutDegree()//打印出度
{
	std::cout << "打印出度：" << std::endl;
	for (int i = 0; i < numVertex; i++)
	{
		std::cout << i << " : " << OutDegree[i] << std::endl;
	}
}
void Graphl::DFS()//深度优先遍历
{
	std::cout << "深度优先遍历：" << std::endl;
	bool* visited = new bool[numVertex];
	for (int i = 0; i < numVertex; i++)
	{
		visited[i] = false;
	}
	for (int i = 0; i < numVertex; i++)
	{
		if (!visited[i])
		{
			DFS(i, visited);
		}
	}
	delete[] visited;
	visited = NULL;
}
void Graphl::DFS(int oneVex, bool* visited)//深度优先遍历
{
	visited[oneVex] = true;
	std::cout << oneVex << " ";
	Node<listUnit>* temp = vexList[oneVex].head;
	while (temp->next != NULL)
	{
		if (!visited[temp->next->data.vertex])
		{
			DFS(temp->next->data.vertex, visited);
		}
		temp = temp->next;
	}
}
void Graphl::BFS()//广度优先遍历
{
	std::cout << "广度优先遍历：" << std::endl;
	bool* visited = new bool[numVertex];
	for (int i = 0; i < numVertex; i++)
	{
		visited[i] = false;
	}
	for (int i = 0; i < numVertex; i++)
	{
		if (!visited[i])
		{
			BFS(i, visited);
		}
	}
	delete[] visited;
	visited = NULL;
}
void Graphl::BFS(int oneVex, bool* visited)//广度优先遍历
{
	visited[oneVex] = true;
	std::cout << oneVex << " ";
	std::queue<int> q;
	q.push(oneVex);
	while (!q.empty())
	{
		int temp = q.front();
		q.pop();
		Node<listUnit>* temp2 = vexList[temp].head;
		while (temp2->next != NULL)
		{
			if (!visited[temp2->next->data.vertex])
			{
				visited[temp2->next->data.vertex] = true;
				std::cout << temp2->next->data.vertex << " ";
				q.push(temp2->next->data.vertex);
			}
			temp2 = temp2->next;
		}
	}
}
void Graphl::DFS_for_judge_connected_graph(int oneVex)
{
	visited[oneVex] = true;
	Node<listUnit>* temp = vexList[oneVex].head;
	while (temp->next != NULL)
	{
		if (!visited[temp->next->data.vertex])
		{
			DFS_for_judge_connected_graph(temp->next->data.vertex);
		}
		temp = temp->next;
	}
}
bool Graphl::is_connected_graph()
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
			delete[] visited;
			visited = NULL;
			return false;
		}
	}
	delete[] visited;
	visited = NULL;
	return true;
}
void Graphl::MiniSpanTree_Prim()
{
	this->to_Graphm().MiniSpanTree_Prim();
}
void Graphl::MiniSpanTree_Kruskal()
{
	this->to_Graphm().MiniSpanTree_Kruskal();
}
void Graphl::ShortestPath_Dijkstra(int v0, int* Patharc, int* ShortPathTable)
{
	this->to_Graphm().ShortestPath_Dijkstra(v0, Patharc, ShortPathTable);
}
void Graphl::ShortestPath_Floyd(int** Patharc, int** ShortPathTable)
{
	this->to_Graphm().ShortestPath_Floyd(Patharc, ShortPathTable);
}
bool Graphl::TopologicalSort(std::vector<int>& path)
{
	if (!is_connected_graph())
	{
		std::cout << "该图不连通，无法进行拓扑排序" << std::endl;
		return false;
	}
	
	int* Indegree_copy = new int[numVertex];
	for (int i = 0; i < numVertex; i++)
	{
		Indegree_copy[i] = InDegree[i];
	}
	
	int count = 0;
	int* stack = new int[numVertex];
	std::vector<int>result;
	int top = -1;
	for (int i = 0; i < numVertex; i++)
	{
		if (Indegree_copy[i] == 0)
		{
			stack[++top] = i;
		}
	}
	while (top != -1)
	{
		int temp = stack[top--];
		//std::cout << temp << " ";
		result.push_back(temp);
		count++;
		Node<listUnit>* temp2 = vexList[temp].head;
		while (temp2->next != NULL)
		{
			if (--Indegree_copy[temp2->next->data.vertex] == 0)
			{
				stack[++top] = temp2->next->data.vertex;
			}
			temp2 = temp2->next;
		}
	}
	if (count < numVertex)
	{
		std::cout << "拓扑排序：有回路" << std::endl;
		delete[]stack;
		delete[]Indegree_copy;
		return false;
	}
	else
	{
		path = result;
		/*std::cout << "拓扑排序：" << std::endl;
		for (int i = 0; i < result.size(); i++)
		{
			std::cout << result[i] << " ";
		}
		std::cout << std::endl;*/
		delete[]stack;
		delete[]Indegree_copy;
		return true;
	}
	
}
bool Graphl::TopologicalSort_for_Critical_Path(int *stack2,int& top2,int*etv)
{
	if (!is_connected_graph())
	{
		std::cout << "该图不连通，无法进行拓扑排序" << std::endl;
		return false;
	}

	int* Indegree_copy = new int[numVertex];
	for (int i = 0; i < numVertex; i++)
	{
		Indegree_copy[i] = InDegree[i];
	}

	int count = 0;
	int* stack = new int[numVertex];
	std::vector<int>result;
	int top = -1;
	for (int i = 0; i < numVertex; i++)
	{
		if (Indegree_copy[i] == 0)
		{
			stack[++top] = i;
		}
	}
	
	top2 = -1;
	for (int i = 0; i < numVertex;i++)
	{
		etv[i] = 0;
	}
	
	while (top != -1)
	{
		int temp = stack[top--];
		//std::cout << temp << " ";
		result.push_back(temp);
		count++;
		
		stack2[++top2] = temp;
		
		Node<listUnit>* temp2 = vexList[temp].head;
		while (temp2->next != NULL)
		{
			if (--Indegree_copy[temp2->next->data.vertex] == 0)
			{
				stack[++top] = temp2->next->data.vertex;
			}
			if (etv[temp] + temp2->next->data.weight > etv[temp2->next->data.vertex])
			{
				etv[temp2->next->data.vertex] = etv[temp] + temp2->next->data.weight;
			}
			temp2 = temp2->next;
		}
	}
	if (count < numVertex)
	{
		std::cout << "拓扑排序：有回路" << std::endl;
		delete[]stack;
		delete[]Indegree_copy;
		return false;
	}
	else
	{
		std::cout << std::endl;
		delete[]stack;
		delete[]Indegree_copy;
		return true;
	}

}
void Graphl::CriticalPath()
{
	Node<listUnit>* e;
	int* stack2 = new int[numVertex];
	int top2 = -1;
	int* etv = new int[numVertex];
	int* ltv = new int[numVertex];
	if (!TopologicalSort_for_Critical_Path(stack2, top2, etv))
	{
		std::cout << "无法进行关键路径选取" << std::endl;
		delete[]stack2;
		delete[]etv;
		delete[]ltv;
		return;
	}
	
	int countIn = 0;
	int countOut = 0;
	for (int i = 0; i < numVertex; i++)
	{
		if (InDegree[i] == 0)
		{
			countIn++;
		}
	}
	for (int i = 0; i < numVertex; i++)
	{
		if (OutDegree[i] == 0)
		{
			countOut++;
		}
	}
	if (countIn != 1 || countOut != 1)
	{
		std::cout << "该图不是单源单汇图，无法进行关键路径选取" << std::endl;
		delete[]stack2;
		delete[]etv;
		delete[]ltv;
		return;
	}
	
	
	for (int i = 0; i < numVertex; i++)
	{
		ltv[i] = etv[numVertex - 1];
	}
	while (top2 != -1)
	{
		int temp = stack2[top2--];
		e = vexList[temp].head;
		while (e->next != NULL)
		{
			if (ltv[e->next->data.vertex] - e->next->data.weight < ltv[temp])
			{
				ltv[temp] = ltv[e->next->data.vertex] - e->next->data.weight;
			}
			e = e->next;
		}
	}
	std::cout << "关键路径：" << std::endl;
	for (int i = 0; i < numVertex; i++)
	{
		e = vexList[i].head;
		while (e->next != NULL)
		{
			int ete = etv[i];
			int lte = ltv[e->next->data.vertex] - e->next->data.weight;
			if (ete == lte)
			{
				std::cout << "顶点" << i << "到顶点" << e->next->data.vertex << "的边" << std::endl;
			}
			e = e->next;
		}
	}
	delete[]stack2;
	delete[]etv;
	delete[]ltv;
}


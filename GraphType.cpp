#include "GraphType.h"

bool NodeType::operator==(NodeType rhs)
{
	return this->index == rhs.index;
}

GraphType::GraphType()
{
}

GraphType::GraphType(int n)
{
	nodeList=new NodeType[n];

	AdjMatrix=new int* [n];
	for(int i=0;i<n;i++)
	{
		AdjMatrix[i]=new int[n];
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			int k;
			cin>>k;
			AdjMatrix[i][j]=k;
		}
	}
	for(int i=0;i<n;i++)
	{
		nodeList[i].index=i;
	}
	nodeCount=n;
}

GraphType::~GraphType()
{
}

void GraphType::setGraphType(int** adjMatrix, NodeType* node_list, int n)
{
	nodeList=new NodeType[n];

	this->AdjMatrix=new int* [n];
	for(int i=0;i<n;i++)
	{
		this->AdjMatrix[i]=new int[n];
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			this->AdjMatrix[i][j]=adjMatrix[i][j];
		}
	}
	for(int i=0;i<n;i++)
	{
		nodeList[i].index=i;
	}
	nodeCount=n;

	for(int i = 0; i < n; ++i)
	{
		this->nodeList[i].MonsterType = node_list[i].MonsterType;
	}
}

bool GraphType::IsAdjacent(NodeType first,NodeType second)
{
	vector<int> adjFirst=getAdjacent(first);//first ������ ������ ���� ������ �޾ƿ�.
	if(find(adjFirst.begin(),adjFirst.end(),second.index)!=adjFirst.end())
	{// first�� ���� ���� ���Ͽ� second�� �ִ��� �˻��ؼ� ������ true, ������ false ����
		return true;
	}
	else 
		return false;
}

int GraphType::WeightIs(NodeType first, NodeType second)
{
	if(first.index==second.index)
	{
		return 0;
	}
	else if(IsAdjacent(first,second))
	{
		return AdjMatrix[first.index][second.index];
	}
	else
		return -1;
}

NodeType* GraphType::getNodeList()
{
	return nodeList;
}

int** GraphType::getAdjMatrix()
{
	return AdjMatrix;
}

vector<int> GraphType::getAdjacent(NodeType target)
{
	vector<int> toReturn;
	for(int i=0;i<nodeCount;i++)
	{
		if(AdjMatrix[target.index][i]!=-1&&AdjMatrix[target.index][i]!=0)
		{
			toReturn.push_back(i);
		}
	}
	return toReturn;
}

NodeType GraphType::getNodeByIndex(int idx)
{
	return nodeList[idx];
}

int GraphType::getNodeCount()
{
	return nodeCount;
}


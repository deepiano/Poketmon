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

GraphType::GraphType(int** test, int n)
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
			AdjMatrix[i][j]=test[i][j];
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

bool GraphType::IsAdjacent(NodeType first,NodeType second)
{
	vector<int> adjFirst=getAdjacent(first);//first 노드의 인접한 노드 목록을 받아옴.
	if(find(adjFirst.begin(),adjFirst.end(),second.index)!=adjFirst.end())
	{// first의 인접 노드 목록에 second가 있는지 검사해서 있으면 true, 없으면 false 리턴
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

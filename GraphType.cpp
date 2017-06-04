#include "GraphType.h"

bool NodeType::operator==(NodeType rhs)
{
	return this->index == rhs.index;
}

GraphType::GraphType()
{
	nodeList=new NodeType[100];

	this->AdjMatrix=new int* [100];
	for(int i=0;i<100;i++)
	{
		this->AdjMatrix[i]=new int[100];
	}
	vector<int> temp;
	for(int i=0;i<12;i++)
	{
		this->mappingTable.push_back(temp);
	}
	for(int i=0;i<100;i++)
	{
		this->nodeList[i].index=i;
	}
	nodeList[0].MonsterType=0;
	nodeCount=100;

	load_file();
	
	this->mappingTable.resize(12);

	MakeMappingTable();
}

void GraphType::load_file()
{
	ifstream placeFile;
	placeFile.open("Data/place.txt");
	if(!placeFile)
	{
		cerr << "Error opening place.txt" << endl;
		exit(100);
	}

	string str;
	std::getline(placeFile, str);
	for(int i = 0; i <= 100; ++i)
	{
		int num;
		placeFile>>num;
		this->nodeList[i].MonsterType=num;
		//>> this->nodeList[i].x >> this->nodeList[i].y;
	}

	placeFile.close();

	ifstream weightFile;
	weightFile.open("Data/weight.txt");
	if(!weightFile)
	{
		cerr << "Error opening weight.txt" << endl;
		exit(100);
	}

	for(int i = 0; i < 100; ++i)
	{
		for(int j = 0; j < 100; ++j)
		{
			int num;
			weightFile >>num;
			this->AdjMatrix[i][j]=num;
		}
	}
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
	this->mappingTable.resize(12);
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
		this->nodeList[i].index=i;
	}
	nodeCount=n;

	for(int i = 0; i < n; ++i)
	{
		this->nodeList[i].MonsterType = node_list[i].MonsterType;
	}

	this->mappingTable.resize(12);

	MakeMappingTable();
}

bool GraphType::IsAdjacent(NodeType first,NodeType second)
{
	vector<int> adjFirst=getAdjacent(first);
	if(find(adjFirst.begin(),adjFirst.end(),second.index)!=adjFirst.end())
	{
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

void GraphType::AddToAdj(int num, int row, int col)
{
    *(*(AdjMatrix+row)+col)=num;
}

void GraphType::AddNodeToMpTable(NodeType nod)
{
    mappingTable[nod.MonsterType].push_back(nod.index);
}

void GraphType::ChangeNodeType(int idx, int type)
{
    nodeList[idx].MonsterType=type;
}
void GraphType::MakeMappingTable()
{
    for(int i=0;i<nodeCount;i++)
    {
        AddNodeToMpTable(nodeList[i]);
    }
}

vector<vector<int>> GraphType::getMap()
{
	return mappingTable;
}

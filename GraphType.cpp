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
/*
 loadInputfile();
    loadPlacefile();
    g->MakeMappingTable();//Main함수에서의 파일 로드 및 초기화방식
    */
/*
void MainWindow::loadInputfile()
{

    QFile file("input.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
       return;
    }
    QTextStream in(&file);
    QString inp;
    while(!in.atEnd())
    {
        for(int i=0;i<g->getNodeCount();i++)
        {
            for(int j=0;j<g->getNodeCount();j++)
            {
                 in>>inp;
                 g->AddToAdj(inp.toInt(),i,j);
            }
        }


    }
    file.close();
}

void MainWindow::loadPlacefile()
{
    QFile file("placeinput.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return;
    }
    QTextStream in(&file);
    QString nodnum;
    QString montype;
    while(!in.atEnd())
    {
        in>>nodnum;
        in>>montype;
        g->ChangeNodeType(nodnum.toInt(),montype.toInt());

    }
    file.close();
}
*/

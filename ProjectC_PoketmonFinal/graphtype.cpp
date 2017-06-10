#include "graphtype.h"
//매핑 테이블(어느 노드에 어느 포켓몬이 있는가) 추가!
//그래프의 입력 단계에서 매핑 테이블 바로 생성할 수 있도록 할 것.
GraphType::GraphType()
{

}
bool NodeType::operator==(NodeType rhs)
{
    return this->index == rhs.index;
}
GraphType::GraphType(int n)
{
    NodeType nod;
    nod.MonsterType=0;
    nodeCount=n;
    AdjMatrix=new int*[n];
    for(int i=0;i<n;i++)
    {
        AdjMatrix[i]=new int[n];
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            AdjMatrix[i][j]=0;
        }
    }
    for(int i=0;i<n;i++)
    {
        nod.index=i;
        nod.x=0;
        nod.y=0;
        nodeList.push_back(nod);
    }

    for(int i=0;i<12;i++)
    {
        QVector<int> newV;
        mappingTable.push_back(newV);
    }
}

GraphType::GraphType(int **test, int n)
{

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

bool GraphType::IsAdjacent(int first, int second)
{
    QVector<int> adjFirst=getAdjacent(first);

}

int GraphType::WeightIs(int first, int second)
{
    if(first==second)
    {
        return 0;
    }
    else if(IsAdjacent(first,second))
    {
        return AdjMatrix[first][second];
    }
    else
    {
        return -1;
    }
}

QVector<NodeType> GraphType::getNodeList()
{
    return nodeList;
}

int** GraphType::getAdjmatrix()
{
    return AdjMatrix;
}

QVector<int> GraphType::getAdjacent(int target)
{
    QVector<int> toReturn;
    for(int i=0;i<nodeCount;i++)
    {
        if(AdjMatrix[target][i]!=-1&&AdjMatrix[target][i]!=0)
        {
            toReturn.push_back(i);
        }
    }
    return toReturn;
}


int GraphType::getNodeCount()
{
    return nodeCount;
}

void GraphType::AddToAdj(int num, int row, int col)
{
    AdjMatrix[row][col]=num;
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

NodeType GraphType::getNodeByIndex(int idx)
{
    return nodeList[idx];
}

QVector<QVector<int>>GraphType::getMap()
{
    return mappingTable;
}

void GraphType::ChangeNodePos(int idx, double x, double y)
{
    nodeList[idx].x=x;
    nodeList[idx].y=y;
}

bool GraphType::operator =(GraphType g)
{
    this->nodeCount=g.nodeCount;
    this->nodeList=g.nodeList;
    this->AdjMatrix=g.AdjMatrix;
    this->mappingTable=g.mappingTable;
}

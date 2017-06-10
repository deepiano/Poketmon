#ifndef _GRAPHTYPE_H_
#define _GRAPHTYPE_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;



struct NodeType 
{
	int MonsterType;
	int index;
	double x;
	double y; 
	bool operator==(NodeType rhs);
};

struct Route
{
	vector<NodeType> route;
	int time;
	int num_catch_poketmon;
};

class GraphType
{
private:
	NodeType* nodeList;// �׷����� ���� ��ü ������ ����Ʈ.
	int** AdjMatrix;// �׷����� ���� ���¸� ��Ÿ���� ��������.
	int nodeCount;// �׷����� ���� ���� ��.
	vector< vector<int> > mappingTable;

public:
	GraphType();
	void load_file();
	GraphType(int n);
	GraphType(int** adjMatrix, NodeType* node_list, int n);
	
	~GraphType();

	void setGraphType(int** adjMatrix, NodeType* node_list, int n);


	bool IsAdjacent(NodeType first, NodeType second);
	int WeightIs(NodeType first,NodeType second);
	vector<int> getAdjacent(NodeType target);

	NodeType* getNodeList();
	NodeType getNodeByIndex(int idx);
	int** getAdjMatrix();
	int getNodeCount();
	
	void AddToAdj(int num,int row,int col);// AdjMatrix[row][col]�� ��� num��� ���. �ٸ� ������ �� ��� ���� ã��� ��� ���.
    void AddNodeToMpTable(NodeType nod);// Mapping Table�� ��� �߰�
    void ChangeNodeType(int idx,int type);//nodeList�� idx �ε����� Ÿ��� type��� ����
    void MakeMappingTable();//Mapping Table� ����� �Լ�� AddNodeToMpTable� ȣ���� ���.

	vector<vector<int>> getMap();
};

#endif


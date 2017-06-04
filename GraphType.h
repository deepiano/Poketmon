#pragma once

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
	NodeType* nodeList;
	int** AdjMatrix;
	int nodeCount;
	vector<vector<int>> mappingTable;

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
	
	void AddToAdj(int num,int row,int col);// AdjMatrix[row][col]의 값을 num으로 설정. 다른 인접행렬 값 설정 방법을 찾으면 제거 예정.
    void AddNodeToMpTable(NodeType nod);// Mapping Table에 노드 추가
    void ChangeNodeType(int idx,int type);//nodeList의 idx 인덱스의 타입을 type으로 변경
    void MakeMappingTable();//Mapping Table을 만드는 함수로 AddNodeToMpTable을 호출해 사용.

	vector<vector<int>> getMap();
};


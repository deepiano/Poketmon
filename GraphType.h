//GraphType. h
#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// struct NodeType은 각 그래프의 노드 형태를 정의하는 구조체이다.
struct NodeType 
{
	int MonsterType; // 각 노드의 타입. 0~11까지 존재하며, 0은 시작점, 11은 포켓스탑과 같이 특정 번호는 특정 지점을 나타냄.
	int index;// 노드의 번호이자 인접행렬에서의 인덱스 번호.
	bool operator==(NodeType rhs);
};

class GraphType
{
private:
	NodeType* nodeList;// 그래프가 가진 전체 노드의 리스트.
	int** AdjMatrix;// 그래프의 연결 상태를 나타내는 인접행렬.
	int nodeCount;// 그래프의 현재 노드 수.

public:
	GraphType();
	GraphType(int n);// 원하는 노드 수를 입력해 그래프를 생성하는 생성자.
	GraphType(int** test, int n);
	~GraphType();

	bool IsAdjacent(NodeType first, NodeType second);// 두 노드가 인접해 있는지 체크.
	int WeightIs(NodeType first,NodeType second);// 두 노드 사이의 가중치(여기서는 소요 시간)를 체크
	vector<int> getAdjacent(NodeType target);// 특정 노드와 인접해 있는 모든 노드를 벡터에 담아 리턴

	NodeType* getNodeList();// 모든 노드 리스트 리턴
	//NodeType getNodeByIndex(int idx);// 인덱스를 받아 해당 인덱스의 노드 리턴.
	int** getAdjMatrix();// 인접행렬 리턴.
	int getNodeCount();//현재 노드 수 리턴.
};

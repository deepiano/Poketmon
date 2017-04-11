#ifndef _GRAPHTYPE_H_
#define _GRAPHTYPE_H_

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// struct NodeType�� �� �׷����� ���� ���¸� �����ϴ� ����ü�̴�.
struct NodeType 
{
	int MonsterType; // �� ������ Ÿ��. 0~11���� �����ϸ�, 0�� ������, 11�� ���Ͻ�ž�� ���� Ư�� ��ȣ�� Ư�� ������ ��Ÿ��.
	int index;// ������ ��ȣ���� �������Ŀ����� �ε��� ��ȣ.
	bool operator==(NodeType rhs);
};

class GraphType
{
private:
	NodeType* nodeList;// �׷����� ���� ��ü ������ ����Ʈ.
	int** AdjMatrix;// �׷����� ���� ���¸� ��Ÿ���� ��������.
	int nodeCount;// �׷����� ���� ���� ��.
	vector<vector<int>> mappingTable;

public:
	GraphType();
	GraphType(int n);// ���ϴ� ���� ���� �Է��� �׷����� �����ϴ� ������.
	GraphType(int** adjMatrix, NodeType* node_list, int n);
	~GraphType();

	void setGraphType(int** adjMatrix, NodeType* node_list, int n);

	bool IsAdjacent(NodeType first, NodeType second);// �� ���尡 ������ �ִ��� üũ.
	int WeightIs(NodeType first,NodeType second);// �� ���� ������ ����ġ(���⼭�� �ҿ� �ð�)�� üũ
	vector<int> getAdjacent(NodeType target);// Ư�� ������ ������ �ִ� ���� ���带 ���Ϳ� ���� ����

	NodeType* getNodeList();// ���� ���� ����Ʈ ����
	NodeType getNodeByIndex(int idx);// �ε����� �޾� �ش� �ε����� ���� ����.
	int** getAdjMatrix();// �������� ����.
	int getNodeCount();//���� ���� �� ����.
	
	void AddToAdj(int num,int row,int col);// AdjMatrix[row][col]의 값을 num으로 설정. 다른 인접행렬 값 설정 방법을 찾으면 제거 예정.
    void AddNodeToMpTable(NodeType nod);// Mapping Table에 노드 추가
    void ChangeNodeType(int idx,int type);//nodeList의 idx 인덱스의 타입을 type으로 변경
    void MakeMappingTable();//Mapping Table을 만드는 함수로 AddNodeToMpTable을 호출해 사용.

	vector<vector<int>> getMap();
};

#endif

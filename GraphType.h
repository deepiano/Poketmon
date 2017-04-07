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

};
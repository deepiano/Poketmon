#ifndef GRAPHTYPE_H
#define GRAPHTYPE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QVector>
#include <iostream>
#include <algorithm>
#include <QPushButton>
#include <QLineEdit>


using namespace std;

struct NodeType
{
    int MonsterType;
    int index;
    double x;
    double y;
    bool operator==(NodeType rhs);

};

class GraphType
{
public:
    GraphType();
    GraphType(int n);
    GraphType(int** test, int n);
    ~GraphType();

    QVector<NodeType> getNodeList();
    int** getAdjmatrix();
    int getNodeCount();
    QVector<int> getAdjacent(int target);//vector를 Qt 타입인 QVector로 대체
    int WeightIs(int first, int second);
    bool IsAdjacent(int first, int second);
    void AddToAdj(int num,int row,int col);// AdjMatrix[row][col]의 값을 num으로 설정. 다른 인접행렬 값 설정 방법을 찾으면 제거 예정.
    void AddNodeToMpTable(NodeType nod);// Mapping Table에 노드 추가
    void ChangeNodeType(int idx,int type);//nodeList의 idx 인덱스의 타입을 type으로 변경
    void MakeMappingTable();//Mapping Table을 만드는 함수로 AddNodeToMpTable을 호출해 사용.
    NodeType getNodeByIndex(int idx);
    QVector<QVector<int>> getMap();
    void ChangeNodePos(int idx,double x, double y);
    bool operator =(GraphType g);

private:
    QVector<NodeType> nodeList;
    int** AdjMatrix;
    int nodeCount;
    QVector<QVector<int>> mappingTable;

};
#endif // GRAPHTYPE_H

#ifndef SELECTALGORITHM_H
#define SELECTALGORITHM_H
#include <QVector>
#include <QString>
#include <QVariant>
#include <iostream>
#include <QTextStream>
#include "graphtype.h"
#include "shortestpath.h"
using namespace std;
struct Route
{
    QVector<NodeType> route;
    int time;
    int num_catch_poketmon;

};
class SelectAlgorithm
{
public:
    SelectAlgorithm();
    virtual  QVector<QString> FindRoute()=0;
    virtual void SetProblem(QVector<int>data)=0;
    virtual void SetGraph(GraphType* gr);
    int getAlgnum();
protected:
    GraphType* g;
    int algNum;
};

#endif // SELECTALGORITHM_H

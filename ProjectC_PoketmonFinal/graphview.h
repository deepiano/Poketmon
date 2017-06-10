#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QObject>
#include <QGraphicsScene>
#include <QColor>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QPair>
#include <QPainter>
#include <QGraphicsItem>
struct GNodeType
{
    qreal x;
    qreal y;
    int type;
    int idx;
};

class GraphView : public QGraphicsScene
{
public:
    GraphView();
    void addNode(GNodeType n);
    void addEdge();
    void setColor(int t);
    QVector<GNodeType> getNodeList();
    void addPathList(QVector<QString>);


private:
    QVector<QVector<int>> adj;
    QVector<GNodeType> nodeList;
    QVector<QString> pathList;
    QColor col;

};

#endif // GRAPHVIEW_H

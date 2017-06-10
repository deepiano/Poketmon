#include "graphview.h"

GraphView::GraphView()
{
    QVector<QString> p;
    pathList=p;
     QVector<int> temp;
    for(int i=0;i<100;i++)
    {
       adj.push_back(temp);
}
    GNodeType n;
    QFile typeFile("Type.txt");
    if(!typeFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return;
    }
    QTextStream in2(&typeFile);
    QString inT;
    while(!in2.atEnd())
    {
        in2>>inT;
        n.type=inT.toInt();
        nodeList.push_back(n);

    }
    typeFile.close();
    QFile adjFile("Adj.txt");
    if(!adjFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return;
    }
    QTextStream in(&adjFile);
    QString inp;
    while(!in.atEnd())
    {
        for(int i=0;i<100;i++)
        {
            for(int j=0;j<100;j++)
            {
                in>>inp;
                adj[i].push_back(inp.toInt());
            }
        }

    }
    adjFile.close();

    QFile placeFile("Pos.txt");
    if(!placeFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return;
    }
    QTextStream in3(&placeFile);
    QString inX;
    QString inY;
    while(!in3.atEnd())
    {
        for(int i=0;i<100;i++)
        {
            in3>>inX>>inY;
            nodeList[i].x=inX.toDouble();
            nodeList[i].y=inY.toDouble();
        }
    }
    placeFile.close();
    for(int i=0;i<nodeList.size();i++)
    {
        nodeList[i].idx=i;
        addNode(nodeList[i]);
    }
    addEdge();
}


void GraphView::addNode(GNodeType n)
{
    qreal a=n.x*30;
    qreal b=n.y*30;
    setColor(n.type);
    this->addEllipse(a,b,20,20,QPen(Qt::transparent),QBrush(col));
    int num=n.idx;
    QString lab=QString("%1").arg(num);
    QGraphicsTextItem* txt=this->addText(lab);
    txt->setPos(a,b+3);
    if(col==Qt::darkBlue||col==Qt::black||col==Qt::blue)
    {
        txt->setDefaultTextColor(Qt::white);
    }

}

void GraphView::addEdge()
{
    if(pathList.size()!=0)
    {
        for(int i=0;i<100;i++)
        {
            for(int j=0;j<100;j++)
            {
                if(adj[i][j]>0)
                {
                    QGraphicsLineItem* l=this->addLine(nodeList[i].x*30+10,nodeList[i].y*30+10,nodeList[j].x*30,nodeList[j].y*30,QPen(Qt::black));
                    l->setZValue(-1);
                }
            }
        }
        QString path=pathList[0];
        QStringList road=path.split(" ");
        QVector<int> introad;
        for(int i=0;i<road.length();i++)
        {
            QString t=road[i];
            introad.push_back(t.toInt());
        }//그림그리는 방법 칮기!
        QVector<QPair<int,int>> edgeNodes;
        for(int i=0;i<introad.size()-1;i++)
        {
            QPair<int,int> temp;
            temp.first=introad[i];
            temp.second=introad[i+1];
            edgeNodes.push_back(temp);
        }
        for(int i=0;i<edgeNodes.size();i++)
        {
            QPair<int,int> cur=edgeNodes[i];
            QGraphicsLineItem* l=this->addLine(nodeList[cur.first].x*30+10,nodeList[cur.first].y*30+10,nodeList[cur.second].x*30,nodeList[cur.second].y*30,QPen(Qt::magenta,3));
            l->setZValue(-1);
        }
    }
    else
    {
        for(int i=0;i<100;i++)
        {
            for(int j=0;j<100;j++)
            {
                if(adj[i][j]>0)
                {
                    QGraphicsLineItem* l=this->addLine(nodeList[i].x*30+10,nodeList[i].y*30+10,nodeList[j].x*30,nodeList[j].y*30,QPen(Qt::black));
                    l->setZValue(-1);
                }
            }
        }
    }
}

void GraphView::setColor(int t)
{
    switch(t)
    {
    case 0:
        col=Qt::gray;
        break;
    case 1:
        col=Qt::yellow;
        break;
    case 2:
        col=Qt::red;
        break;
    case 3:
        col=Qt::blue;
        break;
    case 4:
        col=Qt::green;
        break;
    case 5:
        col=Qt::cyan;
        break;
    case 6:
        col=Qt::magenta;
        break;
    case 7:
        col=Qt::darkCyan;
        break;
    case 8:
        col=Qt::darkBlue;
        break;
    case 9:
        col=Qt::darkYellow;
        break;
    case 10:
        col=Qt::darkMagenta;
        break;
    case 11:
        col=Qt::black;
        break;

    }

}


QVector<GNodeType> GraphView::getNodeList()
{
    return nodeList;
}

void GraphView::addPathList(QVector<QString> p)
{
    pathList=p;
}

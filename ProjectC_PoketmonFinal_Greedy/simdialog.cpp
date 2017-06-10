#include "simdialog.h"

SimDialog::SimDialog()
{
    this->setWindowTitle("Result Simulation");
    this->setGeometry(350,25,700,700);
    g=new GraphView;
    view=new QGraphicsView(g);

    QLayout* layout=new QVBoxLayout();
    layout->addWidget(view);
    this->setLayout(layout);
    view->show();
}

SimDialog::SimDialog(QVector<QString> in)
{
    this->setWindowTitle("Result Simulation");
    this->setGeometry(350,25,700,700);
    g=new GraphView;
    setpathList(in);
    g->addEdge();
    view=new QGraphicsView(g);

    QLayout* layout=new QVBoxLayout();
    layout->addWidget(view);
    this->setLayout(layout);
    view->show();


}

void SimDialog::setpathList(QVector<QString> p)
{
    g->addPathList(p);
}

#ifndef SIMDIALOG_H
#define SIMDIALOG_H
#include <QDialog>
#include <QGraphicsView>
#include <QVector>
#include <QLayout>
#include "graphview.h"

class SimDialog : public QDialog
{
public:
    SimDialog();
    SimDialog(QVector<QString> in);
    void setpathList(QVector<QString> p);
private:
    GraphView* g;
    QGraphicsView* view;
};

#endif // SIMDIALOG_H

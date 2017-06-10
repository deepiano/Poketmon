#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMainWindow>
#include "graphtype.h"
#include <QDataStream>
#include <QTextStream>
#include <QIODevice>
#include <QFile>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QStringList>
#include <QItemDelegate>
#include <QLayoutItem>
#include <QTableWidgetItem>
#include <QMainWindow>
#include <QInputDialog>
#include <QMessageBox>
#include <QDir>
#include "selectionwindow.h"
#include "selectalgorithm.h"
#include "specificmonscatch.h"
#include "everymonscatch.h"
#include "manymonscatch.h"
#include "graphview.h"
#include "simdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    GraphType* getg()
    {
        return g;
    }
    void SelectAlg(int n);

private slots:

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_activated(int index);

    void on_pushButton_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    SelectionWindow* s;
    GraphType* g;
    void loadInputfile();
    void loadPlacefile();
    void loadTypefile();
    SelectAlgorithm* alg;
    SimDialog* sim;
    QVector<QString> res;

};

#endif // MAINWINDOW_H

#ifndef SELECTIONWINDOW_H
#define SELECTIONWINDOW_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QVector>
class SelectionWindow : public QDialog
{
public:
    SelectionWindow();
    QVector<int> getVal();
    void AdjustByIdx(int idx);
    void setAlgId(int id);
private slots:

private:
    QLineEdit* one;
    QComboBox* combo;
    QPushButton* ok;
    QPushButton* cancel;
    QLabel* time;
    QLabel* type;
    int algId;


};

#endif // SELECTIONWINDOW_H

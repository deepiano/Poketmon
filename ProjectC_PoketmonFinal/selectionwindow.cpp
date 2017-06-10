#include "selectionwindow.h"

SelectionWindow::SelectionWindow()
{
    algId=0;
    time=new QLabel;
    time->setText("시간");
    type=new QLabel;
    type->setText("포켓몬");
    one=new QLineEdit;
    combo=new QComboBox(this);
    combo->addItem("피카츄");
    combo->addItem("라이츄");
    combo->addItem("파이리");
    combo->addItem("꼬부기");
    combo->addItem("버터플");
    combo->addItem("야도란");
    combo->addItem("피죤투");
    combo->addItem("또가스");
    combo->addItem("잠만보");
    combo->addItem("리자몽");
    ok=new QPushButton;
    cancel=new QPushButton;
    ok->setText("ok");
    cancel->setText("cancel");
    QHBoxLayout* hlay1=new QHBoxLayout();
    hlay1->addWidget(time);
    hlay1->addWidget(one);
    QHBoxLayout* hlay2=new QHBoxLayout();
    hlay2->addWidget(type);
    hlay2->addWidget(combo);
    QHBoxLayout* hlay3=new QHBoxLayout();
    hlay3->addWidget(ok);
    hlay3->addWidget(cancel);
    QVBoxLayout* vlay=new QVBoxLayout();
    vlay->addLayout(hlay1);
    vlay->addLayout(hlay2);
    vlay->addLayout(hlay3);
    setLayout(vlay);
    connect(ok,SIGNAL(clicked()),this,SLOT(accept()));
    connect(cancel,SIGNAL(clicked()),this,SLOT(reject()));
}

QVector<int> SelectionWindow::getVal()
{
    QVector<int> toret;
    toret.push_back(0);
    toret.push_back(0);
    if(algId==0)
    {
        int time=this->one->text().toInt();
        toret[0]=time;
        toret[1]=this->combo->currentIndex()+1;
    }
    else if(algId==1)
    {
        int time=this->one->text().toInt();
        toret[0]=time;
    }
    return toret;
}

void SelectionWindow::AdjustByIdx(int idx)
{
    if(idx==0)
    {
        algId=0;
        combo->show();
        type->show();
    }
    else if(idx==1)
    {
        algId=1;
        combo->hide();
        type->hide();
    }
}

void SelectionWindow::setAlgId(int id)
{
    algId=id;
}

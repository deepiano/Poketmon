#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    alg=NULL;
    g=new GraphType(100);
    ui->setupUi(this);
    this->setWindowTitle("PoketmonGO Simulator");
    this->setStyleSheet("background-color: aliceblue");
    ui->lineEdit->setStyleSheet("background-color: white");
    ui->lineEdit_2->setStyleSheet("background-color:  white");
    ui->pushButton->setStyleSheet("background-color: #B6C8EF");
    ui->pushButton_2->setStyleSheet("background-color: #B6C8EF");
    ui->pushButton_3->setStyleSheet("background-color: #B6C8EF");
    ui->comboBox->setStyleSheet("background-color: white");
    ui->textEdit->setStyleSheet("background-color:white");
    ui->lineEdit_3->setStyleSheet("background-color: white");
    ui->lineEdit_4->setStyleSheet("background-color: white");
    ui->lineEdit_5->setStyleSheet("background-color: white");
    ui->textBrowser->setStyleSheet("background-color:aliceblue");
    ui->textBrowser->setStyleSheet("border: 1px solid transparent");
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_3->setReadOnly(true);
    ui->lineEdit_4->setReadOnly(true);
    ui->lineEdit_5->setReadOnly(true);
    ui->textEdit->setReadOnly(true);
    loadInputfile();
    loadPlacefile();
    loadTypefile();
    g->MakeMappingTable();
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_clicked(bool)),Qt::UniqueConnection);
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(on_pushButton_2_clicked()),Qt::UniqueConnection);
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(on_pushButton_3_clicked()),Qt::UniqueConnection);
    s=new SelectionWindow;
    sim=new SimDialog;
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_3_clicked()
{
    if(alg==NULL)
    {
        QMessageBox msg;
        msg.setText("문제를 먼저 선택해 주세요!");
        msg.exec();
    }
    else
    {
    res=alg->FindRoute();

    if(res.size()==3)
    {
    QString type=ui->lineEdit_2->text();
    ui->lineEdit_3->setText(type);
    ui->textEdit->setText(res[0]);
    ui->lineEdit_5->setText(res[2]);
    ui->lineEdit_4->setText(res[1]);
    }
    else
    {
        ui->lineEdit_3->setText(res[3]);
        ui->textEdit->setText(res[0]);
        ui->lineEdit_5->setText(res[2]);
        ui->lineEdit_4->setText(res[1]);
    }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    sim=new SimDialog(res);
    sim->show();
}
void MainWindow::loadInputfile()
{
    QFile file("Adj.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
       return;
    }
    QTextStream in(&file);
    QString inp;
    while(!in.atEnd())
    {
        for(int i=0;i<g->getNodeCount();i++)
        {
            for(int j=0;j<g->getNodeCount();j++)
            {
                 in>>inp;
                 g->AddToAdj(inp.toInt(),i,j);
            }
        }


    }
    file.close();
}
void MainWindow::loadPlacefile()
{
    QFile file("Pos.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return;
    }
    QTextStream in(&file);
    double x,y;
    while(!in.atEnd())
    {
        for(int i=0;i<g->getNodeCount();i++)
        {
        in>>x;
        in>>y;
        g->ChangeNodePos(i,x,y);
        }

    }
    file.close();
}
void MainWindow::loadTypefile()
{
    QFile typeFile("Type.txt");
    if(!typeFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return;
    }
    QTextStream in2(&typeFile);
    int inT;
    while(!in2.atEnd())
    {
        for(int i=0;i<g->getNodeCount();i++)
        {
            in2>>inT;
            g->ChangeNodeType(i,inT);

        }
    }
    typeFile.close();
}

void MainWindow::SelectAlg(int n)
{
    switch(n)
    {
    case 0:
    {
        delete alg;
        alg=new SpecificMonsCatch;
        alg->SetGraph(g);
        break;
    }
    case 1:
    {
        delete alg;
        alg=new ManyMonsCatch;
        alg->SetGraph(g);
        break;
    }
    case 2:
    {
        delete alg;
        alg=new EveryMonsCatch;
        alg->SetGraph(g);
        break;
    }
    }
}

void MainWindow::on_comboBox_activated(int index)
{
    SelectAlg(index);//콤보박스(문제선택)
    switch(index)
    {

    case 0:
    {
        ui->pushButton->show();
        QString st="제한 시간 내에 지정한 타입의 포켓몬을 최대한 잡는 경로를 찾습니다.";
        ui->textBrowser->setText(st);
        s->AdjustByIdx(index);
        ui->lineEdit->setDisabled(false);
        ui->lineEdit_2->setDisabled(false);
        break;
    }
    case 1:
    {
        ui->pushButton->show();
        QString st="제한 시간 내에 최대한 많은 수의 포켓몬을 잡는 경로를 찾습니다.";
        ui->textBrowser->setText(st);
        ui->lineEdit_2->setDisabled(true);
        ui->lineEdit_3->setDisabled(true);
        s->AdjustByIdx(index);
        break;
    }
    case 2:
        ui->pushButton->hide();
        QString st="최소 시간에 모든 타입의 포켓몬을 잡는 경로를 찾습니다.";
        ui->textBrowser->setText(st);
        QVector<int> tmp;
        alg->SetProblem(tmp);
        ui->lineEdit->setDisabled(true);
        ui->lineEdit_2->setDisabled(true);
        ui->lineEdit_3->setDisabled(false);
        break;
    }
}

void MainWindow::on_pushButton_clicked(bool checked)

{
    if(!checked)
    {
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        if(alg==NULL)
        {
            QMessageBox msg;
            msg.setText("문제를 먼저 선택해 주세요!");
            msg.exec();
        }
        else
        {
            //int idx=alg->getAlgnum();
            //s.AdjustByIdx(idx);
            s->setAlgId(alg->getAlgnum());
            int a=s->exec();
            QVector<int> val;
            val.push_back(200);
            val.push_back(1);
            if(a==QDialog::Accepted)
            {
                val=s->getVal();
                if(val.size()==1)
                    val.push_back(1);
                QString time=QString::number(val[0]);
                ui->lineEdit->setText(time);
                switch(val[1])
                {
                case 1:
                {
                    ui->lineEdit_2->setText("피카츄");
                    break;
                }
                case 2:
                {
                    ui->lineEdit_2->setText("라이츄");
                    break;
                }
                case 3:
                {
                    ui->lineEdit_2->setText("파이리");
                    break;
                }
                case 4:
                {
                    ui->lineEdit_2->setText("꼬부기");
                    break;
                }
                case 5:
                {
                    ui->lineEdit_2->setText("버터플");
                    break;
                }
                case 6:
                {
                    ui->lineEdit_2->setText("야도란");
                    break;
                }
                case 7:
                {
                    ui->lineEdit_2->setText("피죤투");
                    break;
                }
                case 8:
                {
                    ui->lineEdit_2->setText("또가스");
                    break;
                }
                case 9:
                {
                    ui->lineEdit_2->setText("잠만보");
                    break;
                }
                case 10:
                {
                    ui->lineEdit_2->setText("리자몽");
                    break;
                }
                };
            }
            alg->SetProblem(val);
            return;
        }

    }
}

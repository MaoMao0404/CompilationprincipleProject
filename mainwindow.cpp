#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
#include<bits/stdc++.h>
#include "nfadfa.h"
#include <QDir>
#include <QFileInfo>
#include<QCoreApplication>
#include<QProcess>
#include<QString>
#include<QDebug>
#include <QPixmap>
#include <vector>
#include <QFileDialog>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

int chars(string s)
{
    int n=0;
    for(int i=0; i<int(s.size());i++)
    {
        if((s[i]>=48 && s[i]<=57)||(s[i]>=65 && s[i]<=90)
                ||(s[i]>=97 && s[i]<=122))
            n++;
    }
    return n;
}

void MainWindow::on_Button1_clicked()
{
    ui->label_3->clear();
    nfadfa NFA;
    string zzz;
    QString text = ui->textEdit->toPlainText();
    string s = text.toStdString();
    //将正则表达式转化为nfa
    s = NFA.insert_concat(s);
    s = NFA.regexp_to_postfix(s);
    NFA.postfix_to_nfa(s);
    //将nfa转化为dfa
    set<int> si;
    NFA.nfa_to_dfa(si);
    //最小化dfa
    NFA.minimize_dfa();

    QString z = QCoreApplication::applicationDirPath();
    zzz = z.toStdString();

    NFA.show_nfa(zzz);
    NFA.show_dfa(zzz);
    NFA.show_mini_dfa(zzz);


}

void MainWindow::on_Button2_clicked()
{
    //创建进程执行命令，根据dot.txt文件画出png图并保存在其目录下
    system("dot -Tpng ./debug/graph/nfa.dot -o ./debug/graph/nfa.png");
    //将生成的nfa图展示出来
    QPixmap image;
    image.load("./debug/graph/nfa.png");
    ui->label_3->clear();
    ui->label_3->setPixmap(image);
    ui->label_3->show();

}

void MainWindow::on_Button3_clicked()
{
    system("dot -Tpng ./debug/graph/dfa.dot -o ./debug/graph/dfa.png");
    //将生成的dfa图展示出来
    QPixmap image;
    image.load("./debug/graph/dfa.png");
    ui->label_3->clear();
    ui->label_3->setPixmap(image);
    ui->label_3->show();

}

void MainWindow::on_Button4_clicked()
{
     system("dot -Tpng ./debug/graph/mini_dfa.dot -o ./debug/graph/mini_dfa.png");
    //将生成的dfa图展示出来
    QPixmap image;
    image.load("./debug/graph/mini_dfa.png");
    ui->label_3->clear();
    ui->label_3->setPixmap(image);
    ui->label_3->show();
}

void MainWindow::on_Button4_2_clicked()
{
    ifstream in("Ccode.txt");
    string content;

    while (getline (in, content))
    {
        QString  content_1=QString::fromStdString(content);

    }

}

void MainWindow::on_pushButton_clicked()
{
    QString file = QFileDialog::getOpenFileName(
                this, tr("open image file"),
                "./", tr("Txt files(*.txt);;All files (*.*)"));
    string filepath = file.toStdString();
    cout<<filepath<<endl;
    string content;
    ifstream in(filepath);
    if(in)
    {
        ui->textEdit->clear();
        while (getline (in, content))
        {
            QString  content_1=QString::fromStdString(content);
            ui->textEdit->append(content_1);
        }
    }
    else{
        cout<<"error";
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ofstream out("re.txt");
    QString text = ui->textEdit->toPlainText();
    string s = text.toStdString();
    out<<s;
    out.close();
}

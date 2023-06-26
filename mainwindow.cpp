#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <fstream>
#include <iostream>
#include <QMessageBox>
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
//打开文件
void MainWindow::on_pushButton_clicked()
{
    ui->textEdit->clear();
    fileName = QFileDialog::getOpenFileName(this,QStringLiteral("打开文件"),"F:",QStringLiteral("c++语言文件(*c *cpp *h)"));

    ifstream infile(fileName.toStdString().c_str(),ios::in);
    char chTemp[256]={0};
    while(infile.getline(chTemp,256))
    {
        chTemp[strlen(chTemp)]='\n';
        ui->textEdit->insertPlainText(QString(chTemp));
        memset(chTemp,0,sizeof(chTemp));
    }

}
//压缩文件
void MainWindow::on_pushButton_2_clicked()
{
    ifstream infile(fileName.toStdString().c_str(),ios::in);
    ofstream outFile("compress.data",ios::out);
    char chTemp[2560]={0};
    p_trie = create_node(' ') ;
    //insert_trie(p_trie,7);
    while(infile.getline(chTemp,2560))
    {
        QString strTemp(chTemp);
        QStringList strList = strTemp.split(" ",QString::SkipEmptyParts);
        QStringListIterator strIterator(strList);
          while (strIterator.hasNext())
          {
                QString strTemp = strIterator.next();
                insert_trie(p_trie,strTemp.toStdString().c_str());
                outFile<<strTemp.toStdString().at(strTemp.size()-1)<<" "<<QString::number(strTemp.size()).toStdString()<<endl;
          }
          //插入换行标识
          char backch = 7;
          outFile<<backch<<" "<<1<<endl;

        memset(chTemp,0,sizeof(chTemp));
    }
    QMessageBox::warning(this,"提示","压缩完成，输出文件：compress.data");
}
//查看压缩结果
void MainWindow::on_pushButton_3_clicked()
{

    ui->textEdit->clear();
    fileName1 = QFileDialog::getOpenFileName(this,QStringLiteral("打开文件"),"F:",QStringLiteral("压缩文件(*data)"));

    ifstream infile(fileName1.toStdString().c_str(),ios::in);
    char chTemp[256]={0};
    char ch=0;
    int pos;
    while(infile.getline(chTemp,256))
    {
        sscanf(chTemp,"%c %d",&ch,&pos);
        //读取换行标识
        if(ch ==7)
        {
            ui->textEdit->insertPlainText(QString("\n"));
            continue;
        }
        char buff[2560] = {' '};
        get_word_by_last_char(p_trie,ch,pos,buff,0);

        ui->textEdit->insertPlainText(QString(buff));
    }
}
//解压文件
void MainWindow::on_pushButton_4_clicked()
{
    QString outFileName = QFileDialog::getSaveFileName(this, "Save File",
                                "F:",
                                "c++语言文件(*.c *.cpp *.h)");
    ofstream outFile(outFileName.toStdString().c_str(),ios::out);
    ifstream infile(fileName1.toStdString().c_str(),ios::in);
    char chTemp[256]={0};
    char ch=0;
    int pos;
    while(infile.getline(chTemp,256))
    {
        sscanf(chTemp,"%c %d",&ch,&pos);
        //读取换行标识
        if(ch ==7)
        {
            outFile<<"\n";
            continue;
        }
        char buff[2560] = {' '};
        get_word_by_last_char(p_trie,ch,pos,buff,0);

        outFile<<buff;
    }
}

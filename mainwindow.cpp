#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QFileDialog"
#include"QTextStream"
#include"Processor.h"
#include"string"
#include"QMessageBox"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this,"选择一个文法规则文件", ".", "Code(*.txt *.tiny )");
    ui->lineEdit->setText(file_path);
    ui->textEdit->clear();
    QFile file(file_path);
    if(!file.open(QFile::ReadOnly | QFile::Text))
       return;
    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        ui->textEdit->append(line);
    }
    file.close();
}

/**
    “分析”按钮执行的动作
*/
void MainWindow::on_pushButton_2_clicked()
{
    std::string analyzerFilePath = ui->lineEdit->text().toStdString();
    //未输入文法
    if(analyzerFilePath.empty())
    {
        QMessageBox::about(NULL,"Warning",
                           "Please select a file as an input");
        return;
    }
    processor = new Processor(analyzerFilePath);
    processor->log << "原本语法如下:" << '\n';
    processor->printGrammers();
    processor->dealLeftRecursion();

    processor->log <<'\n';
    processor->log << "去除左递归后:" << '\n';
    processor->printGrammers();
    processor->simplify();

    processor->log <<'\n';
    processor->log << "去除多余项后:" << '\n';
    processor->printGrammers();
    processor->dealLeftCommonFacotr();

    processor->log <<'\n';
    processor->log << "去除左公因子后:" << '\n';
    processor->printGrammers();
    processor->getFirst();
    processor->getFollow();
    //关闭输入流
    processor->log.close();
    //接下来输出
    //先输出处理后的文法
    string output;
    output = this->getProcessedGrammers();
    this -> ui-> textBrowser_6->setText(QString::fromStdString(output));
    //输出first集合
    this->outputFirst();
    //输出follow集合
    this->outputFollow();
    //输出日志信息
    this->outputLog();
    //输出dfa图
    system("dot -Tpng ./debug/graph/dfa.dot -o ./debug/graph/dfa.png");
    //将生成的dfa图展示出来
    QPixmap image;
    image.load("./dubug/graph/dfa.png");
    ui->label_10->clear();
    ui->label_10->setPixmap(image);
    ui->label_10->show();
}




string MainWindow::getProcessedGrammers()
{
    string output = "";
    //输出
    for(LinkNode node : this -> processor->grammers)
    {
        output += node.left;
        output += "->";
        for(size_t j = 0; j < node.right.size(); j++)
        {
            for(size_t i = 0; i < node.right[j].size(); i++)
                output += node.right[j][i];
            if(j != node.right.size() - 1)
                output += "|";
        }
        output += "\n";
    }
    return output;
}

void MainWindow::outputFirst()
{
    string s = "";
    for(LinkNode node : this -> processor->grammers)
    {
        s += "first(" + node.left + ") = {";
        set<string> firstSet = this -> processor ->first[node.left];
        set<string>::iterator it = firstSet.begin();
        bool flag = false;
        for(; it != firstSet.end(); it++)
        {
            if(flag)
                s += ",";
            s += *it;
            flag = true;
        }
        s += "}\n";
    }
    this -> ui -> textBrowser_2->setText(QString::fromStdString(s));
}

void MainWindow::outputFollow()
{
    string s = "";
    //输出follow集合到log文件
    map<string, set<string>>::iterator it = processor->follow.begin();
    for(; it != processor->follow.end(); it++)
    {
        s += "follow(" + it->first + ") = {";
        set<string> &temp = it->second;
        bool flag = false;
        for(set<string>::iterator it1 = temp.begin(); it1 != temp.end(); it1++)
        {
            if(flag) s += ",";
            s += *it1;
            flag = true;
        }
        s += "}\n";
    }
    this -> ui -> textBrowser_4->setText(QString::fromStdString(s));
}

void MainWindow::outputLog()
{
    ifstream log;
    log.open("log.txt");
    if(!log.is_open())
    {
        QMessageBox::about(NULL,"Warning","Fail to open \"log.txt\"");
        return;
    }
    string s = "";
    string line;
    while(getline(log,line))
        s += line + "\n";
    log.close();
    this -> ui -> textBrowser->setText(QString::fromStdString(s));
}


/**
    保存处理好的文法
*/
void MainWindow::on_pushButton_3_clicked()
{
    string str = getProcessedGrammers();
    ofstream file;
    file.open("processedGrammers.txt");
    if(!file.is_open())
    {
        QMessageBox::about(NULL,"Warning","Fail to save grammers!");
        return;
    }
    file << str;
    file.close();
    QMessageBox::about(NULL,"提示","修改好的文法已保存在processedGrammers.txt");
}

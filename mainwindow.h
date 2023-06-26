#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();//打开文件

    void on_pushButton_2_clicked();//生成语法树

    void on_pushButton_3_clicked();//保存语法树

    void on_pushButton_4_clicked();//清空
private:
    Ui::MainWindow *ui;
    //日志的路径
    QString l1_path;
    QString l2_path;
};
#endif // MAINWINDOW_H

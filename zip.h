#ifndef ZIP_H
#define ZIP_H
#include<stdio.h>
#include<stdlib.h>
#include <QMainWindow>
#include <string.h>
#include <QString>
using namespace std;
namespace Ui {
class zip;
}

class zip : public QMainWindow
{
    Q_OBJECT

public:
    explicit zip(QWidget *parent = nullptr);
    ~zip();
    string tarfile(string path,string newpath="");
   // void tardir(string path);
   // void pack(string path,vector<string> &store);
private slots:
    void on_backtoinitial_clicked();

    void on_toolButton_clicked();

    void on_tar_clicked();

private:
    Ui::zip *ui;
};

#endif // ZIP_H

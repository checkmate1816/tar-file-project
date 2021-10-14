#ifndef ZIPDIR_H
#define ZIPDIR_H
#include <string.h>
#include <QMainWindow>
using namespace std;
namespace Ui {
class zipdir;
}

class zipdir : public QMainWindow
{
    Q_OBJECT

public:
    explicit zipdir(QWidget *parent = nullptr);
    ~zipdir();
    string tarfile(string path,string newpath="");
    void tardir(string path);
    void pack(string path,vector<string> &store);
private slots:




    void on_tardir_clicked();

    void on_back_clicked();

    void on_toolButton_clicked();

private:
    Ui::zipdir *ui;
};

#endif // ZIPDIR_H

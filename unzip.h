#ifndef UNZIP_H
#define UNZIP_H

#include <QMainWindow>

namespace Ui {
class unzip;
}

class unzip : public QMainWindow
{
    Q_OBJECT

public:
    explicit unzip(QWidget *parent = nullptr);
    ~unzip();

private slots:
    void on_backtoinitial_clicked();

    void on_toolButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::unzip *ui;
};

#endif // UNZIP_H

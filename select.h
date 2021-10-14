#ifndef SELECT_H
#define SELECT_H

#include <QMainWindow>

namespace Ui {
class select;
}

class select : public QMainWindow
{
    Q_OBJECT

public:
    explicit select(QWidget *parent = nullptr);
    ~select();

private slots:
    void on_tarfile_clicked();

    void on_tardir_clicked();

    void on_cancel_clicked();

private:
    Ui::select *ui;
};

#endif // SELECT_H

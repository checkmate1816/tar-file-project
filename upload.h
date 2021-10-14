#ifndef UPLOAD_H
#define UPLOAD_H

#include <QMainWindow>

namespace Ui {
class upload;
}

class upload : public QMainWindow
{
    Q_OBJECT

public:
    explicit upload(QWidget *parent = nullptr);
    ~upload();

private slots:
    void on_toolButton_clicked();

    void on_uploadfunc_clicked();

private:
    Ui::upload *ui;
};

#endif // UPLOAD_H

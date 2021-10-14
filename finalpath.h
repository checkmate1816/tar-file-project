#ifndef FINALPATH_H
#define FINALPATH_H

#include <QDialog>

namespace Ui {
class finalpath;
}

class finalpath : public QDialog
{
    Q_OBJECT

public:
    explicit finalpath(QString &newpath,QWidget *parent = nullptr);
    ~finalpath();
    QString &temp;
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::finalpath *ui;
};

#endif // FINALPATH_H

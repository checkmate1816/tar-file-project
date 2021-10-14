#include "finalpath.h"
#include "ui_finalpath.h"

finalpath::finalpath(QString &path,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::finalpath),temp(path)
{
    ui->setupUi(this);
}

finalpath::~finalpath()
{
    delete ui;
}

void finalpath::on_buttonBox_accepted()
{
                temp=ui->path->text();
                //delete this;
}

void finalpath::on_buttonBox_rejected()
{
    delete this;
}

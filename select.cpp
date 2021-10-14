#include "select.h"
#include "ui_select.h"
#include "zip.h"
#include "zipdir.h"
select::select(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::select)
{
    ui->setupUi(this);
}

select::~select()
{
    delete ui;
}

void select::on_tarfile_clicked()
{
    zip *a=new zip();
    a->show();
}

void select::on_tardir_clicked()
{
    zipdir *b=new zipdir();
    b->show();
}

void select::on_cancel_clicked()
{
    delete this;
}

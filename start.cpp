#include "start.h"
#include "ui_start.h"
#include "zip.h"
#include "unzip.h"
#include "select.h"
#include "cloudselect.h"
start::start(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::start)
{
    ui->setupUi(this);
}

start::~start()
{
    delete ui;
}


void start::on_zip_clicked()
{
    select *a=new select();
    a->show();
}

void start::on_unzip_clicked()
{
    unzip *b=new unzip();
    b->show();
}

void start::on_cloud_clicked()
{
    cloudselect *a=new cloudselect();
    a->show();
}

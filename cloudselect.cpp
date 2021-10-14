#include "cloudselect.h"
#include "ui_cloudselect.h"
#include "upload.h"
#include "download.h"
cloudselect::cloudselect(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cloudselect)
{
    ui->setupUi(this);
}

cloudselect::~cloudselect()
{
    delete ui;
}

void cloudselect::on_upload_clicked()
{
    upload *a=new upload();
    a->show();
}

void cloudselect::on_download_clicked()
{
    download *a=new download();
    a->show();
}

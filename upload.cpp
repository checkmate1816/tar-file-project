#include "upload.h"
#include "ui_upload.h"
#include <QString>
#include <QFileDialog>
#include <stdio.h>
#include <stdlib.h>
upload::upload(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::upload)
{
    ui->setupUi(this);
}

upload::~upload()
{
    delete ui;
}

void upload::on_toolButton_clicked()
{
    QString filepath=QFileDialog::getOpenFileName(this,"choose file","D:\\","*");
    ui->line->setText(filepath);
}

void upload::on_uploadfunc_clicked()
{
    QString command="bypy upload "+ui->line->text();
    system(command.toStdString().c_str());
}

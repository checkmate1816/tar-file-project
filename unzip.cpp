#include "unzip.h"
#include "ui_unzip.h"
#include <QFileDialog>
#include "decodehead.h"
#include <QString>
#include "hint.h"
unzip::unzip(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::unzip)
{
    ui->setupUi(this);
}

unzip::~unzip()
{
    delete ui;
}

void unzip::on_backtoinitial_clicked()
{
    delete this;
}

void unzip::on_toolButton_clicked()
{
    QString filepath=QFileDialog::getOpenFileName(this,"choose file","D:\\","*.txt");
    ui->line->setText(filepath);
}

void unzip::on_pushButton_clicked()
{
    QString filepath=ui->line->text();
    untar(filepath.toStdString());
    hint *temp=new hint();
    temp->show();
}

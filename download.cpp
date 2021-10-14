#include "download.h"
#include "ui_download.h"
#include <QString>
#include <stdio.h>
#include <stdlib.h>
download::download(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::download)
{
    ui->setupUi(this);
}

download::~download()
{
    delete ui;
}

void download::on_pushButton_clicked()
{
       QString command="bypy download "+ui->line->text();
       system(command.toStdString().c_str());
}

#include "hint.h"
#include "ui_hint.h"

hint::hint(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hint)
{
    ui->setupUi(this);
}

hint::~hint()
{
    delete ui;
}


void hint::on_exit_clicked()
{
    delete this;
}

#include "mod_fields.h"
#include "ui_mod_fields.h"

mod_fields::mod_fields(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mod_fields)
{
    ui->setupUi(this);
}

mod_fields::~mod_fields()
{
    delete ui;
}

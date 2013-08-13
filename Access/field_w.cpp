#include "field_w.h"
#include "ui_field_w.h"
#include <QMessageBox>
field_W::field_W(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::field_W)
{
    ui->setupUi(this);
    ui->field_type->addItem("Entero");
    ui->field_type->addItem("Real");
    ui->field_type->addItem("Cadena");
    ui->field_decimal->setEnabled(false);
}

field_W::~field_W()
{
    delete ui;
}

void field_W::on_field_type_currentIndexChanged(int index)
{
    if(index == 1){
        ui->field_decimal->setEnabled(true);
        ui->field_decimal->setValue(1);
        ui->field_length->setValue(3);
    }
    else{
        ui->field_decimal->setEnabled(false);
    }
}

void field_W::on_field_clear_clicked()
{
    ui->field_decimal->setValue(1);
    ui->field_decimal->setEnabled(false);
    ui->field_key->setChecked(false);
    ui->field_length->setValue(0);
    ui->field_name->setText("");
    ui->field_type->setCurrentIndex(0);
}


void field_W::on_field_add_clicked()
{
    if(ui->field_type->currentIndex()==1 && ((ui->field_decimal->value()==0) || (ui->field_length->value() == 0) || ((ui->field_name->text().operator ==("")) ||(ui->field_name->text().operator ==(NULL)))) ){
        QMessageBox::warning(this,"Error","No tiene los atributos suficientes para crear un campo");
    }
    else if((ui->field_length->value() == 0) || ((ui->field_name->text().operator ==("")) ||(ui->field_name->text().operator ==(NULL)) )){
        QMessageBox::warning(this,"Error","No tiene los atributos suficientes para crear un campo");
    }
    for(int i=0; i<10;++i){
        fieldlist.push_back((i+1));
    }

}
void field_W::getFields(vector<int>& x){
    for(int i=0;i<fieldlist.size();++i){
        x.push_back(fieldlist.at(i));
    }
}

void field_W::on_field_length_valueChanged(int arg1)
{
    if(ui->field_type->currentIndex()==1){
        ui->field_decimal->setMaximum(arg1-2);
    }
    else{
        ui->field_decimal->setValue(1);
    }
}

#include "field_w.h"
#include "field.h"
#include "ui_field_w.h"
#include <QMessageBox>
#include <iostream>
using namespace std;
field_W::field_W(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::field_W)
{
    fh=new FileHeader();
    show_key=true;
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
        ui->field_decimal->setValue(1);
        ui->field_decimal->setEnabled(false);
        ui->field_key->setChecked(false);
        ui->field_length->setValue(0);
        ui->field_name->setText("");
        ui->field_type->setCurrentIndex(0);
        return ;
    }
    else if((ui->field_length->value() == 0) || ((ui->field_name->text().operator ==("")) ||(ui->field_name->text().operator ==(NULL)) )){
        QMessageBox::warning(this,"Error","No tiene los atributos suficientes para crear un campo");
        ui->field_decimal->setValue(1);
        ui->field_decimal->setEnabled(false);
        ui->field_key->setChecked(false);
        ui->field_length->setValue(0);
        ui->field_name->setText("");
        ui->field_type->setCurrentIndex(0);
        return ;
    }
    int y=0;//0 no es key, 1 si lo es
    if(ui->field_key->isChecked()){
        show_key=false;
        y=1;
    }
    if(!show_key){
        ui->field_key->setChecked(false);
        ui->field_key->setEnabled(false);
    }
    char x;
    int d=0;

    if(ui->field_type->currentIndex()==1){
        d=ui->field_decimal->value();
        if(d<=0)
            d=1;
    }

    if(ui->field_type->currentIndex()==0)
        x='0';
    if(ui->field_type->currentIndex()==1)
        x='1';
    if(ui->field_type->currentIndex()==2)
        x='2';

    field a(ui->field_name->text().toStdString(),x,ui->field_length->value(),d,y);
    fh->addField(a);
    ui->field_decimal->setValue(1);
    ui->field_decimal->setEnabled(false);
    ui->field_key->setChecked(false);
    ui->field_length->setValue(0);
    ui->field_name->setText("");
    ui->field_type->setCurrentIndex(0);
}
FileHeader* field_W::getFields(){
    return fh;
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

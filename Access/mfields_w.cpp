#include "mfields_w.h"
#include "ui_mfields_w.h"
#include "field.h"
#include <QMessageBox>
#include <iostream>
using namespace std;
mFields_w::mFields_w(QWidget *parent) ://Constructor de la clase
    QDialog(parent),
    ui(new Ui::mFields_w)
{
    ui->setupUi(this);
    show_key=false;
    ui->setupUi(this);
    ui->mod_tipo->addItem("Entero");
    ui->mod_tipo->addItem("Real");
    ui->mod_tipo->addItem("Cadena");
    ui->mod_decimal->setEnabled(false);

    connect(ui->mod_ok, SIGNAL(clicked()),
            this, SLOT(on_mod_ok_clicked()));
    connect(ui->mod_nombre,SIGNAL(editingFinished()),this,SLOT(on_mod_nombre_editingFinished()));
}

mFields_w::~mFields_w()//Destructor de la clase
{
    delete ui;
}

bool mFields_w::getShow_key(){
    return this->show_key;
}

void mFields_w::setField(field x,vector<QString> z){
    this->f=x;
    ui->mod_nombre->setText(QString::fromStdString(f.getName()));
    ui->mod_length->setValue(f.getLength());
    if(f.getType()==1){
        ui->mod_decimal->setValue(f.getDecimal());
        ui->mod_tipo->setCurrentIndex(1);
    }
    else if(f.getType()==0){
        ui->mod_tipo->setCurrentIndex(0);
        ui->mod_decimal->setEnabled(false);
    }
    else{
        ui->mod_tipo->setCurrentIndex(2);
        ui->mod_decimal->setEnabled(false);
    }
    if(f.getKey()==0)
        ui->mod_key->setChecked(false);
    else
        ui->mod_key->setEnabled(false);

    for(int i=0;i<z.size();++i)
        this->names.push_back(z.at(i));
}

field mFields_w::getField(){
    return f;
}

void mFields_w::on_mod_tipo_currentIndexChanged(int index)
{
    if(index == 1){
        ui->mod_decimal->setEnabled(true);
        ui->mod_decimal->setValue(1);
        ui->mod_length->setValue(3);
    }
    else{
        ui->mod_decimal->setEnabled(false);
    }
}

void mFields_w::on_mod_length_valueChanged(int arg1)
{
    if(ui->mod_tipo->currentIndex()==1){
        ui->mod_decimal->setMaximum(arg1-2);
    }
    else{
        ui->mod_decimal->setValue(1);
    }
}

void mFields_w::on_mod_nombre_editingFinished()
{
    QString qstr1=ui->mod_nombre->text();
    QString qstr2=QString::fromStdString(f.getName());
    int z=0;
    for(int i=0; i<this->names.size();++i)
        if(qstr1 == (names.at(i)) ){
            if( (qstr2 == qstr1) ){
            }
            else{
            QMessageBox::warning(this,"Error","Nombre de campo ya usado");
            ui->mod_nombre->setText("");
            }
        }
}

void mFields_w::on_mod_ok_clicked()
{
    if(ui->mod_tipo->currentIndex()==1 && ((ui->mod_decimal->value()==0) || (ui->mod_length->value() == 0) || ((ui->mod_nombre->text().operator ==("")) ||(ui->mod_nombre->text().operator ==(NULL)))) ){
        QMessageBox::warning(this,"Error","No tiene los atributos suficientes para modificar un campo");
        ui->mod_decimal->setValue(1);
        ui->mod_decimal->setEnabled(false);
        ui->mod_key->setChecked(false);
        ui->mod_length->setValue(1);
        ui->mod_nombre->setText("");
        ui->mod_tipo->setCurrentIndex(0);
        return ;
    }
    else if((ui->mod_length->value() == 0) || ((ui->mod_nombre->text().operator ==("")) ||(ui->mod_nombre->text().operator ==(NULL)) )){
        QMessageBox::warning(this,"Error","No tiene los atributos suficientes para modificar un campo");
        ui->mod_decimal->setValue(1);
        ui->mod_decimal->setEnabled(false);
        ui->mod_key->setChecked(false);
        ui->mod_length->setValue(1);
        ui->mod_nombre->setText("");
        ui->mod_tipo->setCurrentIndex(0);
        return ;
    }
    int y=0;//0 no es key, 1 si lo es
    if(ui->mod_key->isChecked()){
        show_key=true;
        y=1;
    }
    char x;
    int d=0;

    if(ui->mod_tipo->currentIndex()==1){
        d=ui->mod_decimal->value();
        if(d<=0)
            d=1;
    }

    if(ui->mod_tipo->currentIndex()==0)
        x='0';
    if(ui->mod_tipo->currentIndex()==1)
        x='1';
    if(ui->mod_tipo->currentIndex()==2)
        x='2';

    field a(ui->mod_nombre->text().toStdString(),x,ui->mod_length->value(),d,y);
    this->f=a;
    QMessageBox::information(this,"Info.","Modificacion con exito");
    this->close();
}

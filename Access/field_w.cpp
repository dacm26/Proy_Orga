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
    setWindowFlags(Qt::Window|Qt::CustomizeWindowHint|Qt::WindowTitleHint);//No permite que el usuario cierre la ventana
}

field_W::~field_W()
{
    delete ui;
}

void field_W::on_field_type_currentIndexChanged(int index)
{
    //QMessageBox::information(this,"lolol",ui->field_type->currentText());
    if(index == 1){
        ui->field_decimal->setEnabled(true);
    }
    else{
        ui->field_decimal->setEnabled(false);
    }
}

void field_W::on_field_clear_clicked()
{
    ui->field_decimal->setValue(0);
    ui->field_key->setChecked(false);
    ui->field_length->setValue(0);
    ui->field_name->setText("");
    ui->field_type->setCurrentIndex(0);
}

void field_W::on_field_exit_clicked()
{
 this->close();
}

void field_W::on_field_add_clicked()
{
    if(ui->field_type->currentIndex()==1 && ((ui->field_decimal->value()==0) || (ui->field_length->value() == 0) || ((ui->field_name->text().operator ==("")) ||(ui->field_name->text().operator ==(NULL)))) ){
        QMessageBox::warning(this,"Error","No tiene los atributos suficientes para crear un campo");
    }
    else if((ui->field_length->value() == 0) || ((ui->field_name->text().operator ==("")) ||(ui->field_name->text().operator ==(NULL)) )){
        QMessageBox::warning(this,"Error","No tiene los atributos suficientes para crear un campo");
    }
}

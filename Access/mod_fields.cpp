#include "mod_fields.h"
#include "ui_mod_fields.h"
#include <sstream>
using namespace std;
mod_fields::mod_fields(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mod_fields)
{

    ui->setupUi(this);

}

int mod_fields::getSel(){
    return sel;//Devuelve el inciso del campo a modificar
}

void mod_fields::setLabel(const vector<field>& fl){
    stringstream ss;
    for(int i=0; i<fl.size();++i){
        ss << (i) << ". " << (fl.at(i)).getName() << endl;//Se asigna al ss con su respectivo inciso y nombre
    }
    ui->sp_mod->setMaximum(fl.size()-1);//Asignamos el valor max al spinner con el numero de campos
    QString qstr = QString::fromStdString(ss.str());//Pasamos de String -> QString
    ui->mod_label->setText(qstr);//Se setean los campos al label
}

mod_fields::~mod_fields()
{
    delete ui;
}

void mod_fields::on_mod_ok_clicked()
{
    sel=ui->sp_mod->value();//Se asigna el inciso seleccionado
    this->close();//Cierra la ventana
}

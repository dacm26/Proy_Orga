#ifndef MFIELDS_W_H
#define MFIELDS_W_H
#include <QDialog>
#include <vector>
#include "field.h"
using namespace std;

namespace Ui {
class mFields_w;
}

class mFields_w : public QDialog
{
    Q_OBJECT
    
public:
    explicit mFields_w(QWidget *parent = 0);//Constructor de la ventana de modificar campos
    void setField(field,vector<QString>);//Modifica un campo
    field getField();//Devuelve el campo modificado
    bool getShow_key();//Muestra si es o no una llave
    ~mFields_w();//Destructor de la ventana
    
private slots:
    void on_mod_tipo_currentIndexChanged(int index);//Hace las validaciones dependiendo de su tipo
    void on_mod_length_valueChanged(int arg1);//Aplica lo minimo o max de la longitud si es decimal
    void on_mod_nombre_editingFinished();//Verifica si esta o no vacio el campo del nombre
    void on_mod_ok_clicked();//Modifica el campo

private:
    Ui::mFields_w *ui;//Ventana de modificar
    bool show_key;//Bandera que muestra o no la llave
    field f;//Campo a modificar
    vector<QString> names;//Contiene los nombres de los campos
};

#endif // MFIELDS_W_H

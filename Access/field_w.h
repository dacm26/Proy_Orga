#ifndef FIELD_W_H
#define FIELD_W_H
#include "fileheader.h"
#include <QDialog>
#include <vector>
using namespace std;

namespace Ui {
class field_W;
}

class field_W : public QDialog
{
    Q_OBJECT
    
public:
    explicit field_W(QWidget *parent = 0);//Construcor de la ventana crear campos
    FileHeader* getFields();//Devuelve los campos crados
    void copy_fh(FileHeader*);//copia un FH al de la clase
    ~field_W();//destructor de la ventana crear campos

private slots:
    void on_field_type_currentIndexChanged(int index);//Hace las validaciones dependiendo de su tipo
    void on_field_clear_clicked();//Limpia los atributos dados hasta el momento
    void on_field_add_clicked();//Agrega un Campo al FH
    void on_field_length_valueChanged(int arg1);//Aplica lo minimo o max de la longitud si es decimal
    void on_field_name_editingFinished();//Verifica si esta o no vacio el campo del nombre

private:
    Ui::field_W *ui;//Ventana de crear campos
    FileHeader *fh;//FH a devolver al cerrar la ventana
    bool show_key;//Bandera que muestra o no la llave
};

#endif // FIELD_W_H

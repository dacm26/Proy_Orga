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
    explicit mFields_w(QWidget *parent = 0);
    void setField(field,vector<QString>);
    field getField();
    bool getShow_key();
    ~mFields_w();
    
private slots:
    void on_mod_tipo_currentIndexChanged(int index);

    void on_mod_length_valueChanged(int arg1);

    void on_mod_nombre_editingFinished();

    void on_mod_ok_clicked();

private:
    Ui::mFields_w *ui;
    bool show_key;
    field f;
    vector<QString> names;
};

#endif // MFIELDS_W_H

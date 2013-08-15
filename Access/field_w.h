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
    explicit field_W(QWidget *parent = 0);
    FileHeader* getFields();
    void copy_fh(FileHeader*);
    ~field_W();

private slots:
    void on_field_type_currentIndexChanged(int index);

    void on_field_clear_clicked();

    void on_field_add_clicked();

    void on_field_length_valueChanged(int arg1);

private:
    Ui::field_W *ui;
    FileHeader *fh;
    bool show_key;
};

#endif // FIELD_W_H

#ifndef MOD_FIELDS_H
#define MOD_FIELDS_H

#include <QDialog>
#include <vector>
#include "field.h"
using namespace std;
namespace Ui {
class mod_fields;
}

class mod_fields : public QDialog
{
    Q_OBJECT
    
public:
    explicit mod_fields(QWidget *parent = 0);
    ~mod_fields();
    void setLabel(const vector<field>&);
    int getSel();
private slots:
    void on_mod_ok_clicked();

private:
    Ui::mod_fields *ui;
    int sel;
};

#endif // MOD_FIELDS_H

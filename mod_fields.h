#ifndef MOD_FIELDS_H
#define MOD_FIELDS_H

#include <QDialog>

namespace Ui {
class mod_fields;
}

class mod_fields : public QDialog
{
    Q_OBJECT
    
public:
    explicit mod_fields(QWidget *parent = 0);
    ~mod_fields();
    
private:
    Ui::mod_fields *ui;
};

#endif // MOD_FIELDS_H

#ifndef FIELD_W_H
#define FIELD_W_H

#include <QDialog>

namespace Ui {
class field_W;
}

class field_W : public QDialog
{
    Q_OBJECT
    
public:
    explicit field_W(QWidget *parent = 0);
    ~field_W();

private slots:
    void on_field_type_currentIndexChanged(int index);

    void on_field_clear_clicked();

    void on_field_exit_clicked();

    void on_field_add_clicked();

private:
    Ui::field_W *ui;
};

#endif // FIELD_W_H

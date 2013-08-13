#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "field_w.h"
#include <QMainWindow>
#include <vector>
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionNuevo_triggered();

    void on_actionCrear_triggered();

    void on_actionSalir_triggered();
public:
    Ui::MainWindow *ui;
    field_W *novo;
    vector<int> fieldlist;
};

#endif // MAINWINDOW_H

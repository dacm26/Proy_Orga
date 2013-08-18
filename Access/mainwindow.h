#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "field_w.h"
#include <QMainWindow>
#include <vector>
#include "ADTRecordFile.h"
#include "fileheader.h"
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
    void on_actionListar_triggered();

    void on_actionModificar_triggered();

    void on_actionGuardar_triggered();

    void on_actionCerrar_triggered();

    void on_actionAbrir_triggered();

    void on_actionIntroducir_triggered();

    void on_actionBuscar_triggered();

    void on_actionBorrar_triggered();

    void on_actionListar_2_triggered();

    void on_actionCruzar_triggered();

public:
    Ui::MainWindow *ui;
    field_W *novo;
    FileHeader *fh;
    ADTRecordFile* o_file;
    int init;
    int n_rec;
    int init_avail;
};

#endif // MAINWINDOW_H

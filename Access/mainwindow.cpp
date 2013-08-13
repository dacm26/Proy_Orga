#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include "field_w.h"
#include <QFileDialog>
#include <QStandardItemModel>
#include <QStandardItem>
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setFixedSize(1370,710);
    setCentralWidget(ui->table);
    setWindowFlags(Qt::Window|Qt::CustomizeWindowHint|Qt::WindowTitleHint);//No permite que el usuario cierre la ventana
    ui->table->setEnabled(false);
    /*QStandardItemModel* model = new QStandardItemModel(1,1,this);
    model->setHorizontalHeaderItem(0,new QStandardItem(QString("Nombre")));
    model->setHorizontalHeaderItem(1,new QStandardItem(QString("Edad")));
    model->setHorizontalHeaderItem(2,new QStandardItem(QString("Sexo")));
    model->setItem(0,0,new QStandardItem(QString("Daniel")));
    model->setItem(0,1,new QStandardItem(QString("19")));
    model->setItem(0,2,new QStandardItem(QString("Frecuente")));
    ui->table->setModel(model);
    */

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNuevo_triggered()
{

}


void MainWindow::on_actionCrear_triggered()
{
    novo= new field_W();
    novo->exec();
    vector<int>field_list;
    novo->getFields(field_list);
    for(int i=0; i<field_list.size();i++)
        cout << field_list.at(i)<<endl;
    delete novo;
}

void MainWindow::on_actionSalir_triggered()
{
    this->close();
}

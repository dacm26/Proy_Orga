#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "field_w.h"
#include "mod_fields.h"


#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QStandardItem>


#include <iostream>
#include <sstream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setFixedSize(1370,710);//Se le asigna el tamanio deseado a la ventana principal
    setCentralWidget(ui->table);//La tabla es asignada como la aplicacion central de la aplicacion
    setWindowFlags(Qt::Window|Qt::CustomizeWindowHint|Qt::WindowTitleHint);//No permite que el usuario cierre la ventana
    //ui->table->setEnabled(false);//No permite que el usuario interactue con la tabla

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
    novo= new field_W();//Se crea la ventana para crear campos
    novo->exec();//se ejecuta la ventana
    fh=novo->getFields();//Obtiene el FieldList y AvailList
    delete novo;//se libera la memoria
}

void MainWindow::on_actionSalir_triggered()
{
    this->close();//Sale del Programa completamente
}

void MainWindow::on_actionListar_triggered()
{
    QStandardItemModel* model = new QStandardItemModel(1,1,this);//Se crea el modelo para la tabla
    //Se crean las columnas de la tabla
    model->setHorizontalHeaderItem(0,new QStandardItem(QString("Nombre")));
    model->setHorizontalHeaderItem(1,new QStandardItem(QString("Tipo")));
    model->setHorizontalHeaderItem(2,new QStandardItem(QString("Longitud")));
    model->setHorizontalHeaderItem(3,new QStandardItem(QString("Decimal")));
    model->setHorizontalHeaderItem(4,new QStandardItem(QString("Llave")));

    QString qstr;
    string str;
    stringstream ss;

    for(int i=0; i<fh->fl_size();i++){//Se Asignan los valores de los campos a la tabla central
        qstr= QString::fromStdString((fh->getFL().at(i)).getName());
        model->setItem(i,0,new QStandardItem(qstr));
        str=(fh->getFL().at(i)).getType();
        qstr= QString::fromStdString(str);
        model->setItem(i,1,new QStandardItem(qstr));
        ss << (fh->getFL().at(i)).getLength();
        str=ss.str();
        ss.str("");
        qstr= QString::fromStdString(str);
        model->setItem(i,2,new QStandardItem(qstr));
        ss << (fh->getFL().at(i)).getDecimal();
        str=ss.str();
        ss.str("");
        qstr= QString::fromStdString(str);
        model->setItem(i,3,new QStandardItem(qstr));
        ss << (fh->getFL().at(i)).getKey();
        str=ss.str();
        ss.str("");
        qstr= QString::fromStdString(str);
        model->setItem(i,4,new QStandardItem(qstr));
    }//Se termino de Asignar los valores de los campos en la tabla central
    ui->table->setModel(model);//Asigna el Modelo a la tabla
}

void MainWindow::on_actionModificar_triggered()
{
    if(fh->fl_size() > 0){//Si existen campos
    int sel;
    mod_fields *novo = new mod_fields();
    novo->setLabel(fh->getFL());//Se le asignan los campos al Label de novo
    novo->exec();
    sel=novo->getSel();//Campo a Modificar
    delete novo;
    }
    else{//Si no existen campos
        QMessageBox::warning(this,"Error","No tiene campos para modificar");
    }
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "field_w.h"
#include "mfields_w.h"
#include "ADTRecordFile.h"

#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QInputDialog>

#include <iostream>
#include <sstream>
using namespace std;

/*
 Pendiente:
 **Registros
 **Utilidades
 **Archivos
 **Indices
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->o_file=new ADTRecordFile();
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
    if(!o_file->isOpen()){
        QString filename= QFileDialog::getSaveFileName(this,"Save As","/home");//Filters: Text Files (*.txt)::All Files(*.*)
        this->o_file->open(filename.toStdString());
     }
    else
        QMessageBox::warning(this,"Error","No se puede crear un nuevo archivo, ya que tiene uno abierto");
}

void MainWindow::on_actionCrear_triggered()
{
    if(o_file->isOpen()){
    novo= new field_W();//Se crea la ventana para crear campos
    if(fh->fl_size()>0)
        novo->copy_fh(fh);
    novo->exec();//se ejecuta la ventana
    fh=novo->getFields();//Obtiene el FieldList y AvailList
    delete novo;//se libera la memoria
    }else{
        QMessageBox::warning(this,"Error","No tiene un archivo abierto");
    }
}

void MainWindow::on_actionSalir_triggered()
{
    if(o_file->isOpen()){
        this->o_file->flush();
        this->o_file->close();
    }
    this->close();//Sale del Programa completamente
}

void MainWindow::on_actionListar_triggered()
{
    if(o_file->isOpen()){
        if(fh->fl_size()==0){
            QMessageBox::warning(this,"Error","No tiene campos que listar");
        }else{
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
            if((fh->getFL().at(i)).getType() == '0'){
                model->setItem(i,1,new QStandardItem("Entero"));
            }
            else if((fh->getFL().at(i)).getType() == '1'){
                model->setItem(i,1,new QStandardItem("Real"));
            }
            else{
                model->setItem(i,1,new QStandardItem("Cadena"));
            }
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
            if((fh->getFL().at(i)).getKey()==0){
                model->setItem(i,4,new QStandardItem("No es llave"));
            }
            else{
                model->setItem(i,4,new QStandardItem("Es llave"));
            }

        }//Se termino de Asignar los valores de los campos en la tabla central
        ui->table->setModel(model);//Asigna el Modelo a la tabla
        }
    }
    else{
            QMessageBox::warning(this,"Error","No tiene un archivo abierto");
        }
}

void MainWindow::on_actionModificar_triggered()
{
    if(o_file->isOpen()){
        if(fh->fl_size() > 0){//Si existen campos
            stringstream ss;
            bool ok;
            int mod_field;
            for(int i=0; i<fh->fl_size();++i){
                    ss << (i) << ". " << (fh->getFL().at(i)).getName() << endl;//Se asigna al ss con su respectivo inciso y nombre
            }
            QString qstr = QString::fromStdString(ss.str());//Pasamos de String -> QString
            do{
                mod_field=QInputDialog::getInt(this,"Modificar campos",qstr,0,0,fh->fl_size()-1,1,&ok);
            }while(!ok);
            field fd=this->fh->getFL().at(mod_field);
            vector<QString> names;
            for(int i=0;i<fh->getFL().size();++i)
                names.push_back( QString::fromStdString(fh->getFL().at(i).getName()) );
            mFields_w *novo=new mFields_w();
            novo->setField(fd,names);
            novo->exec();
            fd=novo->getField();
            fh->setField(mod_field,fd);
            delete novo;
        }
        else{//Si no existen campos
            QMessageBox::warning(this,"Error","No tiene campos para modificar");
        }
    }
    else
        QMessageBox::warning(this,"Error","No tiene un archivo abierto");
}

void MainWindow::on_actionGuardar_triggered()
{
    if(!o_file->isOpen())
        QMessageBox::warning(this,"Error","No tiene un archivo abierto");
    else{
        this->o_file->flush();
    }

}

void MainWindow::on_actionCerrar_triggered()
{
    if(!o_file->isOpen())
        QMessageBox::warning(this,"Error","No tiene un archivo abierto");
    else{
        this->o_file->flush();
        this->o_file->close();
    }
}

void MainWindow::on_actionAbrir_triggered()
{
    if(this->o_file->isOpen())
        QMessageBox::warning(this,"Error","No se pudo abrir el archivo, porque ya esta uno abierto");
    else{
        QString filename= QFileDialog::getOpenFileName(this,"Open File","/home","*.txt");
        o_file->open(filename.toStdString());
        if(!o_file->isOpen())
            QMessageBox::warning(this,"Error","No se pudo abrir el archivo");
    }
}

void MainWindow::on_actionIntroducir_triggered()
{
    if(o_file->isOpen()){
        if(fh->fl_size()<=0)
            QMessageBox::warning(this,"Error","Necesita tener al menos un campo para poder crear un registro");
        else{

        }
    }
    else
        QMessageBox::warning(this,"Error","No tiene ningun archivo abierto");
}

void MainWindow::on_actionBuscar_triggered()
{
    if(o_file->isOpen()){
        if(fh->fl_size()<=0)
            QMessageBox::warning(this,"Error","Necesita tener al menos un campo para poder crear un registro");
        else{

        }
    }
    else
        QMessageBox::warning(this,"Error","No tiene ningun archivo abierto");
}

void MainWindow::on_actionBorrar_triggered()
{
    if(o_file->isOpen()){
        if(fh->fl_size()<=0)
            QMessageBox::warning(this,"Error","Necesita tener al menos un campo para poder crear un registro");
        else{

        }
    }
    else
        QMessageBox::warning(this,"Error","No tiene ningun archivo abierto");
}

void MainWindow::on_actionListar_2_triggered()
{
    if(o_file->isOpen()){
        if(fh->fl_size()<=0)
            QMessageBox::warning(this,"Error","Necesita tener al menos un campo para poder crear un registro");
        else{

        }
    }
    else
        QMessageBox::warning(this,"Error","No tiene ningun archivo abierto");
}

void MainWindow::on_actionCruzar_triggered()
{
    if(o_file->isOpen()){
        if(fh->fl_size()<=0)
            QMessageBox::warning(this,"Error","Necesita tener al menos un campo para poder crear un registro");
        else{

        }
    }
    else
        QMessageBox::warning(this,"Error","No tiene ningun archivo abierto");
}

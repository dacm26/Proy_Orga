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
#include <stdlib.h>
using namespace std;

/*
 Pendiente:
 **Registros --- trabajar con el AL en delete y buscar  records ---
 **Utilidades
 **Indices
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    init=0;
    n_rec=0;
    init_avail=0;
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
    init=0;
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
    if( !(fh->fl_size()<=0 || fh->fl_size()>1000) )
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
        cout << "tam: "<<fh->fl_size()<<endl;
        if((fh->fl_size()<=0 || fh->fl_size()>1000)){
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
        if(!(fh->fl_size()<=0 || fh->fl_size()>1000)){//Si existen campos
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
    init=0;
    if(!o_file->isOpen())
        QMessageBox::warning(this,"Error","No tiene un archivo abierto");
    else{
        QStandardItemModel* model = new QStandardItemModel(1,1,this);//Se crea el modelo para la tabla
        ui->table->setModel(model);
        this->o_file->flush();
        this->o_file->close();
    }
}

void MainWindow::on_actionAbrir_triggered()
{
    FileHeader* fh1=new FileHeader();
    init=0;
    if(this->o_file->isOpen())
        QMessageBox::warning(this,"Error","No se pudo abrir el archivo, porque ya esta uno abierto");
    else{
        QString filename= QFileDialog::getOpenFileName(this,"Open File","/home","*.txt");
        o_file->open(filename.toStdString());
        if(!o_file->isOpen())
            QMessageBox::warning(this,"Error","No se pudo abrir el archivo");
    }
    o_file->seekp(0,ios_base::end);
    if(o_file->tellp()!=1){
            string line;
            o_file->seekg(0,ios_base::beg);
            stringstream ss;
            int j=0;
            field f;
            int toM=0;
            int y=0;
            while(o_file->file.good()){
                getline(o_file->file,line);
                if((line.c_str())[0]=='@'){
                    char* pch;
                    char * writable = new char[line.size() + 1];
                    copy(line.begin()+1, line.end(), writable);
                    writable[line.size()] = '\0';
                    pch= strtok (writable,",");
                    while(pch != NULL){
                        ss << pch;
                        cout << ss.str() << endl;
                        if((atoi(ss.str().c_str())>0) ){
                            cout << "Hay papadas para el AL"<<endl;
                            cout << ss.str() << endl;
                            y=ss.str().size()+1;
                            toM+=y;
                            fh1->addIndex((atoi(ss.str().c_str())));
                        }
                        else{
                            cout << "No hay nada para el AL"<<endl;
                            break;
                        }
                        pch = strtok (NULL, ",");
                        ss.str("");
                    }
                    cout<<"Tamanio AL: " << fh1->getAL().size() << endl;
                    init=o_file->tellg();
                    cout<< "Init: " << init << endl;
                    o_file->seekg(0,ios_base::end);
                    cout << "Donde deberia: " << o_file->tellg() << endl;
                    fh=fh1;
                    cout<< "Length por registro: " << fh->getLength() << endl;
                    if(init<o_file->tellg()){
                        ui->actionCrear->setEnabled(false);
                        ui->actionModificar->setEnabled(false);
                        this->n_rec=(o_file->tellg()-init)/fh->getLength();
                    }
                    init_avail=init-101+toM;
                    cout << "Numero de Records: " << n_rec << endl;
                    o_file->seekp(init_avail,ios_base::beg);
                    cout << "Donde comienza el Avail List: " << init_avail << endl;
                    n_rec-=fh->getAL().size();
                    break;
                }
                else{
                    char* pch;
                    char * writable = new char[line.size() + 1];
                    copy(line.begin(), line.end(), writable);
                    writable[line.size()] = '\0';
                    pch= strtok (writable,",");
                    while(pch != NULL){
                        ss << pch;
                        if (j==0)
                        {
                            f.setName(ss.str());
                            ++j;
                        }
                        else if(j==1){
                            f.setType((ss.str().c_str())[0]);
                            ++j;
                        }
                        else if(j==2){
                            f.setLength(atoi(ss.str().c_str()));
                            ++j;
                        }
                        else if(j==3){
                            f.setDecimal(atoi(ss.str().c_str()));
                            ++j;
                        }
                        else if(j==4){
                            f.setKey(atoi(ss.str().c_str()));
                            j=0;
                        }
                        pch = strtok (NULL, ",");
                        ss.str("");
                    }
                    //cout << "aqui 1"<<endl;
                    delete[] writable;
                    //cout << "aqui 2"<<endl;
                    fh1->addField(f);
                    //cout << "aqui 3"<<endl;
                }
            }
        }
    }

void MainWindow::on_actionIntroducir_triggered()
{
    if(o_file->isOpen()){
        if((fh->fl_size()<=0 || fh->fl_size()>1000))
            QMessageBox::warning(this,"Error","Necesita tener al menos un campo para poder crear un registro");
        else{
            bool key_pass=false;
            ui->actionCrear->setEnabled(false);
            ui->actionModificar->setEnabled(false);
            for(int i=0;i<fh->fl_size();++i){
                if(fh->getFL().at(i).getKey()==1){
                    key_pass=true;
                    fh->fl_size();
                }
            }
            if(!key_pass){
                field f=fh->getFL().at(0);
                f.setKey(1);
                fh->setField(0,f);
            }
            o_file->seekp(0,ios_base::end);
            if(o_file->tellp()==1){
                o_file->writeRecord(fh->toString().c_str(),0,0,fh->toString().size());
                o_file->seekp(0,ios_base::end);
                o_file->seekp(-2,ios_base::cur);
                init=o_file->tellp();
                o_file->seekp(0,ios_base::beg);
            }
            else{
                //Recordar que en el AL se guarda el registro+1 ya que con 0 tira problemas
                string record="0801199076120_______________________CLAUDIA_23F_987654.13";
                o_file->writeRecord(record.c_str(),1,init,record.size());
            }
        }
    }
    else
        QMessageBox::warning(this,"Error","No tiene ningun archivo abierto");
}

void MainWindow::on_actionBuscar_triggered()
{
    if(o_file->isOpen()){
        if((fh->fl_size()<=0 || fh->fl_size()>1000))
            QMessageBox::warning(this,"Error","Necesita tener al menos un campo para poder buscar un registro");
        else{
            if(n_rec==0)
                QMessageBox::warning(this,"Error","Necesita tener al menos un registro para poder buscar");
            stringstream ss;
            ss <<"Hay un total de " << n_rec << " registros. Ingrese el que quiere buscar";
            QString qstr= QString::fromStdString(ss.str());
            ss.str("");
            bool ok=false;
            int rec_bus;
            do{
            rec_bus=QInputDialog::getInt(this,"Buscar Registros",qstr,0,1,n_rec,1,&ok);
            }while(!ok);
            rec_bus=rec_bus-1;
            string record=o_file->readRecord(rec_bus,init,fh->getLength());
            cout << record << endl;
            QStandardItemModel* model = new QStandardItemModel(1,1,this);//Se crea el modelo para la tabla
            //Se crean las columnas de la tabla
            for(int i=0;i<fh->fl_size();++i){
                model->setHorizontalHeaderItem(i,new QStandardItem(QString(QString::fromStdString(fh->getFL().at(i).getName()))));
            }
            qstr="";
            ss.str("");
            string str;
            str=this->toRecord(record);
            cout<< "Record Listo para parsear: " << str << endl;
            char* pch;
            char * writable = new char[str.size() + 1];
            copy(str.begin(), str.end(), writable);
            writable[str.size()] = '\0';
            pch= strtok (writable,",");
            int j=0;
            while(pch != NULL){
                ss << pch;
                qstr= QString::fromStdString(ss.str());
                model->setItem(0,j,new QStandardItem(qstr));
                pch = strtok (NULL, ",");
                ++j;
                ss.str("");
            }
            delete[] writable;
            ui->table->setModel(model);//Asigna el Modelo a la tabla
        }
    }
    else
        QMessageBox::warning(this,"Error","No tiene ningun archivo abierto");
}

string MainWindow::toRecord(string rec){
    stringstream ss;
    int beg=0,end=0,beg2=0,buff_size=1;
    for(int i=0;i<fh->fl_size();++i){
        for(int j=beg;j<rec.size();++j){
            if(rec.at(j)!='_'){
                beg2=j;
                end+=fh->getFL().at(i).getLength();
                beg=end;
                j=rec.size();
            }
        }
        buff_size=end-beg2;
        char buffer[buff_size];
        size_t length=rec.copy(buffer,buff_size,beg2);
        buffer[length]='\0';
        ss << buffer;
        if( !(i==(fh->fl_size()-1)) )
            ss << ',';
    }
    return ss.str();
}

void MainWindow::on_actionBorrar_triggered()
{
    if(o_file->isOpen()){
        if((fh->fl_size()<=0 || fh->fl_size()>1000))
            QMessageBox::warning(this,"Error","Necesita tener al menos un campo para poder borrar un registro");
        else{
            if(n_rec==0)
                QMessageBox::warning(this,"Error","Necesita tener al menos un registro para poder borrar");
            stringstream ss;
            ss <<"Hay un total de " << n_rec << " registros. Ingrese el que quiere eliminar";
            QString qstr= QString::fromStdString(ss.str());
            ss.str("");
            bool ok=false;
            int rec_bus;
            do{
                rec_bus=QInputDialog::getInt(this,"Eliminar Registros",qstr,0,1,n_rec,1,&ok);
            }while(!ok);
            rec_bus=rec_bus-1;
            o_file->deleteRecord(rec_bus,init,fh->getLength());
            const int toS=rec_bus+1;
            cout<< "toS: " << toS << endl;
            fh->addIndex(toS);//Recordar que en el AL se guarda la pos +1;
            ss << toS;
            int digitos=ss.str().size()+1;
            ss << ',';
            o_file->writeRecord(ss.str().c_str(),0,init_avail,digitos);
            init_avail+=digitos;
            --n_rec;
            QMessageBox::information(this,"Info.","Eliminacion con exito");
        }
    }
    else
        QMessageBox::warning(this,"Error","No tiene ningun archivo abierto");
}

void MainWindow::on_actionListar_2_triggered()
{
    if(o_file->isOpen()){
        if((fh->fl_size()<=0 || fh->fl_size()>1000))
            QMessageBox::warning(this,"Error","Necesita tener al menos un campo para poder listar los registros");
        else{
            if(n_rec==0)
                QMessageBox::warning(this,"Error","Necesita tener al menos un registro para poder listar");
            stringstream ss;
            QString qstr;
            ss.str("");
            int rec_bus;
            QStandardItemModel* model = new QStandardItemModel(1,1,this);//Se crea el modelo para la tabla
            //Se crean las columnas de la tabla
            for(int i=0;i<fh->fl_size();++i){
                model->setHorizontalHeaderItem(i,new QStandardItem(QString(QString::fromStdString(fh->getFL().at(i).getName()))));
            }
            int pos=0;
            for(int k=0;k<n_rec+fh->getAL().size();++k){
                rec_bus=k;
                string record=o_file->readRecord(rec_bus,init,fh->getLength());
                if(!(record.at(0)=='*')){
                    qstr="";
                    ss.str("");
                    string str;
                    str=this->toRecord(record);
                    char* pch;
                    char * writable = new char[str.size() + 1];
                    copy(str.begin(), str.end(), writable);
                    writable[str.size()] = '\0';
                    pch= strtok (writable,",");
                    int j=0;
                    while(pch != NULL){
                        ss << pch;
                        qstr= QString::fromStdString(ss.str());
                        model->setItem(pos,j,new QStandardItem(qstr));
                        pch = strtok (NULL, ",");
                        ++j;
                        ss.str("");
                    }
                    delete[] writable;
                    ++pos;
                }
            }
            ui->table->setModel(model);//Asigna el Modelo a la tabla
        }
    }
    else
        QMessageBox::warning(this,"Error","No tiene ningun archivo abierto");
}

void MainWindow::on_actionCruzar_triggered()
{
    if(o_file->isOpen()){
        if((fh->fl_size()<=0 || fh->fl_size()>1000))
            QMessageBox::warning(this,"Error","Necesita tener al menos un campo para poder cruzar un registro");
        else{
            if(n_rec==0)
                QMessageBox::warning(this,"Error","Necesita tener al menos un registro para poder cruzar");
        }
    }
    else
        QMessageBox::warning(this,"Error","No tiene ningun archivo abierto");
}

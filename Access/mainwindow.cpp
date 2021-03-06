#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "field_w.h"
#include "mfields_w.h"
#include "ADTRecordFile.h"
#include "bnode.h"
#include "btree.h"

#include <QMessageBox>
#include <QDebug>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintEngine>
#include <QtPrintSupport/QPrintDialog>
#include <QPainter>
#include <QFileDialog>
#include <QList>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QInputDialog>
#include <QtXml>
#include <QJsonDocument>
#include <QSet>
#include <QStringList>

#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
using namespace std;

/*
 Pendiente:
 **Cruzar
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{//Constructor de la clase
    init=0;
    n_rec=0;
    simple=true;
    arbol=false;
    ui->setupUi(this);
    this->temp=new ADTRecordFile();
    temp->open("temp.txt");
    fh=new FileHeader();
    this->o_file=new ADTRecordFile();
    this->setFixedSize(1370,710);//Se le asigna el tamanio deseado a la ventana principal
    setCentralWidget(ui->table);//La tabla es asignada como la aplicacion central de la aplicacion
    setWindowFlags(Qt::Window|Qt::CustomizeWindowHint|Qt::WindowTitleHint);//No permite que el usuario cierre la ventana
    //ui->table->setEnabled(false);//No permite que el usuario interactue con la tabla

}

MainWindow::~MainWindow()//Destructor de la clase
{
    temp->close();
    o_file->close();
    delete novo;
    delete fh;
    delete temp;
    delete o_file;
    delete ui;
}

void MainWindow::on_actionNuevo_triggered()//Crea un nuevo archivo
{
    init=0;//inicia el inicio de los registros en 0
    if(!o_file->isOpen()){//Si no hay archivos abiertos, se crea el nuevo archivo
        QString filename= QFileDialog::getSaveFileName(this,"Save As","/home");//Filters: Text Files (*.txt)::All Files(*.*)
        this->o_file->open(filename.toStdString());
     }
    else//Sino devuelve un mensaje de error
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
    }else{//Si no tiene un archivo abierto devuelve un mensaje de error
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

void MainWindow::on_actionListar_triggered()//Lista los campos en la tabla central
{
    if(o_file->isOpen()){
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

void MainWindow::on_actionGuardar_triggered()//Guarda el trabajo hecho hasta los momentos
{
    if(!o_file->isOpen())//Si el archivo no esta abierto, levanta un mensaje de error
        QMessageBox::warning(this,"Error","No tiene un archivo abierto");
    else{//Si el archivo esta abierto
        o_file->seekp(0,ios_base::end);
        if(o_file->tellp()==1){
            o_file->writeRecord(fh->toString().c_str(),0,0,fh->toString().size());
            o_file->seekp(0,ios_base::end);
            init=o_file->tellp();
        }
        this->o_file->flush();
    }

}

void MainWindow::on_actionCerrar_triggered()//Cierra el archivo abierto
{
    if(!o_file->isOpen())//si no hay un archivo abierto lanza un mensaje de error
        QMessageBox::warning(this,"Error","No tiene un archivo abierto");
    else{//sino hace compactacion del archivo y cierra el archivo
        //Verifica si el archivo temporal tiene datos
        this->o_file->seekp(0,ios_base::beg);
        this->o_file->seekg(0,ios_base::beg);
        this->temp->seekp(0,ios_base::end);
        if(temp->tellp()==1){//Si no tiene ubica el puntero al principio
            this->temp->seekg(0,ios_base::beg);
            this->temp->seekp(0,ios_base::beg);
        }
        else{//si el archivo tiene datos, se trunca la informacion
            temp->close();
            temp->file.open("temp.txt",ios_base::out|ios_base::trunc);
            temp->close();
            temp->file.open("temp.txt",fstream::out);
            temp->file.flush();
            temp->file.close();
            temp->file.open("temp.txt", fstream::in | fstream::out);
            this->temp->seekg(0,ios_base::beg);
            this->temp->seekp(0,ios_base::beg);

        }
        temp->writeRecord(fh->toString().c_str(),0,0,fh->toString().size());//se escribe el FH en el archivo temporal
        string x;
        int lol=0;
        for(int i=0;i<n_rec;++i){//Se lee el archivo abierto y si contiene un * no se copia al archivo temporal
            x=this->o_file->readRecord(lol,init,fh->getLength());
            if( (x.c_str())[0] == '*' ){
                --i;
            }
            else{
                if( !((x.c_str())[0]==' '))
                    temp->writeRecord(x.c_str(),-1,init,fh->getLength());
            }
            ++lol;
        }
        //Copia el Archivo Temporal al Archivo Original
        temp->flush();
        x=o_file->filename;
        this->o_file->close();
        this->o_file->file.open(x.c_str(),ios_base::out|ios_base::trunc);
        this->o_file->file.close();
        this->o_file->file.open(x.c_str(),fstream::out);
        this->o_file->file.close();
        this->o_file->file.open(x.c_str(), fstream::in | fstream::out);
        this->o_file->seekg(0,ios_base::beg);
        this->o_file->seekp(0,ios_base::beg);
        temp->seekp(0,ios_base::end);
        int y=temp->tellp();
        char buffer[y];
        temp->seekg(0,ios_base::beg);
        temp->file.read(buffer,y);
        o_file->file.write(buffer,y);
        o_file->seekg(0,ios_base::beg);
        o_file->seekp(0,ios_base::beg);
        ui->table->setModel(NULL);
        ui->actionCrear->setEnabled(true);
        ui->actionModificar->setEnabled(true);
        this->o_file->flush();
        this->o_file->close();
        init=0;
        indices.clear();
        delete fh;
        fh= new FileHeader();
    }
}

void MainWindow::on_actionAbrir_triggered()//Abre el archivo deseado
{
    FileHeader* fh1=new FileHeader();
    init=0;
    if(this->o_file->isOpen())
        QMessageBox::warning(this,"Error","No se pudo abrir el archivo, porque ya esta uno abierto");
    else{
        QString filename= QFileDialog::getOpenFileName(this,"Open File","/home","*.txt");
        o_file->open(filename.toStdString());
        if(!o_file->isOpen()){
            QMessageBox::warning(this,"Error","No se pudo abrir el archivo");
        }
    }
    o_file->seekp(0,ios_base::end);
    if(o_file->tellp()!=1){//Si el archivo contiene Registros y campos
            string line;
            o_file->seekg(0,ios_base::beg);
            stringstream ss;
            int j=0;
            field f;
            while(o_file->file.good()){//Parsea el Archivo
                getline(o_file->file,line);
                if((line.c_str())[0]=='@'){//Llego a Registros y comienza a parsear registros
                    init=o_file->tellg();
                    o_file->seekg(0,ios_base::end);
                    fh=fh1;
                    if(init<o_file->tellg()){
                        ui->actionCrear->setEnabled(false);
                        ui->actionModificar->setEnabled(false);
                        this->n_rec=(o_file->tellg()-init)/fh->getLength();
                    }
                    break;
                }
                else{//Parsea los campos por su determinado delimitador
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
                    delete[] writable;
                    fh1->addField(f);
                }
            }
            makeSimpleIndex();
        }
    }

void MainWindow::on_actionIntroducir_triggered()//Adiciona un registro al archivo
{
    if(o_file->isOpen()){
        if((fh->fl_size()<=0 || fh->fl_size()>1000))
            QMessageBox::warning(this,"Error","Necesita tener al menos un campo para poder crear un registro");
        else{
            string z1;
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
            int where=0;
            o_file->seekp(0,ios_base::end);
            if(o_file->tellp()==1){
                o_file->writeRecord(fh->toString().c_str(),0,0,fh->toString().size());
                o_file->seekp(0,ios_base::end);
                where=-2;
                init=o_file->tellp();
            }
            //Recordar que en el AL se guarda el registro+1 ya que con 0 tira problemas
            //string record="0801199076110_______________________CLAUDIA_23F_987654.13";
            stringstream ss,ss1;
            int x;
            double y;
            string z;
            bool ok;
            int toFill=0;
            int pos1=0;
            for(int i=0; i<fh->fl_size();++i){
                if( (fh->getFL().at(i)).getKey() == 1){
                    pos1=i;
                    break;
                }
            }
             stringstream ss2;
            for(int i=0;i<fh->fl_size();++i){
                ok=false;
                ss2.str("");
                if(fh->getFL().at(i).getType()=='0'){
                    ss1<< "Ingrese "<< fh->getFL().at(i).getName();
                    string asd=ss1.str();
                    string other="";
                    ss1.str("");
                    do{
                        x=QInputDialog::getInt(this,"Add Record",(QString::fromStdString(asd)),0,0,99999999999999999999,1,&ok);
                        ss2.str("");
                        ss2 << x;
                        if(i==pos1 && (indices.contains(ss2.str()) || tree.search_Key(tree.getRoot(),ss2.str()) != -1)){
                            ok=false;
                        }
                        if(ok){
                            ss1 << x;
                            if(ss1.str().size()>fh->getFL().at(i).getLength())
                                ok=false;
                            else if(ss1.str().size()<fh->getFL().at(i).getLength()){
                                other=ss1.str();
                                ss1.str("");
                                toFill=fh->getFL().at(i).getLength()-other.size();
                                for(int i=0;i<toFill;++i)
                                    ss << '_';
                                //ss << setfill('_')<<setw(toFill);
                                ss << other;
                                stringstream ss3;
                                ss3 << x;
                                z1=ss3.str();
                            }
                            else{
                                ss << x;
                                stringstream ss3;
                                ss3 << x;
                                z1=ss3.str();
                            }
                            ss1.str("");
                        }
                        else{
                            QMessageBox::warning(this,"Error","Ya tiene un registro con ese atributo");
                        }
                    }while(!ok);
                }
                else if(fh->getFL().at(i).getType()=='1'){
                    ss1<< "Ingrese "<< fh->getFL().at(i).getName();
                    string other="";
                    do{
                        y=QInputDialog::getDouble(this,"Add Record",(QString::fromStdString(ss1.str())),0,0,99999999999999999999.99,fh->getFL().at(i).getDecimal(),&ok);
                        ss2.str("");
                        ss2 << y;
                        if(i==pos1 && (indices.contains(ss2.str()) || tree.search_Key(tree.getRoot(),ss2.str()) != -1)){
                            ok=false;
                        }
                        if(ok){
                            ss1.str("");
                            ss1 << y;
                            if(ss1.str().size()>fh->getFL().at(i).getLength())
                                ok=false;
                            else if(ss1.str().size()<fh->getFL().at(i).getLength()){
                                other=ss1.str();
                                toFill=fh->getFL().at(i).getLength()-other.size();
                                for(int i=0;i<toFill;++i)
                                    ss << '_';
                                ss << other;
                                stringstream ss3;
                                ss3 << y;
                                z1=ss3.str();
                            }
                            else{
                                ss << y;
                                stringstream ss3;
                                ss3 << y;
                                z1=ss3.str();
                            }
                            ss1.str("");
                        }
                        else{
                            QMessageBox::warning(this,"Error","Ya tiene un registro con ese atributo");
                        }
                    }while(!ok);
                    ss1.str("");
                }
                else{
                    ss1<< "Ingrese "<< fh->getFL().at(i).getName();
                    string asd=ss1.str();
                    string other="";
                    ss1.str("");
                    do{
                        QString text = QInputDialog::getText(this, ("Add Record"),
                                                             (QString::fromStdString(asd)), QLineEdit::Normal,
                                                             QDir::home().dirName(), &ok);
                        z=text.toStdString();
                        ss2.str("");
                        ss2 << z;
                        if(i==pos1 && (indices.contains(ss2.str()) || tree.search_Key(tree.getRoot(),ss2.str()) != -1)){
                            ok=false;
                        }
                        if(ok){
                            ss1 << z;

                            if(ss1.str().size()>fh->getFL().at(i).getLength())
                                ok=false;
                            else if(ss1.str().size()<fh->getFL().at(i).getLength()){
                                other=ss1.str();
                                ss1.str("");
                                toFill=fh->getFL().at(i).getLength()-other.size();
                                for(int i=0;i<toFill;++i)
                                    ss << '_';
                                ss << other;
                                z1=z;
                            }
                            else{
                                ss << z;
                                z1=z;
                            }
                            ss1.str("");
                        }
                        else{
                            QMessageBox::warning(this,"Error","Ya tiene un registro con ese atributo");
                        }
                    }while(!ok);
                    ss1.str("");
                }
            }
            if(where==-2){
                o_file->writeRecord(ss.str().c_str(),where,init,fh->getLength());
                //cout  << "VALUE: " << n_rec << endl;
                //indices.insert(z1,n_rec);
            }
            else{
                int pos1=fh->getIndex();
                o_file->writeRecord(ss.str().c_str(),pos1,init,fh->getLength());
                /*if(pos1 == -1){
                    cout << "El if: "<<endl;
                    cout  << "VALUE: " << n_rec << endl;
                    cout << "Tamanio 1: " << indices.values().size() << endl;
                    indices.insert(z1,n_rec);
                    cout << "Tamanio 2: " << indices.values().size() << endl;
                }
                else{
                    cout << "El else: "<<endl;
                    cout  << "VALUE: " << pos1 << endl;
                    cout << "Tamanio 1: " << indices.values().size() << endl;
                    indices.insert(z1,pos1);
                    cout << "Tamanio 2: " << indices.values().size() << endl;
                }
                */

           }
            ++n_rec;
            if(arbol){
                indices.clear();
                makeSimpleIndex();
                on_actionCrear_Indices_Arbol_B_triggered();
            }
            else{
                indices.clear();
                makeSimpleIndex();
            }
            /*QList<int> asd=indices.values();
            QList <string> asd1=indices.keys();
            cout<< "Tamanio: " << asd.size() << endl;
            for(int i=0; i < asd.size() ; ++i)
                cout << asd1.at(i) << '\t' << asd.at(i) << endl;*/
        }
    }else
        QMessageBox::warning(this,"Error","No tiene ningun archivo abierto");
}

void MainWindow::on_actionBuscar_triggered()//Busca un Registro
{
    if(o_file->isOpen()){
        if((fh->fl_size()<=0 || fh->fl_size()>1000))
            QMessageBox::warning(this,"Error","Necesita tener al menos un campo para poder buscar un registro");
        else{
            if(indices.size()==0)
                QMessageBox::warning(this,"Error","Necesita tener al menos un registro para poder buscar");
            else{
                stringstream ss;
                ss <<"Ingrese el registro que desea buscar";
                QString qstr= QString::fromStdString(ss.str());
                string asd=ss.str();
                ss.str("");
                bool ok=false;
                string z1;
                do{
                    QString text = QInputDialog::getText(this, ("Find Record"),
                                                         (QString::fromStdString(asd)), QLineEdit::Normal,
                                                         QDir::home().dirName(), &ok);
                    z1=text.toStdString();
                }while(!ok);
                bool in=false;
                int val;
                if(simple){
                    in=indices.contains(z1);
                    val=indices.value(z1);
                }
                if(arbol){
                    val=tree.search_Key(tree.getRoot(),z1);
                    if(val==-1)
                        in=false;
                    else{
                        in=true;
                    }
                }
                if(in){
                    string record=o_file->readRecord(val,init,fh->getLength());
                    QStandardItemModel* model = new QStandardItemModel(1,1,this);//Se crea el modelo para la tabla
                    //Se crean las columnas de la tabla
                    for(int i=0;i<fh->fl_size();++i){
                        model->setHorizontalHeaderItem(i,new QStandardItem(QString(QString::fromStdString(fh->getFL().at(i).getName()))));
                    }
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
                        model->setItem(0,j,new QStandardItem(qstr));
                        pch = strtok (NULL, ",");
                        ++j;
                        ss.str("");
                    }
                    delete[] writable;
                    ui->table->setModel(model);//Asigna el Modelo a la tabla
                }
                else{
                    QMessageBox::warning(this,"Error","No tiene ningun registro con ese atributo");
                }
            }
        }
    }
    else
        QMessageBox::warning(this,"Error","No tiene ningun archivo abierto");
}

string MainWindow::toRecord(string rec){//Aniade el espacio necesario para que el registro sea del tamanio adecuado
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

void MainWindow::on_actionBorrar_triggered()//Elimina un registro
{
    if(o_file->isOpen()){
        if((fh->fl_size()<=0 || fh->fl_size()>1000))
            QMessageBox::warning(this,"Error","Necesita tener al menos un campo para poder borrar un registro");
        else{
            if(indices.size()==0)
                QMessageBox::warning(this,"Error","Necesita tener al menos un registro para poder borrar");
            else{
                stringstream ss;
                ss <<"Ingrese el registro que desea Eliminar";
                string asd=ss.str();
                ss.str("");
                bool ok=false;
                string z1;
                do{
                    QString text = QInputDialog::getText(this, ("Delete Record"),
                                                         (QString::fromStdString(asd)), QLineEdit::Normal,
                                                         QDir::home().dirName(), &ok);
                    z1=text.toStdString();
                }while(!ok);
                bool in=false;
                int val;
                if(simple){
                    in=indices.contains(z1);
                    val=indices.value(z1);
                    if(in)
                        indices.remove(z1);
                }
                else{
                    indices.clear();
                    makeSimpleIndex();
                    in=indices.contains(z1);
                    val=indices.value(z1);
                    if(in)
                        indices.remove(z1);
                }
                /*if(arbol){
                    val=tree.remove(z1);
                    if(val==-1)
                        in=false;
                    else{
                        in=true;
                    }
                }*/
                if(in){
                    o_file->deleteRecord(val,init,fh->getLength());
                    fh->addIndex(val);//Recordar que en el AL se guarda la pos +1;
                    --n_rec;
                    QMessageBox::information(this,"Info.","Eliminacion con exito");
                }
                else{
                    QMessageBox::warning(this,"Error","No tiene ningun registro con ese atributo");
                }
            }
        }
    }
    else
        QMessageBox::warning(this,"Error","No tiene ningun archivo abierto");
}

void MainWindow::on_actionListar_2_triggered()//Lista los registros
{
    if(o_file->isOpen()){
        if((fh->fl_size()<=0 || fh->fl_size()>1000))
            QMessageBox::warning(this,"Error","Necesita tener al menos un campo para poder listar los registros");
        else{
            if(indices.size()==0)
                QMessageBox::warning(this,"Error","Necesita tener al menos un registro para poder listar");
            stringstream ss;
            QString qstr;
            ss.str("");
            QStandardItemModel* model = new QStandardItemModel(1,1,this);//Se crea el modelo para la tabla
            //Se crean las columnas de la tabla
            for(int i=0;i<fh->fl_size();++i){
                model->setHorizontalHeaderItem(i,new QStandardItem(QString(QString::fromStdString(fh->getFL().at(i).getName()))));
            }
            int pos=0;
            if(arbol){
                indices.clear();
                makeSimpleIndex();
            }
            QList<string> asd=indices.keys();
            for(int k=0;k<asd.size();++k){
                string record=o_file->readRecord(indices.value(asd.at(k)),init,fh->getLength());
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
            ui->table->setModel(model);//Asigna el Modelo a la tabla
        }
    }
    else
        QMessageBox::warning(this,"Error","No tiene ningun archivo abierto");
}

void MainWindow::on_actionCruzar_triggered()//Cruza dos archivos
{
    if(o_file->isOpen()){
        if(n_rec != 0){
            QList<int> intersection;
            fstream file;
            indices.clear();
            makeSimpleIndex();
            file.open("empleados.txt",fstream::in | fstream::out);
            string line;
            stringstream ss;
            while(file.good()){//Parsea el Archivo
                getline(file,line);
                cout << line << endl;
                for(int i=0; i<line.size();++i){
                    if( (line.c_str())[i]==',' )
                        i=line.size();
                    else
                        ss << (line.c_str())[i];
                }
                if(indices.contains(ss.str()))
                    intersection.push_back(indices.value(ss.str()));
                ss.str("");
            }
            file.close();
            if(intersection.size() == 0 ){
                QMessageBox::information(this,"Info","No hay registros en comun");
            }
            else{
                file.open("intersection.txt",fstream::out);
                string rec;
                for(int i=0; i<intersection.size();++i){
                    rec=o_file->readRecord(intersection.at(i),init,fh->getLength());
                    file.write(rec.c_str(),rec.size());
                }
                file.flush();
                file.close();
                QMessageBox::information(this,"Info","Hay registros en comun se copiaran los registros a un nuevo archivo");
            }
        }
        else
            QMessageBox::warning(this,"Error","No tiene ningun registro");
    }
    else
        QMessageBox::warning(this,"Error","No tiene ningun archivo abierto");
}

void MainWindow::on_actionImprimir_triggered()//Imprime en pdf los registros
{
    if(o_file->isOpen()){
        if((fh->fl_size()<=0 || fh->fl_size()>1000))
            QMessageBox::warning(this,"Error","Necesita tener al menos un campo para poder imprimir");
        else{
            QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"untitled",tr("PDF Document (*.pdf)"));
            QString field_Table = "";
            stringstream ss;
            field_Table += "<table border=\"2\">";
            field_Table += "<tr>";
            for(int i=0; i < fh->fl_size(); ++i){
                field_Table += QString::fromStdString(string("<th>")) + QString::fromStdString(fh->getFL().at(i).getName()) + QString::fromStdString(string("</th>"));
            }
            QList<string> asd=indices.keys();
            for(int i=0; i < asd.size();++i){
                field_Table += "<tr>";
                string record=o_file->readRecord(indices.value(asd.at(i)),init,fh->getLength());
                ss.str("");
                string str;
                str=this->toRecord(record);
                char* pch;
                char * writable = new char[str.size() + 1];
                copy(str.begin(), str.end(), writable);
                writable[str.size()] = '\0';
                pch= strtok (writable,",");
                while(pch != NULL){
                    ss << pch;
                    field_Table += QString::fromStdString(string("<td>")) + QString::fromStdString(ss.str()) + QString::fromStdString(string("</td>"));
                    pch = strtok (NULL, ",");
                    ss.str("");
                }

                delete[] writable;
                ss.str("");

                field_Table += "</tr>";
            }
            field_Table += "</table>";
            QTextDocument doc;
            doc.setHtml(field_Table);
            QPrinter printer;
            printer.setOutputFileName(fileName);
            printer.setOutputFormat(QPrinter::PdfFormat);
            doc.print(&printer);
            printer.newPage();
        }
    }
    else
        QMessageBox::warning(this,"Error","No tiene ningun archivo abierto");

}

void MainWindow::makeSimpleIndex(){//Crea los Indices SImples
    int pos1=0;
    for(int i=0; i<fh->fl_size();++i){
        if( (fh->getFL().at(i)).getKey() == 1){
            pos1=i;
            break;
        }
    }
    QString qstr;
    stringstream ss;
    for(int k=0;k<n_rec;++k){
        string record=o_file->readRecord(k,init,fh->getLength());
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
                if(pos1==j){
                    ss << pch;
                    break;
                }
                pch = strtok (NULL, ",");
                ++j;
            }
            delete[] writable;
            indices.insert(ss.str(),k);
        }
    }
}

void MainWindow::on_actionCrear_Indices_Simples_triggered()//Crea los indices simples
{
    makeSimpleIndex();
    simple=true;
    arbol=false;
}

void MainWindow::on_actionReindexar_triggered()//Vuelve a crear los indices
{
    makeSimpleIndex();
    simple=true;
    arbol=false;
}

void MainWindow::on_actionExportar_XML_triggered()//Exporta el archivo a XML
{
    if(o_file->isOpen()){
        if(indices.size() !=0){
            if(arbol){
                indices.clear();
                makeSimpleIndex();
            }
            QDomDocument document;
            stringstream ss,ss1;
            QDomElement root = document.createElement("DB");
            document.appendChild(root);
            for(int i=0; i<fh->fl_size();++i){
                QDomElement field = document.createElement("Field");
                //field.setAttribute(QString::fromStdString("N"), QString::number(i));
                root.appendChild(field);
                QDomElement atributo = document.createElement("F_Atributos");
                atributo.setAttribute("Nombre",QString::fromStdString(fh->getFL().at(i).getName()));
                ss << fh->getFL().at(i).getType();
                atributo.setAttribute("Tipo",QString::fromStdString(ss.str()));
                ss.str("");
                ss << fh->getFL().at(i).getDecimal();
                atributo.setAttribute("Decimal",QString::fromStdString(ss.str()));
                ss.str("");
                ss << fh->getFL().at(i).getLength();
                atributo.setAttribute("Longitud",QString::fromStdString(ss.str()));
                ss.str("");
                ss << fh->getFL().at(i).getKey();
                atributo.setAttribute("LLave",QString::fromStdString(ss.str()));
                ss.str("");
                field.appendChild(atributo);

            }
            //Add Records
            ss.str("");
            QList<string> ids=indices.keys();
            for(int i = 0; i < indices.size(); i++)
            {
                QDomElement record = document.createElement("Record");
                //record.setAttribute(QString::fromStdString("N"), QString::number(i));
                ss.str("");
                root.appendChild(record);
                QList<string>attr;
                string record1=o_file->readRecord(indices.value(ids.at(i)),init,fh->getLength());
                ss.str("");
                string str;
                str=this->toRecord(record1);
                char* pch;
                char * writable = new char[str.size() + 1];
                copy(str.begin(), str.end(), writable);
                writable[str.size()] = '\0';
                pch= strtok (writable,",");
                while(pch != NULL){
                    ss1 << pch;
                    attr.push_back(ss1.str());
                    ss1.str("");
                    pch = strtok (NULL, ",");
                }
                delete[] writable;
                QDomElement atributo = document.createElement("R_Atributos");
                for(int h = 0; h < attr.size(); h++)
                {
                    atributo.setAttribute(QString::fromStdString(fh->getFL().at(h).getName()), QString::fromStdString(attr.at(h)));
                }
                record.appendChild(atributo);
            }
            //Write to file
            QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"untitled",tr("XML Document (*.xml)"));
            ofstream file(fileName.toStdString().c_str());
            file << (document.toString()).toStdString().c_str();
            file.close();
        }
        else{
            QMessageBox::warning(this,"Error","Necesita tener al un registro para poder exportar");
        }
    }
    else
        QMessageBox::warning(this,"Error","Necesita tener un archivo abierto para poder exportar");
}

void MainWindow::on_actionExportar_Json_triggered()//Exporta el archivo a Json
{
    if(o_file->isOpen()){
        if(indices.size() !=0){
            if(arbol){
                indices.clear();
                makeSimpleIndex();
            }
            QJsonDocument doc;
            QJsonObject root;
            stringstream ss,ss1;
            QList<string> ids=indices.keys();
            for(int i=0; i< fh->fl_size(); i++){
                QJsonObject a;
                QJsonValue value(QString::fromStdString(fh->getFL().at(i).getName()));
                a.insert(QString::fromStdString("Name"),value);
                ss << fh->getFL().at(i).getType();
                QJsonValue value1(QString::fromStdString(ss.str()));
                a.insert(QString::fromStdString("Type"),value1);
                ss.str("");
                ss << fh->getFL().at(i).getDecimal();
                QJsonValue value2(QString::fromStdString(ss.str()));
                a.insert(QString::fromStdString("Decimal"),value2);
                ss.str("");
                ss << fh->getFL().at(i).getLength();
                QJsonValue value3(QString::fromStdString(ss.str()));
                a.insert(QString::fromStdString("Length"),value3);
                ss.str("");
                ss << fh->getFL().at(i).getKey();
                QJsonValue value4(QString::fromStdString(ss.str()));
                a.insert(QString::fromStdString("Key"),value4);
                ss.str("");
                root.insert("Field "+QString::number(i),a);
                ss.str("");
            }

            for(int i=0; i < indices.size(); ++i){
                QJsonObject a;
                QList<string>attr;
                string record1=o_file->readRecord(indices.value(ids.at(i)),init,fh->getLength());
                ss.str("");
                string str;
                str=this->toRecord(record1);
                char* pch;
                char * writable = new char[str.size() + 1];
                copy(str.begin(), str.end(), writable);
                writable[str.size()] = '\0';
                pch= strtok (writable,",");
                while(pch != NULL){
                    ss1 << pch;
                    attr.push_back(ss1.str());
                    ss1.str("");
                    pch = strtok (NULL, ",");
                }
                delete[] writable;
                for(int j=0;j<fh->fl_size();++j){
                    QJsonValue value(QString::fromStdString(attr.at(j)));
                    a.insert(QString::fromStdString(fh->getFL().at(j).getName()),value);
                }
                root.insert("Record "+QString::number(i),a);
            }
                doc.setObject(root);
                QString qwe=doc.toJson();
                QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"untitled",tr("Json Document (*.json)"));
                ofstream file(fileName.toStdString().c_str());
                file << (qwe).toStdString().c_str();
                file.close();
        }
        else{
            QMessageBox::warning(this,"Error","Necesita tener al un registro para poder exportar");
        }
    }
    else
        QMessageBox::warning(this,"Error","Necesita tener un archivo abierto para poder exportar");
}

void MainWindow::on_actionImportar_XML_triggered()//Importa el archivo a XML
{
    if(!o_file->isOpen()){
        on_actionNuevo_triggered();
        QDomDocument document;
        QString filename= QFileDialog::getOpenFileName(this,"Open File","/home","*.xml");
        //Load the file
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            cout << "Failed to open file" << endl;
            return ;
        }
        else
        {
            if(!document.setContent(&file))
            {
                cout << "Failed to load file" << endl;
                return ;
            }
            file.close();
        }
        QDomElement root = document.firstChildElement();
        QDomNodeList fields = root.elementsByTagName("Field");
        for(int i = 0; i < fields.count(); i++)
        {
            QDomNode fieldnode = fields.at(i);
            //convert to an element
            if(fieldnode.isElement())
            {
                QDomElement Field = fieldnode.toElement();
                string name;
                char type;
                int length,decimal,key;
                name=getElement(Field,"F_Atributos","Nombre");
                type=(getElement(Field,"F_Atributos","Tipo").c_str())[0];
                length=atoi((getElement(Field,"F_Atributos","Longitud").c_str()));
                decimal=atoi((getElement(Field,"F_Atributos","Decimal").c_str()));
                key=atoi((getElement(Field,"F_Atributos","LLave").c_str()));
                field f(name,type,length,decimal,key);
                fh->addField(f);
            }
        }
        o_file->writeRecord(fh->toString().c_str(),0,0,fh->toString().size());
        o_file->seekp(0,ios_base::end);
        init=o_file->tellp();
        QDomNodeList records = root.elementsByTagName("Record");
        stringstream ss;
        for(int i = 0; i < records.count(); i++)
        {
            QDomNode recordnode = records.at(i);
            //convert to an element
            if(recordnode.isElement())
            {
                QDomElement RECORD = recordnode.toElement();
                for(int j=0; j<fh->fl_size();++j){
                    if(getElement(RECORD,"R_Atributos",QString::fromStdString(fh->getFL().at(j).getName())).size()<fh->getFL().at(j).getLength()){
                        int toFill=fh->getFL().at(j).getLength()-getElement(RECORD,"R_Atributos",QString::fromStdString(fh->getFL().at(j).getName())).size();
                        for(int k=0;k<toFill;++k)
                            ss << "_";
                        ss << getElement(RECORD,"R_Atributos",QString::fromStdString(fh->getFL().at(j).getName()));
                    }
                    else{
                        ss << getElement(RECORD,"R_Atributos",QString::fromStdString(fh->getFL().at(j).getName()));
                    }
                }
                if(o_file->writeRecord(ss.str().c_str(),-2,init,ss.str().size()))
                    cout << "Se guardo el registro"<<endl;
                else{
                    cout << "NO se pudo guardar el registro"<<endl;

                }
                ss.str("");
            }
        }
        o_file->file.flush();
        o_file->close();
        delete fh;
        fh=new FileHeader();
    }
    else
        QMessageBox::warning(this,"Error","No tiene que tener archivos abiertos para poder importar");
}

string MainWindow::getElement(QDomElement root, QString tagname, QString attribute)//Obtiene un atributo de un archivo xml
{
    QDomNodeList items = root.elementsByTagName(tagname);
     for(int i = 0; i < items.count(); i++)
     {
        QDomNode itemnode = items.at(i);

        //convert to element
        if(itemnode.isElement())
        {
            QDomElement itemele = itemnode.toElement();
            return itemele.attribute(attribute).toStdString();
        }
     }
}

void MainWindow::on_actionImportal_Json_triggered()//importa un archivo json
{
    if(!o_file->isOpen()){
        on_actionNuevo_triggered();
        QString filename= QFileDialog::getOpenFileName(this,"Open File","/home","*.json");
        QString inFile;
        QFile file(filename);
        if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            cout << "Failed to open file" << endl;
            return ;
        }
        else
        {
            inFile = file.readAll();
            file.close();
            QJsonDocument doc=QJsonDocument::fromJson(inFile.toUtf8());
            QJsonObject root=doc.object();
            if(root.isEmpty()){
                QMessageBox::warning(this, "Error", "El archivo esta vacio");
                return ;
            }
            QStringList stuff=root.keys();
            for(int i=0; i<stuff.size();++i){
                if (stuff[i].contains(QString::fromStdString("Field"), Qt::CaseInsensitive)) {//QT::caseInsensitive compara un string ignorando mayusculas y minusculas
                    QJsonObject obj = root[stuff[i]].toObject();
                    QStringList atrib = obj.keys();
                    string name;
                    char type;
                    int decimal;
                    int length;
                    int key;

                    for (int j = 0; j < atrib.size(); j++) {

                        if (atrib[j] == "Name") {
                            name = obj[atrib[j]].toString().toStdString();
                        } else if (atrib[j] == "Type") {
                            type = ((obj[atrib[j]].toString().toStdString()).c_str())[0];
                        } else if (atrib[j] == "Length") {
                            length = obj[atrib[j]].toString().toInt();
                        } else if (atrib[j] == "Decimal") {
                            decimal = obj[atrib[j]].toString().toInt();
                        } else if (atrib[j] == "Key") {
                            key = obj[atrib[j]].toString().toInt();
                        } else {
                            QMessageBox::warning(this, "Error", "No tiene Campos en el Archivo");
                            return;
                        }
                    }
                    field f(name,type,length,decimal,key);
                    fh->addField(f);
                }
            }
            o_file->writeRecord(fh->toString().c_str(),0,0,fh->toString().size());
            o_file->seekp(0,ios_base::end);
            init=o_file->tellp();
            stringstream ss;
            for (int i = 0; i < stuff.size(); i++) {
                if (stuff[i].contains(QString::fromStdString("Record"), Qt::CaseInsensitive)) {
                    QJsonObject obj = root[stuff[i]].toObject();
                    QStringList atrib = obj.keys();
                    for (int j = 0; j < fh->fl_size(); j++) {
                        int p = atrib.indexOf(QString::fromStdString(fh->getFL().at(j).getName()));
                        string atr=(obj[atrib[p]].toString().toStdString());
                        if(atr.size()<fh->getFL().at(j).getLength()){
                            int asd=fh->getFL().at(j).getLength()-atr.size();
                            for(int h=0; h< asd;++h)
                                ss << "_";
                        }
                        ss << atr;
                    }
                    if(o_file->writeRecord(ss.str().c_str(),-2,init,ss.str().size()))
                        cout << "Se guardo el registro"<<endl;
                    else{
                        cout << "NO se pudo guardar el registro"<<endl;

                    }
                }
                ss.str("");
            }
            o_file->file.flush();
            o_file->close();
            delete fh;
            fh=new FileHeader();
        }
    }
        else
        QMessageBox::warning(this,"Error","No tiene que tener archivos abiertos para poder importar");
}

void MainWindow::on_actionCrear_Indices_Arbol_B_triggered()
{
    if(o_file->isOpen()){
        if(n_rec !=0){
            QList<string>keys=indices.keys();
            QList<int>values=indices.values();
            for(int i=0;i<keys.size();++i){
                tree.insert(keys.at(i),values.at(i));
            }
            simple=false;
            arbol=true;
        }
        else{
            QMessageBox::warning(this,"Error","Debe tener un archivo con registros");
        }
    }
    else{
        QMessageBox::warning(this,"Error","Debe tener un archivo abierto y con registros");
    }
}


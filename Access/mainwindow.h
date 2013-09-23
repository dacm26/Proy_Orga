#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "field_w.h"
#include <QMainWindow>
#include <vector>
#include <QMap>
#include <string>
#include <QtXml>
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
    explicit MainWindow(QWidget *parent = 0);//Constructor de la ventana Principal
    string toRecord(string);//Metodo para aniadar el espacio necesario para que el archivo sea de longitud fija
    void makeSimpleIndex();//Crea el Indice Simple
    string getElement(QDomElement, QString, QString );//Obtiene un Atributo de un archivo xml
    ~MainWindow();//Destructor de la ventana principal

private slots:
    void on_actionNuevo_triggered();//Crea un nuevo archivo
    void on_actionCrear_triggered();//Crea un campo
    void on_actionSalir_triggered();//Sale del programa
    void on_actionListar_triggered();//Lista los campos existentes
    void on_actionModificar_triggered();//Modifica los campos existentes
    void on_actionGuardar_triggered();//Guarda el trabajo realizado hasta el momento
    void on_actionCerrar_triggered();//Cierra el archivo abierto
    void on_actionAbrir_triggered();//Abre un archivo
    void on_actionIntroducir_triggered();//Crea un registro
    void on_actionBuscar_triggered();//Busca un registro
    void on_actionBorrar_triggered();//Elimina un registro
    void on_actionListar_2_triggered();//Lista los registros
    void on_actionCruzar_triggered();//Interseccion de dos archivos
    void on_actionImprimir_triggered();//imprime en pdf los registros del archivo
    void on_actionCrear_Indices_Simples_triggered();//Crea los indices simples
    void on_actionReindexar_triggered();//Vuelve a crear los indices
    void on_actionExportar_XML_triggered();//Exporta el archivo en xml
    void on_actionExportar_Json_triggered();//Exporta el archivo en json
    void on_actionImportar_XML_triggered();//Importa el archivo en xml
    void on_actionImportal_Json_triggered();//Importa el archivo en json

public:
    Ui::MainWindow *ui;//Ventana Principal
    field_W *novo;//Ventana de crear campos
    FileHeader *fh;//File Header del Archivo
    ADTRecordFile* o_file;//Archivo de Registros
    ADTRecordFile* temp;//Archivo temporal para compactar
    QMap<string,int> indices;//Indices Simples
    int init;//Inicio de los registros en el archivo
    int n_rec;//Numero de Registros en el archivo
};

#endif // MAINWINDOW_H

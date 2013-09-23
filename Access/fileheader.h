#ifndef FILEHEADER_H
#define FILEHEADER_H

#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include "field.h"

using namespace std;

class FileHeader {

private:
    stack<int> availList;//Contiene los registros eliminados
    vector<field> fieldlist;//contiene los campos del archivo

public:
    FileHeader();//constructor de la clase
    ~FileHeader();//destructor de la clase
    void setAL(stack<int>);//Setea el nuevo AL
    void setField(int,field);//setea un nuevo field
    stack<int> getAL();//devuelve el AL
    void addField ( field );//Agrega un campo
    int fl_size()const;//devuelve el tamanio del FL
    vector<field> getFL()const;//devuelve el FL
    void removeField ( const int );//elimina un campo
    const int getLength () const;//obtiene la longitud por registro
    void addIndex ( const int );//agrega un rrn al AL
    int getIndex() ; //Obtiene el ultimo rrn del AL
    string toString();//Devuelve el FH del archivo
	
};

#endif

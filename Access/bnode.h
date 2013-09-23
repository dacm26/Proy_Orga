#ifndef BNODE_H
#define BNODE_H

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <stddef.h>
#include <sstream>
#include <vector>
#include "key.h"

using namespace std;

class BNode {

private:
    BNode* parent; //padre del nodo
    BNode* pointers[5]; //arreglo de hijos
    Key keys[4]; //llaves
    int keycount; //contador de llaves
    bool isleaf; //dice si es hoja
public:
    BNode();//constructor de la clase
    ~BNode();//destructor de la clase
    void addKey(string, int); //agrega una llave al nodo
    int searchKey(string); //busca una llave en el nodo
    void setParent (BNode*); //asigna el padre del nodo
    int getKeyPosition(string); //retorna la posicion de la llave en el arreglo
    void setPointers(BNode**, BNode**, int); //asigna los apuntadores de la izq y la derecha del nodo nuevo
    void setChildren(BNode**, int); //asigna un nodo hijo en la posicion del arreglo correspondiente
    BNode* getParent (); //retorna el padre del nodo
    BNode* getChildren(int); //retorna el hijo en la posicion indicada
    int getChildrenPosition(BNode**); //retorna la posicion del nodo hijo
    BNode* getPosition(string); //retorna el puntero de la llave especificada en inorder
    void setKeyCount (int); //asigna el contador de llaves
    int getKeyCount(); //retorna el contador de llaves en el arreglo
    void setIsLeaf(bool); //asigna si es hoja
    bool getIsLeaf(); //retorna si es hoja
    Key getKey(int); //retorna la llave en la posicion indicada
    void setKey(int, Key); //asigna la llave en la posicion indicada
    string toString(); //retorna el toString
    void print(); //imprime la informacion del arbol y los subarboles
    void sortKeys(); //arregla las llaves
    void removeKey(string k); //remueve la llave del arreglo
    void removeChildren(int); //remueve un hijo de la posicion indicada
};
#endif

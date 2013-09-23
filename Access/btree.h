#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <cstring>
#include <string>
#include <stddef.h>
#include "bnode.h"

using namespace std;

class BTree{

private:
	BNode* root; //raiz del arbol
public:
	BTree(); //constructor de la clase
	~BTree(); //destructor de la clase
	void insert (string); //metodo de insercion
	void remove (string); //metodo de eliminacion de llaves
	bool search_Key (BNode*,string); //busca la llave a partir de un nodo y retorna si existe
	BNode* search_RemoveNode(BNode*, string);  // busca el nodo del que se removera la llave
	BNode* getRoot(); //retorna la raiz
	BNode* search_InsertNode (BNode*,string); //busca el nodo donde se insertara la llave
	void split_promote (BNode*); //realiza el procedimiento de split promote en los nodos
	void print(); //imprime el arbol
	string swap(BNode**, string); //realiza el intercambio de llaves en la eliminacion
	void rebalance(BNode**); //realiza el metodo de redistribucion
	BNode* swapNode(BNode**, string k); //retorna el nodo en que se hizo el intercambio en la eliminacion
	void concatenate(BNode**); // metodo de concatenacion
};
#endif
#include "field.h"


//Constructores de la Clase
field::field(){

}

field::field( string n, char t, int l, int d, int k ) {
	this->name = n;
	this->type = t;
	this->decimal = d;
	this->length = l;
	this->key = k;
}
//Destructor de la clase
field::~field() {
	
}

//Mutadores y Accesores de la CLase
void field::setName ( const string name ){
	this->name = name;
}

const string field::getName () const{
	return this->name;
}

void field::setType ( const char c ){
	this->type = c;
}

const char field::getType () const{
	return this->type;
}

void field::setLength ( const int l ){
	this->length = l;
}

const int field::getLength () const{
	return this->length;
}

void field::setDecimal ( const int d ){
	this->decimal = d;
}

const int field::getDecimal () const{
	return this->decimal;
}

void field::setKey ( const int k ){
	this->key = k;
}

const int field::getKey () const{
	return this->key;	
}

const string field::toString () const{
	stringstream ss;
    ss << this->getName() << ',' << this->getType() << ',' << this->getLength() << ',' << this->getDecimal() << ',' << this->getKey() << endl;
    return ss.str();
}

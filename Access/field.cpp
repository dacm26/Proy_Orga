#include "field.h"

field::field( string n, char t, int l, int d, int k ) {
	this->name = n;
	this->type = t;
	this->decimal = d;
	this->length = l;
	this->key = k;
}

field::~field() {
	
}

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
	
}
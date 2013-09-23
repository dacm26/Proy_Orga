#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class field {

private:
    string name;//nombre del campo
    char type;//tipo del campo(INT=0,STRING=1,DOUBLE=2)
    int length;//LONGITUD del campo
    int decimal;//cuantos puntos decimales tendra el campo
    int key;//Campo llave
public:
    field();//Constructor simple
    field( string, char, int, int, int );//Constructor
    ~field();//destructor del campo

    //SETTERS Y GETTERS del campo
	void setName ( const string );
	const string getName () const;
	void setType ( const char );
	const char getType () const;
	void setLength ( const int );
	const int getLength () const;
	void setDecimal ( const int );
	const int getDecimal () const;
	void setKey ( const int );
	const int getKey () const;
	const string toString () const;

};

#endif

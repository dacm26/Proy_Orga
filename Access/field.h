#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class field {

private:
	string name;
	char type;
	int length;
	int decimal;
	int key;
public:
	field( string, char, int, int, int );
	~field();
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

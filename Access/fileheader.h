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
    vector<field> fieldlist;
	stack<int> availList;

public:
	FileHeader();
	~FileHeader();
    void setAL(stack<int>);
    void setField(int,field);
    stack<int> getAL();
    void addField ( field );
    int fl_size()const;
    vector<field> getFL()const;
	void removeField ( const int );
	const int getLength () const;
	void addIndex ( const int );
	int getIndex() ; 
    string toString()const;
	
};

#endif

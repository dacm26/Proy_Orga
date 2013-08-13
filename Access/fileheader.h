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
	vector<field*> fieldlist;
	stack<int> availList;

public:
	FileHeader();
	~FileHeader();
	void addField ( field* );
	void removeField ( const int );
	const int getLength () const;
	void addIndex ( const int );
	int getIndex() ; 
	
};

#endif

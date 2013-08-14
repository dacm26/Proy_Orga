#include "fileheader.h"

FileHeader::FileHeader() {
	
}

FileHeader::~FileHeader() {
	
}

void FileHeader::addField ( field f ){//Se anade un campo al vector de campos
	this->fieldlist.push_back(f);
}

void FileHeader::removeField ( const int i ){//Se elimina un campo del vector de campos
	this->fieldlist.erase(fieldlist.begin() + i);
}

const int FileHeader::getLength () const{//Obtiene la longitud del registro
	int length = 0;
	for (int i = 0; i < fieldlist.size(); i++)	{
        length+= fieldlist.at(i).getLength();
	}
	return length;
}

const int FileHeader::fl_size()const{//Devuelve cuantos campos hay en el vector
    return this->fieldlist.size();
}

void FileHeader::addIndex ( const int i ){//Anade donde se borro un registro
	this->availList.push(i);
}

vector<field> FileHeader::getFL()const{// devuelve el vector de campos
    return this->fieldlist;
}

int FileHeader::getIndex() {//Devuelve un elemento del availlist
	if ( availList.empty() ){
		return -1;
	}
	int i = availList.top();
	availList.pop();
    return i;
}



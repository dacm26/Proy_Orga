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
void FileHeader::setAL(stack<int> x){
    this->availList=x;
}

stack<int> FileHeader::getAL(){
    return this->availList;
}

void FileHeader::setField(int x,field y){//Modifica un campo
    this->fieldlist.at(x).setName(y.getName());
    if(y.getKey()==1)
        for(int i=0;i<this->fieldlist.size();++i)
            if(fieldlist.at(i).getKey()==1){
                fieldlist.at(i).setKey(0);
                i=fieldlist.size();
            }
    this->fieldlist.at(x).setKey(y.getKey());
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



#include "fileheader.h"
#include <sstream>
#include <iostream>
using namespace std;
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

 int FileHeader::fl_size()const{//Devuelve cuantos campos hay en el vector
    //cout<< "fl_size: " << fieldlist.size()<<endl;
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

string FileHeader::toString(){
    stringstream ss;
    for(int i = 0; i < this->fl_size();++i){
        ss << this->fieldlist.at(i).getName() << ',';
        ss << this->fieldlist.at(i).getType() << ',';
        ss << this->fieldlist.at(i).getLength() << ',';
        ss << this->fieldlist.at(i).getDecimal() << ',';
        ss << this->fieldlist.at(i).getKey() << endl;
    }
    ss << '@';
    ss << endl;
    return ss.str();
}


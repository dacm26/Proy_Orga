#include "fileheader.h"

FileHeader::FileHeader() {
	
}

FileHeader::~FileHeader() {
	
}

void FileHeader::addField ( field* f ){
	this->fieldlist.push_back(f);
}

void FileHeader::removeField ( const int i ){
	this->fieldlist.erase(fieldlist.begin() + i);
}

const int FileHeader::getLength () const{
	int length = 0;
	for (int i = 0; i < fieldlist.size(); i++)	{
		length+= fieldlist.at(i)->getLength();
	}
	return length;
}

void FileHeader::addIndex ( const int i ){
	this->availList.push(i);
}

int FileHeader::getIndex() {
	if ( availList.empty() ){
		return -1;
	}
	int i = availList.top();
	availList.pop();
	return 1;
}



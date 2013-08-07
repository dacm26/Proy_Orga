#include "ADTFile.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

ADTFile::ADTFile(){
}

ADTFile::~ADTFile(){
}

bool ADTFile::open(string name,ios_base::openmode modo){
	filename=name;
	mode=modo;

	file.open(name.c_str(), modo);

	if (file.is_open())
		return true;

	return false;
}
bool ADTFile::open(string name,ios_base::openmode modo,ios_base::openmode modo2){
	filename=name;
	mode=modo;
	
	file.open(name.c_str(), modo | modo2);
	
	if (file.is_open())
		return true;

	return false;
}

bool ADTFile::close(){
	if (!file.is_open())
		return false;
	file.close();
	if(file.rdstate()!= 0)
		return false;
	
	return true;
}

int ADTFile::read(char* buffer,int s){
	if (!file.is_open())
		return -1;

	if (mode==ios_base::out)
		return -1;

	file.read(buffer,s);
	return file.gcount();
}

int ADTFile::write(const char* buffer,int s){
	if (!file.is_open())
		return -1;

	if(mode==ios_base::in)
		return -1;

	file.write(buffer,s);
	if(file.rdstate()!= 0)
		return -1;

	return s;
}

bool ADTFile::flush(){
	if (!file.is_open())
		return false;

	if (mode==ios_base::out)
	{
		file.flush();
		if(file.rdstate()!= 0)
			return false;

	}
	return false;
}

bool ADTFile::seek(int n,ios_base::seekdir way){
	if (!file.is_open())
		return false;

	if (mode==ios_base::in)//utilizariamos la libreria ifstream
	{
		file.seekg(n,way);
	}
	else if(mode==ios_base::out){//utilizariamos la libreria ofstream
		file.seekp(n,way);
	}
	return true;
}

int ADTFile::tell(){
	if (!file.is_open())
		return -1;

	if (mode==ios_base::in)//utilizariamos la libreria ifstream
	{
		return file.tellg();
	}
	else if(mode==ios_base::out){//utilizariamos la libreria ofstream
		return file.tellp();
	}
	return -1;
}

bool ADTFile::isOpen(){
	if(file.is_open())
		return true;

	return false;
}

bool ADTFile::isOk(){
	if (!file.is_open())
		return false;

	if(file.good())
		return true;

	return false;
}

bool ADTFile::isBoF(){
	if (!file.is_open())
		return false;

    if (mode==ios_base::in){//utilizariamos la libreria ifstream
		if(file.tellg()==0)
			return true;
    }

	else if(mode==ios_base::out)//utilizariamos la libreria ofstream
		if(file.tellp()==0)
			return true;

	return false;
}

bool ADTFile::isEoF(){
	if(file.eof())
		return true;
	return false;
}

#include "ADTRecordFile.h"
#include <string>
#include <ios>
#include <fstream>
using namespace std;

ADTRecordFile::ADTRecordFile(){

}

ADTRecordFile::~ADTRecordFile(){

}
bool ADTRecordFile::open(string name){
    filename=name;
    file.open(name.c_str(), fstream::in | fstream::out);

    if (file.is_open())
        return true;

    return false;
}

bool ADTRecordFile::close(){
    if (!file.is_open())
        return false;
    file.close();
    if(file.rdstate()!= 0)
        return false;

    return true;
}

int ADTRecordFile::readRecord(int p,int init){
    /*
     *No Implementado
     */
    return -1;
}

int ADTRecordFile::writeRecord(const char* buffer,int init){
    /*
     *No Implementado
     */
    return -1;
}

int ADTRecordFile::updateRecord(){
    /*
     *No Implementado
     */
    return -1;
}

int ADTRecordFile::deleteRecord(int p,int init){
    /*
     *No Implementado
     */
    return -1;
}

bool ADTRecordFile::flush(){
    if (!file.is_open())
        return false;
    file.flush();
    if(file.rdstate()!= 0)
       return false;

    return true;
}

bool ADTRecordFile::seekg(int n,ios_base::seekdir way){
    if (!file.is_open())
        return false;

    file.seekg(n,way);

    return true;
}
bool ADTRecordFile::seekp(int n,ios_base::seekdir way){
    if (!file.is_open())
        return false;

    file.seekp(n,way);
    return true;
}

int ADTRecordFile::tellg(){
    if (!file.is_open())
        return -1;

    return file.tellg();
}

int ADTRecordFile::tellp(){
    if (!file.is_open())
        return -1;

    return file.tellp();
}

bool ADTRecordFile::isOpen(){
    if(file.is_open())
        return true;

    return false;
}

bool ADTRecordFile::isOk(){
    if (!file.is_open())
        return false;

    if(file.good())
        return true;

    return false;
}

bool ADTRecordFile::isBoF(){
    if (!file.is_open())
        return false;

    if(file.tellg()==0)
        return true;

    return false;
}

bool ADTRecordFile::isEoF(){
    if(file.eof())
        return true;
    return false;
}

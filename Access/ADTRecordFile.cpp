#include "ADTRecordFile.h"
#include <string>
#include <ios>
#include <fstream>
using namespace std;

ADTRecordFile::ADTRecordFile(){

}

ADTRecordFile::~ADTRecordFile(){

}
bool ADTRecordFile::open(string name,ios_base::openmode modo){
    filename=name;
    mode=modo;

    file.open(name.c_str(), modo);

    if (file.is_open())
        return true;

    return false;
}

bool ADTRecordFile::open(string name,ios_base::openmode modo,ios_base::openmode modo2){
    filename=name;
    mode=modo;

    file.open(name.c_str(), modo | modo2);

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

    if (mode==ios_base::out)
    {
        file.flush();
        if(file.rdstate()!= 0)
            return false;

    }
    return false;
}

bool ADTRecordFile::seek(int n,ios_base::seekdir way){
    /*
     *No Implementado
     */
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

int ADTRecordFile::tell(){
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

    if (mode==ios_base::in){//utilizariamos la libreria ifstream
        if(file.tellg()==0)
            return true;
    }

    else if(mode==ios_base::out)//utilizariamos la libreria ofstream
        if(file.tellp()==0)
            return true;

    return false;
}

bool ADTRecordFile::isEoF(){
    if(file.eof())
        return true;
    return false;
}

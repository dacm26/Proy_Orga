#include "ADTRecordFile.h"
#include <string>
#include <ios>
#include <fstream>
#include <sstream>
using namespace std;

ADTRecordFile::ADTRecordFile(){
}

ADTRecordFile::~ADTRecordFile(){

}

bool ADTRecordFile::open(string name){
    filename=name;
    file.open(name.c_str(), fstream::in | fstream::out);
    if(!file.is_open()){
        file.open(name.c_str(),fstream::out);
        file.write(" ",1);
        file.flush();
        file.close();
        file.open(name.c_str(), fstream::in | fstream::out);
    }
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

string ADTRecordFile::readRecord(int p,int init,int size_record){
    file.seekg(0,ios_base::beg);
    file.seekg(init,ios_base::cur);
    file.seekg((size_record*p),ios_base::cur);
    char buffer[size_record];
    file.read(buffer,size_record);
    buffer[size_record]='\0';
    stringstream ss;
    ss << buffer;
    return ss.str();
}

int ADTRecordFile::read(char* buffer,int s){
    if (!file.is_open())
        return -1;
    file.read(buffer,s);
    return file.gcount();
}

int ADTRecordFile::write(const char* buffer,int s){
    if (!file.is_open())
        return -1;
    file.write(buffer,s);
    if(file.rdstate()!= 0)
        return -1;

    return s;
}

bool ADTRecordFile::writeRecord(const char* buffer,int where,int init,int size_record){
    file.seekp(0,ios_base::beg);
    file.seekp(init,ios_base::cur);
    if(where == -1){
        file.seekp(0,ios_base::end);
        file.seekp(-2,ios_base::cur);
        file.seekp(1,ios_base::cur);
        file.write(buffer,size_record);
    }
    else{
    file.seekp((size_record*where),ios_base::cur);
    file.write(buffer,size_record);
    }
    file.flush();
    if(file.rdstate()!= 0)
        return false;
    return true;
}

bool ADTRecordFile::updateRecord(){

    return this->flush();
}

int ADTRecordFile::deleteRecord(int p,int init,int size_record){
    file.seekp(0,ios_base::beg);
    file.seekp(init,ios_base::cur);
    file.seekp((p*size_record),ios_base::cur);
    file.write("*",1);
    file.flush();
    return p+1;//Para el availList
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

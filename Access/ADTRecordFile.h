#ifndef ADTRECORDFILE_H
#define ADTRECORDFILE_H
#include <string>
#include <ios>
#include <fstream>
using namespace std;
class ADTRecordFile
{
public:
    ADTRecordFile();
    ~ADTRecordFile();
    bool open(string);
    bool close();
    int read(char*,int);
    int write(const char*,int);
    string readRecord(int,int,int);
    bool writeRecord(const char*,int,int,int);
    bool updateRecord();
    int deleteRecord(int,int,int);
    bool flush();
    bool seekg(int,ios_base::seekdir);
    bool seekp(int,ios_base::seekdir);
    int tellp();
    int tellg();
    bool isOpen();
    bool isOk();
    bool isBoF();
    bool isEoF();
    fstream file;
    string filename;
};
#endif

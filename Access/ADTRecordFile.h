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
    int readRecord(int,int);
    int writeRecord(const char*,int);
    int updateRecord();
    int deleteRecord(int,int);
    bool flush();
    bool seekg(int,ios_base::seekdir);
    bool seekp(int,ios_base::seekdir);
    int tellp();
    int tellg();
    bool isOpen();
    bool isOk();
    bool isBoF();
    bool isEoF();
private:
    fstream file;
    string filename;
};
#endif

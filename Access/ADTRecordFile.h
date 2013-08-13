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
    bool open(string,ios_base::openmode);
    bool open(string,ios_base::openmode,ios_base::openmode);
    bool close();
    int readRecord(int,int);
    int writeRecord(const char*,int);
    int updateRecord();
    int deleteRecord(int,int);
    bool flush();
    virtual bool seek(int,ios_base::seekdir);
    virtual int tell();
    bool isOpen();
    bool isOk();
    bool isBoF();
    bool isEoF();
private:
    fstream file;
    string filename;
    ios_base::openmode mode;
};
#endif

#ifndef ADTFILE_H
#define ADTFILE_H
#include <string>
#include <ios>
#include <fstream>
using namespace std;
class ADTFile
{
public:
	ADTFile();
	~ADTFile();
	bool open(string,ios_base::openmode);
	bool open(string,ios_base::openmode,ios_base::openmode);
	bool close();
	int read(char*,int);
	int write(const char*,int);
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
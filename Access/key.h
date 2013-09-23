#ifndef KEY_H
#define KEY_H

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <stddef.h>

using namespace std;

class Key{

private:
	string key;
	int rrn;
public:
	Key(string="", int=0);
	~Key();
	void setKey(string);
	void setrrn(int);
	string getKey() const;
	int getrrn() const;
	string toString();
	bool operator==(const Key&) const;
	bool operator<(const Key&) const;
	bool operator>(const Key&) const;
	bool isNumber(string) const;
};
#endif
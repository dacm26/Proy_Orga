#ifndef BNODE_H
#define BNODE_H

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <stddef.h>
#include <sstream>
#include <vector>

using namespace std;

class BNode {

private:
	BNode* parent;
	BNode* pointers[5];
	string keys[4];
	int keycount;
	bool isleaf;
public:
	BNode();
	~BNode();
	void addKey(string);
	bool searchKey(string);
	void setParent (BNode*);
	int getKeyPosition(string);
	void setPointers(BNode**, BNode**, int);
	void setChildren(BNode**, int);
	BNode* getParent ();
	BNode* getChildren(int);
	int getChildrenPosition(BNode**);
	BNode* getPosition(string);
	void setKeyCount (int);
	int getKeyCount();
	void setIsLeaf(bool);
	bool getIsLeaf();
	string getKey(int);
	void setKey(int, string);
	string toString();
	void print();
	void sortKeys();
	void removeKey(string k);
	void removeChildren(int);
};
#endif

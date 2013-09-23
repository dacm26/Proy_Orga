#include "bnode.h"

BNode::BNode(){
    isleaf = true;
    parent = NULL;
    keycount = 0;
    for (int i = 0; i < 4; i++)	{
        this->pointers[i] = NULL;
    }
}

BNode::~BNode(){
    for (int i = 0; i < 4; i++)	{
        this->pointers[i] = NULL;
    }
}

Key BNode::getKey(int i){
    return keys[i];
}

void BNode::setParent (BNode* p){
    parent = p;
}

BNode* BNode::getParent(){
    return this->parent;
}

void BNode::addKey( string k, int i ){
    Key* llave = new Key(k, i);
    keys[keycount] = *llave;
    keycount++;
    if (keycount > 1){
        sortKeys();
    }
}

int BNode::getKeyPosition(string k){
    for (int i = 0; i < 4; i++)
    {
        if (k == keys[i].getKey()){
            return i;
        }
    }
    return -1;
}

void BNode::setKey(int i, Key s){
    keys[i] = s;
}

int BNode::searchKey(string k){
    for (int i = 0; i < keycount; i++)	{
        if (keys[i].getKey() == k)
            return keys[i].getrrn();
    }
    return -1;
}

void BNode::setPointers(BNode** l, BNode** r, int p){
    if (p == 10){
        pointers[0] = *l;
        pointers[1] = *r;
    } else {
        for (int i = 4; i > p; i--)		{
            pointers[i] = pointers[i-1];
        }
        pointers[p] = *l;
        pointers[p+1] = *r;
    }
}

BNode* BNode::getPosition(string n) {
    if (pointers[0] == NULL){
        return NULL;
    }
    int k = 10;
    Key s(n);
    for (int i = 0; i < keycount; i++)	{
        if(s > keys[i]){
            continue;
        } else {
            k = i;
            break;
        }
    }
    if (k == 10){
        k = keycount;
    }
    return pointers[k];
}

void BNode::setKeyCount( int k) {
    this->keycount = k;
}

int BNode::getKeyCount() {
    return this->keycount;
}

void BNode::setIsLeaf( bool l) {
    this->isleaf = l;
}

bool BNode::getIsLeaf() {
    return isleaf;;
}

string BNode::toString(){
    stringstream ss;
    for (int i = 0; i < keycount; i++)	{
        ss << "Key " << i << ": " << keys[i].toString() << "; ";
    }
    ss << " Keycount: " << keycount << endl;
    return ss.str();
}

void BNode::removeChildren(int i){
    if (i == 0){
        pointers[0] = pointers[1];
        pointers[1] = pointers[2];
        pointers[2] = pointers[3];
        pointers[4] = NULL;
    } else if ( i == 1 ){
        pointers[1] = pointers[2];
        pointers[2] = pointers[3];
        pointers[3] = NULL;
    } else if ( i == 2 ){
        pointers[2] = pointers[3];
        pointers[3] = NULL;
    } else {
        pointers[3] == NULL;
    }
}

void BNode::print(){
    cout << toString() << endl;
    if (pointers[0]){
        for (int i = 0; i < keycount+1; i++){
            cout << "Hijos de: " << keys[0].getKey() << " ";
            BNode* temp = pointers[i];
            temp->print();
        }
    }
}

BNode* BNode::getChildren(int i){
    return pointers[i];
}

void BNode::setChildren(BNode** c, int k){
    pointers[k] = *c;
}

void BNode::sortKeys() {
    for (int i = 0; i < keycount; i++) {
        for (int k = 0; k < keycount; k++) {
            if (keys[i] < keys[k]) {
                Key tmp = keys[i];
                keys[i] = keys[k];
                keys[k] = tmp;
            }
        }
    }
}

int BNode::getChildrenPosition(BNode** n) {
    for (int i = 0; i < keycount+1; i++){
        if(pointers[i] == *n){
            return i;
        }
    }
    return -1;
}

void BNode::removeKey(string k){
    int pos = 0;
    for (int i = 0; i < keycount; i++)	{
        if (keys[i] == k)
            pos = i;
    }
    if (pos == 0){
        keys[0] = keys[1];
        keys[1] = keys[2];
    } else if (pos == 1){
        keys[1] = keys[2];
    } else {

    }
    --keycount;
}



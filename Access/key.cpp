#include "key.h"

Key::Key(string k, int i){
	this->key = k;
	this->rrn = i;
}

Key::~Key(){

}

void Key::setKey(string k){
	this->key =k;
}

void Key::setrrn(int i){
	this->rrn = i;
}

string Key::getKey() const{
	return key;
}

int Key::getrrn() const{
	return rrn;
}

string Key::toString(){
	stringstream ss;
	ss << "Key: " << key << ", RRN: " << rrn;
	return ss.str();
}

bool Key::operator ==(const Key& r) const{
	if (this->key == r.getKey()){
		return true;
	}
	return false;
}

bool Key::operator<(const Key& r) const{
	if (isNumber(key)){
		int l = atoi(key.c_str());
		string k = r.getKey();
		int r = atoi(k.c_str());
		if (l < r)
			return true;
		else return false;
	} else {
		if (key < r.getKey())
			return true;
		else return false;
	}
	return false;
}

bool Key::operator>(const Key& r) const{
	if (isNumber(key)){
		int l = atoi(key.c_str());
		string k = r.getKey();
		int r = atoi(k.c_str());
		if (l > r)
			return true;
		else return false;
	} else {
		if (key > r.getKey())
			return true;
		else return false;
	}
	return false;
}

bool Key::isNumber(string a) const{
	bool num=false;
	int x=atoi(a.c_str());
	if(x==0 && a.size()==1 && (a.c_str())[0]=='0'){
		num=true;
	}
	else if(x != 0){
		num=true;
	}
	return num;
}


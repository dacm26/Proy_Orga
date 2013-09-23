#include "btree.h"

BTree::BTree(){
	root = new BNode();
}

BTree::~BTree(){
	delete root;
}

void BTree::insert(string k){	
	BNode* temp = search_InsertNode(this->root, k);
	temp->addKey(k); 
	if (temp->getKeyCount() == 4){
		split_promote(temp);
	}
}

bool BTree::search_Key (BNode* n, string k){
	if (!n)
		return false;
	if (n->searchKey(k))
		return true;
	else return search_Key(n->getPosition(k), k);
}

BNode* BTree::search_InsertNode (BNode* n, string k){
	if(!n) {
		n = new BNode();
		return n;
	}
	if (!n->getPosition(k))
		return n;
	else return search_InsertNode(n->getPosition(k), k);
}

void BTree::split_promote (BNode* n){
    BNode* left = new BNode();
	BNode* right = new BNode();
	left->addKey(n->getKey(0));
	right->addKey(n->getKey(2));
	right->addKey(n->getKey(3));
	BNode* parent = n->getParent();
	BNode* temp;
	if (!parent){
		parent = new BNode();
		parent->addKey(n->getKey(1));
		parent->setPointers(&left,&right,10);
		root = parent;
		parent->setIsLeaf(false);
		left->setParent(parent);
		right->setParent(parent);
		if(!n->getIsLeaf()){
			left->setIsLeaf(false);
			right->setIsLeaf(false);
			for (int i = 0; i < 5; ++i)	{
				temp = n->getChildren(i);
				if(i==0 || i ==1){
					left->setChildren(&temp,i);
					temp->setParent(left);
				}else 
					right->setChildren(&temp,i-2);
					temp->setParent(right);
			}

		}
		n = NULL;
	} else {				
		parent->addKey(n->getKey(1));
		int l = parent->getKeyPosition(n->getKey(1));
		parent->setPointers(&left,&right,l);
		left->setParent(parent);
		right->setParent(parent);
		if(!n->getIsLeaf()){
			left->setIsLeaf(false);
			right->setIsLeaf(false);
			for (int i = 0; i < 5; ++i)	{
				temp = n->getChildren(i);
				if(i==0 || i ==1){
					left->setChildren(&temp,i);
					temp->setParent(left);
				}
				else {
					right->setChildren(&temp,i-2);
					temp->setParent(right);
				}
			}

		}
		n = NULL;
		if (parent->getKeyCount()==4){
			split_promote(parent);
		}
	}
}

BNode* BTree::getRoot(){
	return root;
}

void BTree::print(){
	root->print();
}

void BTree::remove (string k){
	BNode* node = search_RemoveNode(root,k);
	if (node->getIsLeaf()){
		node->removeKey(k);	
		if (node->getKeyCount() == 0){
			BNode* parent = node->getParent();
			int pos = parent->getChildrenPosition(&node);
			if (pos == 0){
				BNode* right = parent->getChildren(1);
				if (right->getKeyCount() > 1){
					rebalance(&node);
				} else {
					concatenate(&node);
					//concatenate
				}
			} else if (pos == 1) {				
			    BNode* left = parent->getChildren(0);
				BNode* right = parent->getChildren(2);
				if (right->getKeyCount() > 1 || left->getKeyCount() > 1){
					rebalance(&node);
				} else {
					concatenate(&node);
					//concatenate
				}
			} else if (pos == 2){
				BNode* left = parent->getChildren(1);
				BNode* right = parent->getChildren(3);
				if (right->getKeyCount() > 1 || left->getKeyCount() > 1){
					rebalance(&node);
				} else {
					concatenate(&node);
					//concatenate
				}
			} else {
				BNode* left = parent->getChildren(2);
				if (left->getKeyCount() > 1){
					rebalance(&node);
				} else {
					concatenate(&node);
					//concatenate
				}
			}
		}
	} else {
		int i = node->getKeyPosition(k);
		BNode* temp = node->getChildren(i+1);
		string s = swap(&temp, k);
		node->setKey(i, s);
		temp = swapNode(&temp, k);
		if (temp->getKeyCount() == 0){
			BNode* parent = temp->getParent();
			int pos = parent->getChildrenPosition(&node);
			if (pos == 0){
				BNode* right = parent->getChildren(1);
				if (right->getKeyCount() > 1){
					rebalance(&temp);					
				} else {
					concatenate(&node);
					//concatenate
				}
			} else if (pos == 1) {
				BNode* left = parent->getChildren(0);
				BNode* right = parent->getChildren(2);
				if (right->getKeyCount() > 1 || left->getKeyCount() > 1){
					rebalance(&temp);
				} else {
					concatenate(&node);
					//concatenate
				}
			} else if (pos == 2){
				BNode* left = parent->getChildren(1);
				BNode* right = parent->getChildren(3);
				if (right->getKeyCount() > 1 || left->getKeyCount() > 1){
					rebalance(&temp);
				} else {
					concatenate(&node);
					//concatenate
				}
			} else {
				BNode* left = parent->getChildren(2);
				if (left->getKeyCount() > 1){
					rebalance(&temp);
				} else {
					concatenate(&node);
					//concatenate
				}
			}
		}
	}

}

BNode* BTree::search_RemoveNode (BNode* n, string k){
	if (!n)
		return NULL;
	if (n->searchKey(k))
		return n;
	else return search_RemoveNode(n->getPosition(k), k);
}

string BTree::swap(BNode** n, string k) {
	BNode* l = *n;
	if (l->getIsLeaf())	{
		string temp = l->getKey(0);
		l->setKey(0, k);
		l->removeKey(k);
		return temp;
	} else {
		BNode* t = l->getChildren(0);
		return swap (&t, k);
	}
}

BNode* BTree::swapNode(BNode** n, string k){
	BNode* l = *n;
	if (l->getIsLeaf())	{
		return l;
	} else {
		BNode* t = l->getChildren(0);
		return swapNode(&t, k);
	}
}


void BTree::rebalance(BNode** n){
	BNode* node = *n;
	BNode* parent = node->getParent();
	int pos = parent->getChildrenPosition(&node);
	if (pos < parent->getKeyCount()){
		BNode* right = parent->getChildren(pos+1);
		BNode* left = parent->getChildren(pos-1);
		if (right->getKeyCount() > 1){
			string child = right->getKey(0);
			right->removeKey(child);
			string separator = parent->getKey(pos);
			parent->removeKey(separator);
			parent->addKey(child);
			node->addKey(separator);
		}else if (left->getKeyCount() > 1){
			string child = left->getKey(left->getKeyCount()-1);
			left->removeKey(child);
			string separator = parent->getKey(pos-1);
			parent->removeKey(separator);
			parent->addKey(child);
			node->addKey(separator);
		}
	} else if (pos == parent->getKeyCount()){
		BNode* left = parent->getChildren(pos-1);
		if (left->getKeyCount() > 1){
			string child = left->getKey(left->getKeyCount()-1);
			left->removeKey(child);
			string separator = parent->getKey(pos-1);
			parent->removeKey(separator);
			parent->addKey(child);
			node->addKey(separator);
		}
	}
	
}

void BTree::concatenate(BNode** n){
	BNode* node = *n;
	if (node->getIsLeaf()){
		BNode* parent = node->getParent();
		int pos = parent->getChildrenPosition(&node);
		if(pos == 0){
			string separator = parent->getKey(0);
			BNode* right = parent->getChildren(1);
			node->addKey(separator);
			node->addKey(right->getKey(0));
			parent->removeKey(separator);
			parent->removeChildren(1);
			if (parent->getKeyCount() == 0){
				BNode* empty = parent;
				parent = parent->getParent();
				if (parent){		
					int pos = parent->getChildrenPosition(&empty);
					if (pos == 0){
						BNode* right = parent->getChildren(1);
						if (right->getKeyCount() > 1){
							rebalance(&empty);					
						} else {
							concatenate(&empty);
						//concatenate
						}					
						concatenate(&empty);
					} else if (pos == 1) {
						BNode* left = parent->getChildren(0);
						if (left->getKeyCount() > 1){
						rebalance(&empty);
						} else {
							concatenate(&empty);
							//concatenate
						}
					}
				} else {
					root = empty;
					empty->setParent(NULL);					
				}
			}
		} else if (pos == 1){
			string separator = parent->getKey(1);
			BNode* right = parent->getChildren(2);
			node->addKey(separator);
			node->addKey(right->getKey(0));
			parent->removeKey(separator);
			parent->removeChildren(2);
		} else if (pos == 2){
			string separator = parent->getKey(2);
			BNode* right = parent->getChildren(3);
			node->addKey(separator);
			node->addKey(right->getKey(0));
			parent->removeKey(separator);
			parent->removeChildren(3);
		} else {
			string separator = parent->getKey(2);
			BNode* left = parent->getChildren(2);
			left->addKey(separator);
			parent->removeKey(separator);
			parent->removeChildren(3);
		}
	} else {
		BNode* parent = node->getParent();
		if (parent){
			BNode* abuelo = parent->getParent();
			if (abuelo->getParent() == NULL && parent->getKeyCount() == 1){
				string separator = parent->getKey(0);
				BNode* right = parent->getChildren(1);
				node->addKey(separator);
				node->addKey(right->getKey(0));
				BNode* t = right->getChildren(0);
				node->setChildren(&t, 1);
				t = right->getChildren(1);
				node->setChildren(&t, 2);
				parent->removeKey(separator);
				parent->removeChildren(1);
				node->setParent(NULL);
				root = node;
			} else if (abuelo->getParent() == NULL && parent->getKeyCount() > 1) {
				int posicion = parent->getChildrenPosition(&node);
				if( posicion == 0 ){
					string separator = parent->getKey(0);
					BNode* right = parent->getChildren(1);
					node->addKey(separator);
					node->addKey(right->getKey(0));
					BNode* t = right->getChildren(0);
					node->setChildren(&t, 1);
					t = right->getChildren(1);
					node->setChildren(&t, 2);
					parent->removeKey(separator);
					parent->removeChildren(1);
				}
			}
		}
	}
}
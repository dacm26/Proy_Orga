#include "btree.h"

BTree::BTree(){
    root = new BNode();
}

BTree::~BTree(){
    delete root;
}

bool BTree::insert(string k, int i){
    if (search_Key(root, k) == -1){
        BNode* temp = search_InsertNode(this->root, k);
        temp->addKey(k, i);
        if (temp->getKeyCount() == 4){
            split_promote(temp);
        }
        return true;
    } else {
        return false;
    }
}

int BTree::search_Key (BNode* n, string k){
    if (!n)
        return -1;
    if (n->searchKey(k) != -1){
        return n->searchKey(k);
    }
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
    left->addKey(n->getKey(0).getKey(), n->getKey(0).getrrn());
    right->addKey(n->getKey(2).getKey(), n->getKey(2).getrrn());
    right->addKey(n->getKey(3).getKey(), n->getKey(3).getrrn());
    BNode* parent = n->getParent();
    BNode* temp;
    if (!parent){
        parent = new BNode();
        parent->addKey(n->getKey(1).getKey(), n->getKey(1).getrrn());
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
        parent->addKey(n->getKey(1).getKey(), n->getKey(1).getrrn());
        int l = parent->getKeyPosition(n->getKey(1).getKey());
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

/*int BTree::remove (string k){
    BNode* node = search_RemoveNode(root,k);
    if (!node->getIsLeaf()){
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

        } else if (pos == 1){
        } else if (pos == 2){
        } else {
        }
    } else {

    }
}*/

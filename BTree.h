#ifndef BTREE_H
#define BTREE_H
#include <string>
class BTree{
public:
	BTree();
	~BTree();
	bool insert_int();
	bool insert_string();
	int search_int();
	string search_string();

};


#endif
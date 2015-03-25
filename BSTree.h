#ifndef BTREE_H
#define BTREE_H
#include <string>
class BSTree{

public:
	BSTree();
	~BSTree();
	Nodo* crear(int);
	Nodo* insertar(Nodo*,int);
	int buscar(Nodo*,int);



};


#endif
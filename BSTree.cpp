#include <stddef.h>
#include "BSTree.h"
using namespace std;
struct Nodo{
	
};
BSTree::BSTree();
BSTree::~BSTree();
Nodo* BSTree::crear(int);
Nodo* BSTree::insertar(Nodo*,int);
int BSTree::buscar(Nodo*,int);
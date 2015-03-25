#include "BTree.h"
#include <string>
using namespace std;

struct NodeInts{
	int data[15];
	NodeInts* children[16];
	int numero_llaves;

	int buscarLlave(int llave){
		int retval = 0;
		while(retval<numero_llaves && llave > data[a]){
			retval++;
		}
		return retval;
	}
};
struct NodeStrings{
	string data[15];
	NodeStrings* children[16];
	int numero_llaves;
};

BTree::BTree(){

}
BTree::~BTree(){

}
bool BTree::insert_int(){

}
bool BTree::insert_string(){

}
int BTree::search_int(){

}
string BTree::search_string(){

}
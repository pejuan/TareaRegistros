#include "BTree.h"
#include <string>
using namespace std;

struct NodeInts{
	int data[15];
	NodeInts* children[16];
};
struct NodeStrings{
	string data[15];
	NodeStrings* children[16];
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
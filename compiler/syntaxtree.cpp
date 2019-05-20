#include "syntaxtree.h"

syntaxtree::syntaxtree() {
}
syntax_node* ::makenode(string s) {
	syntax_node* node;
	node->lexerLine = 0;
	node->str = s;
	node->bro = NULL;
	node->son = NULL;
	return node;
}

string syntaxtree::tostring() {
	return head->str;
}
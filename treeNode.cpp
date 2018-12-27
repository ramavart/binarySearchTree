#include "pch.h"
#include "treeNode.h"
#include <iostream>

using namespace std;

treeNode::treeNode(const treeNode &obj) {
	int * value = new int;
	*value = *obj.value;
	Left = obj.Left;
	Right = obj.Right;
	cout << "this is constructor of copy" << endl;
}
treeNode::~treeNode() {
	delete value;
	Left = 0;
	Right = 0;
	cout << "Delete object" << endl;
}
bool treeNode::CompareTo(treeNode * node) {
	if (node == 0) return false;
	else if (*value < *(node->value)) return true; //true if this < node
	else return false;
}

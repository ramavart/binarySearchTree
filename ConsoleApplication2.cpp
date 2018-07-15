#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>
#include <assert.h>
#include <initializer_list>
#include <utility>
#include <stack>
using namespace std;

//binary tree
//todo
//need the test on lastLeft, the 3 case in remove() method
//implement action in -pre -post -in
//head case remove() method need fix

class treeNode {
	int value;
	treeNode * Left;
	treeNode * Right;

public:
	treeNode(int val=0) {
		value = val;
		Left = 0;
		Right = 0;
	}
	void setRight(treeNode * val) { Right = val; }
	void setLeft(treeNode * val) { Left = val; }
	treeNode * getRight() const { return Right; }
	treeNode * getLeft() const { return Left; }
	int getNodeValue() const { 
		if (value != 0)
		return value;
		else return 0;
	}
	void setNodeValue(int val) { value = val; }
	bool CompareTo(treeNode * node);
};

bool treeNode::CompareTo(treeNode * node) {
	if (node == 0) return false;
	else if (value < node->value) return true; //true if this < node
	else return false;
}

class binaryTree {
	
	int quantity;
	treeNode * head;
	void PreOrder(treeNode * pointer);
	void PostOrder(treeNode * pointer);
	void InOrder(treeNode * pointer/*const fptr &f*/);
	void addTo(treeNode * node, treeNode * firstNode);
public:	
	//treeNode * head;
	binaryTree(int value = 0);
	void NewNode(int value);
	bool remove(int value);
	treeNode * search(int val, treeNode * anyNode, treeNode *& parrent);
	int getCount() const { return quantity; };
	void clear();

	void PreOrderShelter();
	void PostOrderShelter();
	void InOrderShelter();
	typedef void(*fptr)(...);

	void showValue(/*treeNode * node*/);
};

binaryTree::binaryTree(int value) {
	if (!value) {
		head = 0;
		quantity = 0;
	}
	else {
		treeNode * node = new treeNode();
		node->setNodeValue(value);
		head = node;
		quantity++;
	}
}

void binaryTree::showValue(/*treeNode * node*/) {
	//cout << node->getNodeValue() << endl;
	cout << head->getNodeValue() << endl;
}

void binaryTree::NewNode(int value) {
	treeNode * node = new treeNode(value);
	if (head == 0) {
		head = node;
		head->setLeft(0);
		head->setRight(0);
		quantity++;
		return;
	}
	else {
		addTo(node, head);
		node->setLeft(0);
		node->setRight(0);
		return;
	}
}

void binaryTree::addTo(treeNode * node, treeNode * firstNode){
	treeNode * permanent = firstNode;
	if (node->CompareTo(firstNode)) {
		if (permanent->getLeft() == 0) {
			permanent->setLeft(node);
			quantity++;
			return;
		}
		else addTo(node, permanent->getLeft());
	}
	else {
		if (permanent->getRight() == 0){
			permanent->setRight(node);
			quantity++;
			return;
		}
		else addTo(node, permanent->getRight());
	}
}

bool binaryTree::remove(int value) {
	treeNode* parrentNode = 0;
	bool result = false;
	treeNode* node = this->search(value, this->head, ref(parrentNode));
	cout << "prNode: " << parrentNode->getNodeValue() << endl;
	cout << "node:" << node->getNodeValue() << endl;
	if (node == 0) return false;
	if (node->getRight() == 0) {
		if (parrentNode == 0) {
			head = node->getLeft();
		}
		else {
			result = node->CompareTo(parrentNode);
			if (result) {
				//if left
				parrentNode->setLeft(node->getLeft());
			}
			else if (!result) {//if right
				parrentNode->setRight(node->getLeft());
			}
		}
	}
	else if (node->getRight()->getLeft()==0) {
		result = node->CompareTo(parrentNode);
		if (parrentNode == 0) {
			head = node->getRight();
		}
		else if (result) {
			parrentNode->setLeft(node->getRight());
		}
		else {
			parrentNode->setRight(node->getRight());
		}
	}
	else {
		treeNode * LastLeft = node->getRight()->getLeft();
		treeNode * parrentLastLeft = node->getRight();

		while (LastLeft->getLeft() != 0) { parrentLastLeft = LastLeft; LastLeft = LastLeft->getLeft(); }

		parrentLastLeft->setLeft(LastLeft->getRight()); 

		if (parrentNode == 0) head = LastLeft;
		else {
			result = node->CompareTo(parrentNode);
			if (result) {
				parrentNode->setLeft(LastLeft);
				LastLeft->setLeft(node->getLeft());
				LastLeft->setRight(node->getRight());
			}
			else {
				parrentNode->setRight(LastLeft);
				LastLeft->setLeft(node->getLeft());
				LastLeft->setRight(node->getRight());
			}
		}
	}
	delete[] node;
	return true;
}

treeNode * binaryTree::search(int val, treeNode * anyNode, treeNode *& parrent) {

	while (anyNode != NULL) {
		if (anyNode->getNodeValue() == val) {
			cout << "find: "<<anyNode->getNodeValue() << endl;
			cout << "parrent: " << (parrent)->getNodeValue() << endl;

			return anyNode;
		}
		if (anyNode->getNodeValue() > val) {
			parrent = anyNode;
			anyNode = anyNode->getLeft();

		}
		else {
			(parrent) = anyNode;
			anyNode = anyNode->getRight();
		}
	}
	cout << "we didn't find anything" << endl;
	return anyNode = 0;
}

void binaryTree::clear() {
	//необходимо реализовать гарбедж коллектор
	head = 0; 
	quantity = 0; 
};

void binaryTree::PreOrderShelter() {
	PreOrder(head);
}

void binaryTree::PostOrderShelter() {
	PostOrder(head);
}

void binaryTree::PreOrder(treeNode * pointer) {
	if (pointer != NULL) {
		cout << pointer->getNodeValue() << endl;
			PreOrder(pointer->getLeft());
			PreOrder(pointer->getRight());
		}
	}

void binaryTree::PostOrder(treeNode * pointer) {
	if (pointer != NULL) {
			PostOrder(pointer->getLeft());
			PostOrder(pointer->getRight());
			cout << pointer->getNodeValue() << endl;
	}
}

//cyclic variant
//doesn't work
//void binaryTree::InOrder(/*const fptr &f*/) {
/*if (head != 0) {
stack <treeNode *> stack; 

treeNode * current = head;
//stack.push(current);

bool goLeft = true;
while (stack.size() > 0) {

while (current->getLeft()) {
stack.push(current);
current = current->getLeft();
}
//f(current);
cout << current->getNodeValue() << endl;

if (current->getRight()) {
current = current->getRight();
goLeft = true;
}
else {
current = stack.top();
stack.pop();
goLeft = false;
}
}
}
}*/

void binaryTree::InOrderShelter() {
	InOrder(head);
}

void binaryTree::InOrder(treeNode * pointer) {
	if (pointer != NULL) {
		InOrder(pointer->getLeft());
		cout << pointer->getNodeValue() << endl;
		InOrder(pointer->getRight());
	}
}

int main() {


	system("pause");
	return 0;
}
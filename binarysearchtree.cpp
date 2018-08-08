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
// methods works well when u don't using class CInterface
//todo
//class interface doesn't work correctly

//void simpleInterface();
//void listener(int i, binaryTree *& pointer);

class treeNode {
	int * value;
	treeNode * Left;
	treeNode * Right;

public:
	treeNode(int val = 0) {
		value = new int();
		*value = val;
		Left = 0;
		Right = 0;
	}
	treeNode(const treeNode &obj);
	~treeNode();
	void setRight(treeNode * val) { Right = val; }
	void setLeft(treeNode * val) { Left = val; }
	treeNode * getRight() const { return Right; }
	treeNode * getLeft() const { return Left; }
	int getNodeValue() const {
		if (value != 0)
			return *value;
		else return 0;
	}
	void setNodeValue(int val) { *value = val; }
	bool CompareTo(treeNode * node);
};

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

class binaryTree {

	int quantity;
	//treeNode * head;
	void PreOrder(void (binaryTree::*fptr)(treeNode * ptr), treeNode * pointer);
	void PostOrder(void (binaryTree::*fptr)(treeNode * ptr), treeNode * pointer);
	void InOrder(void (binaryTree::*fptr)(treeNode * ptr), treeNode * pointer);
	void addTo(treeNode * node, treeNode * firstNode);
public:
	treeNode * head;
	binaryTree(int value = 0);
	void NewNode(int value);
	bool remove(int value);
	treeNode * search(int val, treeNode * anyNode, treeNode *& parrent);
	int getCount() const { return quantity; };
	void clear(treeNode * node);
	void PreOrderShelter(void (binaryTree::*fptr)(treeNode * ptr), treeNode * pointer);
	void PostOrderShelter(void (binaryTree::*fptr)(treeNode * ptr), treeNode * pointer);
	void InOrderShelter(void (binaryTree::*fptr)(treeNode * ptr), treeNode * pointer);
	treeNode* getHead()const;
	void showValue(treeNode * node);

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
		//cout << "I am: " << node->getNodeValue() << "| my right: " <<node->getRight() << "my left: " << node->getLeft()<< endl;

	}
	
}

void binaryTree::showValue(treeNode * node) {
	cout << node->getNodeValue() << endl;
}

void binaryTree::NewNode(int value) {
	treeNode * node = new treeNode(value);
	if (head == 0) {
		head = node;
		head->setLeft(0);
		head->setRight(0);
	}
	else {
		addTo(node, head);
		node->setLeft(0);
		node->setRight(0);
	}
	quantity++;
	return;
}

void binaryTree::addTo(treeNode * node, treeNode * firstNode) {
	treeNode * permanent = firstNode;
	if (node->CompareTo(firstNode)) {
		if (permanent->getLeft() == 0) {
			permanent->setLeft(node);
			cout << "I am: " << permanent->getNodeValue() << "| my left: " << node->getNodeValue() << endl;
		}
		else addTo(node, permanent->getLeft());
	}
	else {
		if (permanent->getRight() == 0) {
			permanent->setRight(node);
			cout << "I am: " << permanent->getNodeValue() << "| my right: " << node->getNodeValue() << endl;
		}
		else addTo(node, permanent->getRight());
	}
	return;
}

bool binaryTree::remove(int value) {
	treeNode* parrentNode = 0;
	bool result = false;
	cout << "path this check" << endl;
	cout << "head is: " << this->getHead()/*->getNodeValue()*/ << endl;
	treeNode* node = this->search(value, this->head, ref(parrentNode));

	//cout << "prNode: " << parrentNode->getNodeValue() << endl;
	//cout << "node:" << node->getNodeValue() << endl;
	if (node == 0) return false;
	if (node->getRight() == 0) {
		if (parrentNode == 0) {
			head = node->getLeft();
			cout << "this is new head: " << head->getNodeValue() << endl;
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
	else if (node->getRight()->getLeft() == 0) {
		result = node->CompareTo(parrentNode);
		if (parrentNode == 0) {
			head = node->getRight();
			head->setLeft(node->getLeft());
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

		if (parrentNode == 0) {
			head = LastLeft;
			head->setRight(node->getRight());
		}
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
	node->~treeNode();
	return true;
}

treeNode * binaryTree::search(int val, treeNode * anyNode, treeNode *& parrent) {

	while (anyNode != 0) {
		if (anyNode->getNodeValue() == val) {
			cout << "find: " << anyNode->getNodeValue() << endl;
			//cout << "parrent: " << (parrent)->getNodeValue() << endl;

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

void binaryTree::clear(treeNode * node) {
	node->~treeNode();
	head = 0;
	quantity = 0;
};

void binaryTree::PreOrderShelter(void (binaryTree::*fptr)(treeNode * ptr), treeNode * pointer) {
	PreOrder(fptr, pointer);
}

void binaryTree::PreOrder(void (binaryTree::*fptr)(treeNode * ptr), treeNode * pointer) {
	if (pointer != NULL) {
		(this->*fptr)(pointer);
		//cout << pointer->getNodeValue() << endl;
		PreOrder(fptr, pointer->getLeft());
		PreOrder(fptr, pointer->getRight());
	}
}

void binaryTree::PostOrderShelter(void (binaryTree::*fptr)(treeNode * ptr), treeNode * pointer) {
	PostOrder(fptr, pointer);
}

void binaryTree::PostOrder(void (binaryTree::*fptr)(treeNode * ptr), treeNode * pointer) {
	if (pointer != NULL) {
		PostOrder(fptr, pointer->getLeft());
		PostOrder(fptr, pointer->getRight());
		(this->*fptr)(pointer);
	}
}


void binaryTree::InOrderShelter(void (binaryTree::*fptr)(treeNode * ptr), treeNode * pointer) {
	InOrder(fptr, pointer);
}

void binaryTree::InOrder(void (binaryTree::*fptr)(treeNode * ptr), treeNode * pointer) {
	if (pointer != NULL) {
		InOrder(fptr,pointer->getLeft());
		(this->*fptr)(pointer);
		InOrder(fptr,pointer->getRight());
	}
}

treeNode * binaryTree::getHead() const {
	
	return head;
}

class CInterface {
 
public:
 void simpleInterface();
 void listener(int i, binaryTree *& pointer);
	
};

 void CInterface::listener(int i, binaryTree *& pointer) { 
	int val = 0;
	switch (i) {
	case 1: {
		if (pointer) {
			cout << "you cannot create one more tree" << endl;
			break;
		}
		else {
			cout << "Enter the head value for the tree" << endl;
			cin >> val;
			binaryTree tree(val);
			pointer = &tree;
			break;
		}
	}


	case 2: {
		cout << "Type int value for the tree" << endl;
		cin >> val;
		pointer->NewNode(val);
		break;
	}
	case 3: {
		cout << "listener "<< pointer/*->getHead()*/ <<" "/*<< pointer->getHead()->getNodeValue() */<< endl;
		cout << "Type the number which you want delete from tree" << endl;
		cin >> val;
		pointer->remove(val);
		break;
	}
	case 4: {
		cout << "Binary search tree in preorder" << endl;
		void(binaryTree::*fptr)(treeNode * ptr) = &binaryTree::showValue;
		pointer->PreOrderShelter(fptr, pointer->getHead());
		cout << endl;
		break;
	}
	case 5: {
		cout << "Binary search tree postorder" << endl;
		void(binaryTree::*fptr)(treeNode * ptr) = &binaryTree::showValue;
		pointer->PostOrderShelter(fptr, pointer->getHead());
		cout << endl;
		break;


	}
	case 6: {
		cout << "Binary search tree Inorder" << endl;
		void (binaryTree::*fptr)(treeNode * ptr) = &binaryTree::showValue;
		pointer->InOrderShelter(fptr, pointer->getHead());
		cout << endl;
		break;

	}
	}

}

 void CInterface::simpleInterface() {
	int i = 0;
	binaryTree * pointer = 0;
	while (i != 7) {
		if (i != 0) {

			//here is the problem place head pointer becomes nullptr like ccccccccc adress
			//do not know why
			treeNode *const holder = pointer->head;
			cout << "pointer " << pointer << endl;
			cout << "holder " << holder->getNodeValue() << endl;
			pointer->head = holder;
			cout << "before we path into listener " << pointer << " " << pointer->head << endl;
			cout << "before we path into listener " << pointer << " " << pointer->head << endl;
			cout << "holder " << holder->getNodeValue() << endl;

		}
		cout << "Menu" << endl;
		cout << "1. Create tree" << endl;
		cout << "2. Add new node to tree" << endl;
		cout << "3. Delete node from the tree" << endl;
		cout << "4. Show tree in Preorder" << endl;
		cout << "5. Show tree in Postorder" << endl;
		cout << "6. Show tree Inorder" << endl;
		cout << "7. End" << endl;
		
		cin >> i;
		if (i > 7 & i < 1) continue;
		listener(i, ref(pointer));
		
	}
}


int main() {
	
	CInterface object;

	object.simpleInterface();
/*
	binaryTree tree(10);

	void (binaryTree::*ptr)(treeNode * node) = &binaryTree::showValue;
	treeNode * node = tree.getHead();*/

	//check tree traversal algos
	//tree.InOrderShelter(ptr, node);
	//tree.PostOrderShelter(ptr, node);
	//tree.PreOrderShelter(ptr, node);
	// test user creats node
/*	int val = 0;
	int iter = 0;
	while (iter < 10) {
	cin >> val;
	tree.NewNode(val);
	iter++;
}
	cout << endl;
	cout << "inorder" << endl;
	tree.PreOrderShelter(ptr, node);
	cout << endl;


	cout << "what value would you like to remove" << endl;
	cin >> val;
	cout << endl;
	tree.remove(val);
	node = tree.getHead();*/
	/*cout<<tree.getHead()->getNodeValue()<<endl;
	cout << tree.getHead()->getLeft()->getNodeValue() << endl;
	cout << tree.getHead()->getLeft()->getLeft()->getNodeValue() << endl;*/
	//tree.PreOrderShelter(ptr, node);
	//cout << endl;
	//tree.InOrderShelter(ptr, node);
	
	//test binaryTree::clear() method
	/*void(binaryTree::*del)(treeNode * leaf) = &binaryTree::clear;
	tree.InOrderShelter(del, node);
	if (!tree.getHead()) cout << "remove done" << endl;*/

	system("pause");
	return 0;
}
#include "pch.h"
#include "CInterface.h"


#include <iostream>

using namespace std;


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
		if (pointer) {
			cout << "Type int value for the tree" << endl;
			cin >> val;
			pointer->NewNode(val);
		}
		else {
			cout << "First of all create the tree" << endl;
			cout << "To create the tree please press 1" << endl;
		}
		break;
	}
	case 3: {
		if (pointer) {
			cout << "Type the number which you want delete from tree" << endl;
			cin >> val;
			pointer->remove(val);
		}
		else {
			cout << "First of all create the tree" << endl;
			cout << "To create the tree please press 1" << endl;
		}
		break;
	}
	case 4: {
		if (pointer) {
			cout << "Binary search tree in preorder" << endl;
			void(binaryTree::*fptr)(treeNode * ptr) = &binaryTree::showValue;
			pointer->PreOrderShelter(fptr, pointer->getHead());
			cout << endl;
		}
		else {
			cout << "First of all create the tree" << endl;
			cout << "To create the tree please press 1" << endl;
		}
		break;
	}
	case 5: {
		if (pointer) {
			cout << "Binary search tree postorder" << endl;
			void(binaryTree::*fptr)(treeNode * ptr) = &binaryTree::showValue;
			pointer->PostOrderShelter(fptr, pointer->getHead());
			cout << endl;
		}
		else {
			cout << "First of all create the tree" << endl;
			cout << "To create the tree please press 1" << endl;
		}
		break;
	}
	case 6: {
		if (pointer) {
			cout << "Binary search tree Inorder" << endl;
			void (binaryTree::*fptr)(treeNode * ptr) = &binaryTree::showValue;
			pointer->InOrderShelter(fptr, pointer->getHead());
			cout << endl;
		}
		else {
			cout << "First of all create the tree" << endl;
			cout << "To create the tree please press 1" << endl;
		}
		break;
	}
	}
}
void CInterface::simpleInterface() {
	int i = 0;
	binaryTree * pointer = 0;
	while (i != 7) {
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

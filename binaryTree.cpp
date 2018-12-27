#include "pch.h"
#include "binaryTree.h"
#include <iostream>
using namespace std;

treeNode * binaryTree::head;

using namespace std;
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
	treeNode* node = this->search(value, this->head, ref(parrentNode));
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
		InOrder(fptr, pointer->getLeft());
		(this->*fptr)(pointer);
		InOrder(fptr, pointer->getRight());
	}
}
treeNode * binaryTree::getHead() const {
	return head;
}

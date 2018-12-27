#pragma once
#include "treeNode.h"
class binaryTree {
	int quantity;
	//treeNode * head;
	void PreOrder(void (binaryTree::*fptr)(treeNode * ptr), treeNode * pointer);
	void PostOrder(void (binaryTree::*fptr)(treeNode * ptr), treeNode * pointer);
	void InOrder(void (binaryTree::*fptr)(treeNode * ptr), treeNode * pointer);
	void addTo(treeNode * node, treeNode * firstNode);
public:
	static treeNode * head;
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

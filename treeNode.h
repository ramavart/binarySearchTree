#pragma once
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


#include<iostream>

using namespace std;

template<typename T>
class TreeNode {
private:
	T Data;
	TreeNode *LChild;
	TreeNode *RChild;
public:
	TreeNode(const T &data) {
		this->Data = data;
	}

	TreeNode() {
		cout << "an empty node is created" << endl;
	}

	void AddData(T data) {
		this->Data = data;
	}

	TreeNode* lchild() {
		if(this->LChild != nullptr) {
			return LChild;
		}
		else{
			cout << "this node has no left child" << endl;
			
		}
		return this;
	}

	TreeNode* rchild() {
		if (RChild != nullptr) {
			return RChild;
		}
		else {
			cout << "this node has no right child" << endl;
		}
		return this;
	}


};

template<typename T>
class Tree {
private:
	TreeNode<T>* Root;
public:
	Tree() {
		TreeNode* r = new TreeNode();
		this->Root = r;
	}
};


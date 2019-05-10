#include<iostream>
#include<string>
#include<vector>

using namespace std;

template<class T>
class Node {
private:
	T Data;
	vector<Node<T>*> children;
	int numberOfChildren = 0;
	Node<T>* Parent;


public:

	void pint_my_address() {
		cout << this << endl;
	}

	Node() {
		cout << "a new empty node!" << endl;
		cout << this << endl;
	}
	int getData() {
		return Data;
	}
	void setData(int data) {
		Data = data;
	}
	vector<Node*> getChilden() {
		return children;
	}
	void addChild(Node* childPtr ) {
		children.push_back(childPtr);
		numberOfChildren++;
	}

	Node<T>* addChild(int data) {
		Node* newChild = new Node;
		newChild->setData(data);
		children.push_back(newChild);
		numberOfChildren++;

	}

	void deleteChild(Node* childPtr) {
		for (int i = 0; i < this->numberOfChildren; i++) {
			if (childPtr == this->children[i]) {
				children.erase(children.begin() + i);
				numberOfChildren--;
				return;
			}
		}
		cout << childPtr << " is not a child of " << this << endl;
	}
	
	void setParent(Node* p) {
		Parent = p;
	}
	Node* getParent() {
		return this->Parent;
	}
};


template<class T>
class undirectedGraph {
private:
	Node<T>* Vertices[100];

};

template<class T>
class Tree {
private:
	Node<T>* Root;
	Node<T>* Current;
public:
	Tree(Node<T>* root) {
		this->Root = root;
		this->Current = root;
		cout << "a tree is constructed, its root is: " << root << endl;
	}
	Tree() {
		Node *root = new Node;
		this->Root = root;
		this->Current = root;
		cout << "this->Root: " << this->Root << endl;
		cout << "this->Current: " << this->Current << endl;
	}

	void attachNode(Node* n) {
		n->setParent(Current);
		Current->addChild(n);
		this->Current = n;
		cout << "a new node " << n << " has been attached to the current node " << Current << endl;
	}
	
	void attachNode(int d) {
		Node* newNode = new Node;
		newNode->setData(d);
		attachNode(newNode);

	}

	bool is_leaf(Node* n) {
		return n->getChilden().empty();
	}

	void deleteNode() {
		Node* n = this->Current;
		if (is_leaf(n)) {//if current node is a leaf, it can be deleted immediately
			this->Current = this->Current->getParent();
			n->getParent()->deleteChild(n);
		}else{
			cout << "do you want to delete this node and its subtree? [Y/N]" << endl;
			char a;
			cin >> a;
			if (a == 'Y') {
				this->Current = this->Current->getParent();
				n->getParent()->deleteChild(n);
			}
			else if (a == 'N') {
				cout << "exiting function deleteNode()" << endl;
				return;
			}
		}
	}

	void DFS(vector<Node<T>*> &unread) {
		while (unread.empty() == false) {
			cout << unread[0]->getData() << endl;
			vector<Node*> children = unread[0]->getChilden();
			unread.erase(unread.begin());
			unread.insert(unread.begin(), children.begin(), children.end());
			
		}
	}

	void BFS(vector<Node<T>*> &unread) {
		while (unread.empty() == false) {
			cout << unread[0]->getData() << endl;
			vector<Node*> children = unread[0]->getChilden();
			unread.erase(unread.begin());
			unread.insert(unread.end(), children.begin(), children.end());
		}
	}

	void BFS() {
		vector<Node<T>*> unread;
		unread[0] = this->Root;
		BFS(unread);
	}

};

template<class T>
class BinaryTree : Tree<T> {
private:
	Node<T>* root;
public:
	BinaryTree() :Tree() {
		cout << "a binary tree!" << endl;
		cout << this << endl;
	}

	void left_rotate() {

	}

	void right_rotate() {

	}


};


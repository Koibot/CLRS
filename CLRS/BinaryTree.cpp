#include<iostream>
#include<string>
#include<vector>

using namespace std;


class Node {
//private:
//	int Data;
//	vector<Node*> children;
//	int numberOfChildren = 0;
//	Node* Parent;

public:

	int Data;
	vector<Node*> children;
	int numberOfChildren = 0;
	Node* Parent;

	void see_my_address() {
		cout << this << endl;
	}

	Node() {
		cout << "a new empty node!" << endl;
		cout << this << endl;
	}
	int GetData() {
		return this->Data;
	}
	void SetData(int data) {
		this->Data = data;
	}
	vector<Node*> getChilden() {
		return this->children;
	}
	void addChild(Node* childPtr) {
		children.push_back(childPtr);
		numberOfChildren++;
	}

	Node* addChild(int data) {
		Node* newChild = new Node;
		newChild->SetData(data);
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

	void SetParent(Node*& p) {
		Parent = p;
	}
	Node* GetParent() {
		cout << "return a type of " << typeid(this).name() << endl;
		return this->Parent;
	}

};

template<class T>
class BinaryTreeNode {
private:
	BinaryTreeNode<T>* Parent;
	BinaryTreeNode<T>* LChild;
	BinaryTreeNode<T>* RChild;
	T Data;

public:
	BinaryTreeNode():Parent(0), LChild(0), RChild(0) {
		cout << "a binary tree node is created" << endl;
	}

	BinaryTreeNode<T>*& GetParent() {
		cout << "meow?" << endl;
		return this->Parent;
	}


	void SetParent(BinaryTreeNode<T>*& p) {
		this->Parent = p;
	}

	void attachLeftChild(BinaryTreeNode<T>*& BTNode) {
		this->LChild = BTNode;
		BinaryTreeNode<T>* Ppt = this;// new BinaryTreeNode<T>;
		BTNode->SetParent(Ppt);
	}



	void attachRightChild(BinaryTreeNode<T>*& BTNode) {
		this->RChild = BTNode;
		BinaryTreeNode<T>* Ppt = this;
		BTNode->SetParent(Ppt);
	}


	

	void SetData(T data) {
		this->Data = data;
	}

	T GetData() {
		return this->Data;
	}

	BinaryTreeNode<T>*& GetLChild() {
		return this->LChild;
	}

	BinaryTreeNode<T>*& GetRChild() {
		return this->RChild;
	}

};

template<class T>
class BinaryTree {
private:
	BinaryTreeNode<T>* Root;
public:
	BinaryTree() {
		cout << "a binary tree is created" << endl;
		cout << "with a root at " << this->Root << endl;
	}
	BinaryTree(BinaryTreeNode<T>*& r) {
		this->Root = r;
		cout << "a binary tree with root is created" << endl;
	}

	void SetRoot(BinaryTreeNode<T>*& r) {
		this->Root = r;
	}

	BinaryTreeNode<T>*& GetRoot() {
		return this->Root;
	}

	void BFS(vector<BinaryTreeNode<T>*>*& unread) {
		if (unread->size()==0) {
			return;
		}
		cout << ((*unread)[0])->GetData() << endl;
		BinaryTreeNode<T>* LC = ((*unread)[0])->GetLChild();//
		BinaryTreeNode<T>* RC = ((*unread)[0])->GetRChild();//
		if (LC != nullptr) {
			unread->push_back(LC);
		}
		if (RC != nullptr) {
			unread->push_back(RC);
		}
		unread->erase(unread->begin());
		BFS(unread);
	}
	void BFS(BinaryTreeNode<T>*& subTreeNode) {
		vector<BinaryTreeNode<T>*>* unread = new vector<BinaryTreeNode<T>*>;
		unread->insert(unread->begin(), subTreeNode);
		BFS(unread);
		delete unread;
	}
	void BFS() {
		BFS(this->Root);
	}

	void DFS(vector<BinaryTreeNode<T>*>*& unread) {
		if (unread->size() == 0) {
			return;
		}
		cout << ((*unread)[0])->GetData() << endl;
		BinaryTreeNode<T>* LC = ((*unread)[0])->GetLChild();
		BinaryTreeNode<T>* RC = ((*unread)[0])->GetRChild();
		unread->erase(unread->begin());
		if (RC != nullptr) {
			unread->insert(unread->begin(), RC);
		}
		if (LC != nullptr) {
			unread->insert(unread->begin(), LC);
		}
		DFS(unread);

	}

	void DFS(BinaryTreeNode<T>*& subTreeNode) {
		vector<BinaryTreeNode<T>*>* unread = new vector<BinaryTreeNode<T>*>;
		unread->insert(unread->begin(), subTreeNode);
		DFS(unread);
		delete unread;
	}
	
	void DFS() {
		DFS(this->Root);//why there's no error sign in this line?
	}


	void LeftRotate(BinaryTreeNode<T>* SubTreeRoot) {
		BinaryTreeNode<T>* p = SubTreeRoot->GetParent();
		BinaryTreeNode<T>* subtree_right = SubTreeRoot->GetRChild();
		BinaryTreeNode<T>* subtree_right_left = subtree_right->GetLChild();
		if (p->GetLChild() == SubTreeRoot) {
			p->attachLeftChild(subtree_right);
		}
		else {
			p->attachRightChild(subtree_right);
		}
		subtree_right->SetParent(p);
		subtree_right->attachLeftChild(SubTreeRoot);
		SubTreeRoot->SetParent(subtree_right);
		SubTreeRoot->attachRightChild(subtree_right_left);
		subtree_right_left->SetParent(SubTreeRoot);

	}

	void RightRotate(BinaryTreeNode<T>* SubTreeRoot) {
		BinaryTreeNode<T>* p = SubTreeRoot->GetParent();
		BinaryTreeNode<T>* subtree_left = SubTreeRoot->GetLChild();
		BinaryTreeNode<T>* subtree_left_right = subtree_left->GetRChild();
		if (p->GetLChild() == SubTreeRoot) {
			p->attachLeftChild(subtree_left);
		}
		else {
			p->attachRightChild(subtree_left);
		}
		subtree_left->SetParent(p);
		SubTreeRoot->attachLeftChild(subtree_left_right);
		subtree_left_right->SetParent(SubTreeRoot);
		subtree_left->attachRightChild(SubTreeRoot);
		SubTreeRoot->SetParent(subtree_left);

	}

};



template<class T>
class BinarySearchTree: public BinaryTree<T> {
public:

	BinaryTreeNode<T>*& GetBSTRoot() {
		return GetRoot();
	}
	void SetBSTRoot(BinaryTreeNode<T>*& r) {
		SetRoot(r);
	}

	void Insert(T data, BinaryTreeNode<T>*& SubTreeRoot) {
		cout << "starting Insert(T data, BinaryTreeNode<T>* SubTreeRoot)" << endl;
		if (data <= SubTreeRoot->GetData()) {
			cout << "data:" << data << " <= SubTreeRoot_>GetData(): " << SubTreeRoot->GetData() << endl;
			if (SubTreeRoot->GetLChild() == 0) {
				BinaryTreeNode<T>* NewNode = new BinaryTreeNode<T>;
				NewNode->SetData(data);
				SubTreeRoot->attachLeftChild(NewNode);
			}
			else {
				Insert(data, SubTreeRoot->GetLChild());
			}
		}
		else if (data > SubTreeRoot->GetData()) {
			cout << "data:" << data << " > SubTreeRoot_>GetData(): " << SubTreeRoot->GetData() << endl;
			if (SubTreeRoot->GetRChild() == 0) {
				BinaryTreeNode<T>* NewNode = new BinaryTreeNode<T>;
				NewNode->SetData(data);
				SubTreeRoot->attachRightChild(NewNode);
			}
			else {
				Insert(data, SubTreeRoot->GetRChild());
			}
		}
		cout << "end of Insert(T data, BinaryTreeNode<T>* SubTreeRoot)" << endl;
	}

	void Generate(vector<T> &v) {
		cout << "starting Generate(vector<T> &v) " << endl;
		if (GetBSTRoot() == nullptr) {
			BinaryTreeNode<T>* root = new BinaryTreeNode<T>;
			root->SetData(v[0]);
			SetBSTRoot(root);
			v.erase(v.begin());

		}
		for (int i = 0; i < v.size(); i++) {
			Insert(v[i], GetBSTRoot());
		}
		cout << "end of Generate(vector<T> &v)" << endl;
	}

	void Search(T data) {

	}

};



void BTmain() {

	BinarySearchTree<int> TestBST;
	int arr[] = { 1,4,2,6,4,3,7,9,8,3,2,7,1 };
	vector<int> v(arr, arr + 13);
	TestBST.Generate(v);
	TestBST.DFS();
	cout << "exit" << endl;
	system("pause");
}
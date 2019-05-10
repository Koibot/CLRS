#include<iostream>
#include<queue>
using namespace std;



const int MaxChildren = 10;

template<typename T> class Tree;

//template<typename T> Tree<T>* to_tree();


template<class T>
class TreeNode {
private:
	T data_;
	TreeNode** children_;
	int children_ptr_;
public:
	friend class Tree<T>;
	TreeNode(const T& data);
	TreeNode(const TreeNode& tn);
	TreeNode();
	Tree<T>* to_tree();
	TreeNode& operator=(TreeNode& tn);
	T data();
	void add_child(const T& child_data);
	void add_child(TreeNode* tn);
};

template<class T>
TreeNode<T>::TreeNode(const T& data) :data_(data), children_ptr_(-1) {
	this->data_ = data;
	children_ = new TreeNode*[MaxChildren];
}

template<class T>
TreeNode<T>::TreeNode() {}



template<class T>
void TreeNode<T>::add_child(const T& child_data) {
	TreeNode<T>* nn = new TreeNode<T>(child_data);
	add_child(nn);
}

template<class T>
void TreeNode<T>::add_child(TreeNode<T>* tn) {
	cout << tn->data_ << endl;
	if (this->children_ptr_ == MaxChildren - 1) {
		cout << "can't add another child to this node" << endl;
		return;
	}
	this->children_ptr_++;
	cout << children_ptr_ << endl;
	if (this->children_ == nullptr) {
		this->children_ = new TreeNode*[MaxChildren];
	}
	this->children_[this->children_ptr_] = tn;
	//this->cur_ = nn;
	return;
}


template<class T>
Tree<T>* TreeNode<T>::to_tree() {
	Tree<T>* nt = new Tree<T>(this);
	return nt;
}

template<class T>
TreeNode<T>& TreeNode<T>::operator=(TreeNode<T>& tn) {
	if (this != &tn) {
		if (this->children_ != nullptr) {
			delete[] this->children_;
		}
		this->children_ = tn.children_;
		this->children_ptr_ = tn.children_ptr_;
		this->data_ = tn.data_;
	}
	return tn;
}

template<class T>
T TreeNode<T>::data() {
	return data_;
}


template<class T>
class Tree {
private:
	TreeNode<T>* root_;
	TreeNode<T>* cur_;
public:
	Tree(TreeNode<T>* root);

	Tree(const T& root);

	Tree();

	void add_subtree(Tree<T>* subtree);

	void add_subtree(TreeNode<T>* tn);

	void DFS(TreeNode<T>* tn);

	void BFS(TreeNode<T>* tn, queue<TreeNode<T>*> wait_list);

	void DFS();

	void BFS();

};

void Tree_Test();



template<class T>
Tree<T>::Tree(TreeNode<T>* root) :root_(root), cur_(root) {}

template<class T>
Tree<T>::Tree(const T& data):root_(new TreeNode<T>(data)), cur_(new TreeNode<T>(data)){}

template<class T>
Tree<T>::Tree(){}

template<class T>
void Tree<T>::add_subtree(Tree<T>* subtree) {
	this->cur_->add_child((subtree->root_));
}

template<class T>
void Tree<T>::add_subtree(TreeNode<T>* tn) {
	if (this->root_ == nullptr) {
		this->root_ = tn;
		this->cur_ = tn;
	}
	this->cur_->add_child(tn);
}

template<class T>
void Tree<T>::DFS(TreeNode<T>* tn) {
	if (tn->children_ptr_ == -1) {
		cout << "reaching a leaf node" << endl;
		cout << tn->data_ << endl;
		return;
	}
	for (int i = 0; i <= tn->children_ptr_; i++) {
		TreeNode<T>* child = tn->children_[i];
		DFS(child);
	}
	cout << tn->data_ << endl;
	return;
}


template<class T>
void Tree<T>::DFS() {
	DFS(this->root_);
}


template<class T>
void Tree<T>::BFS(TreeNode<T>* tn, queue<TreeNode<T>*> wait_list) {

	T data = tn->data_;
	cout << data << end;
	if (tn->children_ptr_ != -1) {

		for (int i = 0; i < children_ptr_; i++) {
			wait_list.push(tn->children_[i]);
		}
	}
}


template<typename T>
class Heap: public Tree<T> {
public:
	Heap(){}
};

template<typename T>
class MaxPriorityQueue {
public:
	virtual void Insert(const TreeNode<T>&) = 0;
	virtual TreeNode<T>* DeleteMax(T&) = 0;
};


int Tree_main() {
	cout << "c" << endl;
	TreeNode<char>* tn = new TreeNode<char>('c');
	cout << "d" << endl;
	TreeNode<char>* tnd = new TreeNode<char>('d');
	cout << "e" << endl;
	TreeNode<char>* tne = new TreeNode<char>('e');
	Tree<char> test_tree(tn);
	Tree<char>* t2 = new Tree<char>('k');
	test_tree.add_subtree(tnd);
	test_tree.add_subtree(tne);
	test_tree.add_subtree(t2);
	test_tree.DFS();
	system("pause");
	return 0;
}

#include<iostream>

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
	void add_child(TreeNode& tn);
};

template<class T>
TreeNode<T>::TreeNode(const T& data) :data_(data), children_ptr_(-1) {}

template<class T>
TreeNode<T>::TreeNode() {}

template<class T>
TreeNode<T>::TreeNode(const TreeNode<T>& tn) :data_(tn.data_), children_ptr_(tn.children_ptr_) {
	children_ = new TreeNode*[MaxChildren];
	memset(this->children_, 0, sizeof(this->children_));
	for (int i = 0; i < MaxChildren; i++) {
		TreeNode* nn = new TreeNode(tn.children_[i]->data_);
		this->children_[i] = nn;
	}
}


template<class T>
void TreeNode<T>::add_child(const T& child_data) {
	TreeNode<T>* nn = new TreeNode<T>(child_data);
	add_child(*nn);
}

template<class T>
void TreeNode<T>::add_child(TreeNode<T>& tn) {
	if (this->children_ptr_ == MaxChildren - 1) {
		cout << "can't add another child to this node" << endl;
		return;
	}
	this->children_ptr_++;
	this->children_[this->children_ptr_] = &tn;
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

template class TreeNode<char>;
template class Tree<char>;
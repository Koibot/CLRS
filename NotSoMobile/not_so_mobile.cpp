#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
const int buffersize = 256;
const int max_children = 10;

using namespace std;

template<class datatype> class Tree;

//do you have to be so hard core?
template<class datatype>
class TreeNode {
private:
	datatype data_;
	vector<TreeNode*> children_;
	int children_number_;

public:

	template<class u> friend class Tree;

	TreeNode(const datatype& data):data_(data), children_number_(0){}

	void AddChild(TreeNode* child) {
		if (children_number_ == max_children) {
			cout << "can not add a new child to this node" << endl;
			return;
		}
		children_.push_back(child);
		children_number_++;
	}

	void AddChild(datatype data) {
		TreeNode<datatype>* ntn = new TreeNode(data);
		AddChild(ntn);
	}

	void PrintChildrenAddr() {
		cout << "supposed to print the address of each child in this node?" << endl;
		for (vector<TreeNode*>::iterator iter = children_.begin(); iter != children_.end(); iter++) {
			cout << *iter << " ";
		}
		cout << endl;
	}

};

template<class datatype>
class Tree {
private:
	TreeNode<datatype>* root_;
public:
	Tree() :root_(0) {
		cout << "an empty tree is created" << endl;
	}
	Tree(TreeNode<datatype>* root):root_(root){}
	void AddBranch(TreeNode<datatype>* newnode, TreeNode<datatype>*) {

	}
	void DFS(TreeNode<datatype>* tn) {
		if (tn->children_number_ != 0) {
			for (vector<TreeNode<datatype>*>::iterator iter = tn->children_.begin(); iter < tn->children_.end(); iter++) {
				DFS(*iter);
			}
		}
		cout << tn->data_ << endl;
	}
	void DFS() {
		DFS(root_);
	}
};

template<class T>
T Calculate(vector<T>* parameters, int& p) {
	T left;
	T right;
	cout << "let's see the parameter" << endl;
	for (vector<T>::iterator iter = parameters[p].begin(); iter != parameters[p].end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;
	if (parameters[p][0] == 0 && parameters[p][2] == 0) {
		cout << "calculate left recursively" << endl;
		p++;
		left = Calculate(parameters, p);
		parameters[p][0] = left;
		cout << "calculate right recursively" << endl;
		p++;
		right = Calculate(parameters, p);
		parameters[p][2] = right;
	}
	else if (parameters[p][2] == 0) {
		cout << "calculate right recursively" << endl;
		p++;
		right = Calculate(parameters, p);
		parameters[p][2] = right;
	}
	else if (parameters[p][0] == 0) {
		cout << "calculate left recursively" << endl;
		p++;
		right = Calculate(parameters, p);
		parameters[p][0] = right;
	}
	else if (parameters[p][0] * parameters[p][1] == parameters[p][2] * parameters[p][3]) {
		int r = parameters[p][0] + parameters[p][2];
		cout << "return value: " << r << endl;
		return r;
	}
	else {
		cout << "imbalanced branch found" << endl;
		return -1;
	}
}

void main() {
	char buffer[buffersize];
	ifstream file("test_mobile.txt");
	if (!file.is_open()) {
		cout << "kekekekekekekeke" << endl;
	}
	cout << "?????" << endl;
	TreeNode<int>* Root = new TreeNode<int>(-1);
	Tree<int> test_tree(Root);
	vector<int>* parameters = new vector<int>[10];
	int p = 0;
	while (!file.eof()) {
		file.getline(buffer, 256);
		vector<int> parameter;
		cout << "get line" << endl;
		stringstream ss(buffer);
		int i;
		while (ss >> i) {
			parameter.push_back(i);
		}
		parameters[p] = parameter;
		p++;
	}

	int i = 0;

	int r = Calculate(parameters, i);


	system("pause");
}
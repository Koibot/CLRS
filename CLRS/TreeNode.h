#ifndef _TREENODE_H_
#define _TREENODE_H_

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
	void add_child(TreeNode& tn);
};





#endif
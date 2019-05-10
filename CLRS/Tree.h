#ifndef _TREE_H_
#define _TREE_H_
using namespace std;

template<typename T> class TreeNode;

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

	void DFS();

};

void Tree_Test();
#endif // !_TREE_H_


#ifndef _OPERANDS_H_
#define _OPERANDS_H_

#include<iostream>
#include"Stack.h"
#include"TreeNode.h"
#include"Tree.h"

using namespace std;

int priority(char c);

void build_exp_tree(Stack<TreeNode<char>*>& sub_exp_stack);

//void build_exp_tree(char*& exp);

void Operands();

#endif // !1

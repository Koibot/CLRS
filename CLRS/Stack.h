#ifndef _STACK_H_
#define _STACK_H_

#include<iostream>
using namespace std;


template<class KeyType>
class Stack {
private:
	int top;
	KeyType* stack;
	int MaxSize;
public:
	template<class KeyType, typename a, typename b>
	friend basic_ostream<a, b>& operator<<(basic_ostream<a, b>& os, const Stack<KeyType>& stack);
	Stack(int MaxStackSize);
	~Stack();

	bool IsFull();
	bool IsEmpty();

	void StackFull();

	void Push(KeyType item);

	KeyType Pop();

	KeyType Top();

	int len();

};



template<class KeyType, typename a, typename b>
basic_ostream<a, b>& operator<<(basic_ostream<a, b>& os, const Stack<KeyType>& s);

//void stack_main() {
//	int MaxStackSize = 1024;
//	Stack<int> test_stack(MaxStackSize);
//	test_stack.Push(3);
//	test_stack.Push(2);
//	test_stack.Push(9);
//	test_stack.Push(0);
//	test_stack.Push(6);
//	cout << test_stack << endl;
//	int* i = test_stack.Pop();
//	cout << test_stack << endl;
//	cout << *i << endl;
//	system("pause");
//}






#endif
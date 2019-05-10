#include<iostream>
#include"Stack.h"

template<class KeyType>
Stack<KeyType>::Stack(int MaxStackSize) : MaxSize(MaxStackSize) {
	stack = new KeyType[MaxSize];
	top = -1;
}

template<class KeyType>
Stack<KeyType>::~Stack() {
	delete[] stack;
}

template<class KeyType>
bool Stack<KeyType>::IsFull() {
	if (top == MaxSize - 1) {
		return true;
	}
	return false;
}

template<class KeyType>
bool Stack<KeyType>::IsEmpty() {
	if (top == -1) {
		return true;
	}
	return false;
}

template<class KeyType>
void Stack<KeyType>::StackFull() {
	if (IsFull()) {
		KeyType* NewStack = new KeyType[2 * MaxSize];
		memcpy(NewStack, stack, sizeof(KeyType)*MaxSize);
		delete[] stack;
		stack = NewStack;
	}
}

template<class KeyType>
KeyType Stack<KeyType>::Top() {
	return this->stack[top];
}

template<class KeyType>
int Stack<KeyType>::len() {
	return top + 1;
}

template<class KeyType>
void Stack<KeyType>::Push(KeyType item) {
	if (IsFull()) {
		cout << "stack is full" << endl;
		return;
	}
	top++;
	stack[top] = item;
	return;
}

template<class KeyType>
KeyType Stack<KeyType>::Pop() {
	/*if (IsEmpty()) {
		cout << "stack is empty" << endl;
		return 0;
	}*/
	KeyType item = stack[top];
	top--;
	return item;
}

template<class KeyType, typename a, typename b>
basic_ostream<a,b>& operator<<(basic_ostream<a, b>& os, const Stack<KeyType>& s) {
	//KeyType* p = s.stack;
	for (int i = s.top; i >= 0; i--) {
		os << s.stack[i] << " ";
	}
	os << endl;
	return os;
}

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


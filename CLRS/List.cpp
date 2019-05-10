#pragma once

#include<iostream>
#include<string>
#include<fstream>

using namespace std;

#define MaxLength 10;

template<class T>
class List;

template<class T>
class ListIterator;

template<class T>
class Node {
private:
	T data;
	Node* next;

public:

	friend class List<T>;
	friend class ListIterator<T>;

	Node(const T& Data) :data(Data), next(0) {}

	template<class T, typename a, typename b>
	friend basic_ostream<a, b>& operator<<(basic_ostream<a, b>& os, const Node<T>& n);

	template<class T>
	friend ostream& operator<<(ostream& os, const List<T>& lst);
};

template<class T>
class List {
private:
	const int m = MaxLength;
	int len;
	Node<T>* first;
	Node<T>* last;
public:
	friend class ListIterator<T>;
	template<class T>
	friend ostream& operator<<(ostream& os, const List<T>& lst);

	List():first(0),last(0) {}

	void delete_data(T d) {
		if (first == nullptr) {
			cout << "no element in the list to be deleted" << endl;
			return;
		}
		Node<T>* cur = first->next;
		Node<T>* prev = first;
		if (first->data == d) {
			Node<T>* del = first;
			first = first->next;
			delete del;
			return;
		}
		while (cur != nullptr) {
			if (cur->data <= d) {
				if (cur->data == d) {
					prev->next = cur->next;
					delete cur;
					return;
			}
				prev = cur;
				cur = cur->next;
				continue;
			}
		}
		cout << "no such element in the list" << endl;
	}

	void insert_data(T d) {
		cout << "first: " << first << endl;
		Node<T>* nd = new Node<T>(d);
		cout << "nd: " << nd << endl;
		//T d = nd->data;
		if (first == nullptr) {
			cout << "e" << endl;
			first = nd;
			last = nd;
			nd->next = 0;
			return;
		}

		if (first->next == nullptr) {
			cout << "fne" << endl;
			if (first->data > d) {
				nd->next = first;
				first = nd;
			}
			else {
				first->next = nd;
				nd->next = 0;
				last = nd;
			}
			return;
		}
		Node<T>* ptr = first;
		if (first->data > d) {
			cout << "n" << endl;
			nd->next = first;
			first = nd;
			return;
		}
		while (ptr != nullptr) {
			if (ptr->next!=nullptr && ptr->next->data < d) {
				cout << "a" << endl;
				ptr = ptr->next;
				continue;
			}
			else if(ptr->next != nullptr && ptr->next->data >= d) {
				cout << "b" << endl;
				nd->next = ptr->next;
				ptr->next = nd;
				break;
			}
			else if (ptr->next == nullptr) {
				cout << "c" << endl;
				nd->next = 0;
				ptr->next = nd;
				last = nd;
				break;
			}
		}
		this->len++;
		cout << "first: " << first << endl;
		cout << "first->data: " << first->data << endl;
	}

	void attach_rear(T d) {
		Node<T>* nd = new Node<T>(d);
		this->last->next = nd;
		nd->next = 0;
		this->last = nd;
	}

	void attach_front(T d) {
		Node<T>* nd = new Node<T>(d);
		nd->next = first;
		first = nd;
	}

	void delete_front() {
		Node<T>* temp = this->first->next;
		delete first;
		first = temp;
	}

	void delete_rear() {
		Node<T>* ptr = first;
		for (ptr; ptr->next != last; ptr = ptr->next);
		ptr->next = 0;
		delete last;
	}

	void invert() {
		Node<T>* prev = this->first;
		Node<T>* cur = prev->next;
		Node<T>* nxt = cur->next;
		while (nxt != nullptr) {
			nxt = cur->next;
			cur->next = prev;
			prev = cur;
			cur = nxt;
		}
		this->first->next = 0;
		this->last = first;
		this->first = prev;
	}

	void is_empty() {
		if (first == nullptr) {
			cout << "this is an empty list" << endl;
		}
		else {
			cout << first << endl;
		}
		return;
	}

};

template<class T>
class ListIterator {
private:

	Node<T>* current;
	const List<T>& list;

public:

	bool NotNull() {
		if (current) {
			return true;
		}
		else {
			return false;
		}
	}

	bool NextNotNull() {
		if (current->next&&current) {
			return true;
		}
		else {
			return false;
		}
	}

	ListIterator(const List<T> &lst):current(lst.first), list(lst){}

	T* first() {
		if (this->list.first) {
			return &list.first->data;
		}
		else return 0;
	}

	T* next() {
		if (current) {
			current = current->next;
			if (current) {
				return &current->data;
				}
			}
		else {
			return 0;
		}

	}
};



template<class T, typename a, typename b>
basic_ostream<a,b>& operator<<(basic_ostream<a, b>& os, const Node<T>& n) {
	os << n.data;
	return os;
}

template<class T>
ostream& operator<<(ostream& os, const List<T>& lst) {
	//Node<T>* p = lst.first;
	/*while (p != nullptr) {
		T dt = p->data;
		os << dt << " ";
		p = p->next;
	}
	os << endl;
	return os;*/

	ListIterator<T> lit(lst);
	if (!lit.NotNull()) {
		return os;
	}
	os << *lit.first() << " ";
	while (lit.NextNotNull()) {
		//lit.next();
		os << *lit.next() << " ";
	}
	os << endl;
	return os;
}



void main_list() {
	List<int> test_list;
	test_list.is_empty();
	test_list.insert_data(10);
	test_list.insert_data(5);
	test_list.insert_data(9);
	test_list.insert_data(2);
	test_list.insert_data(17);
	test_list.insert_data(4);
	test_list.insert_data(7);
	test_list.insert_data(13);
	test_list.insert_data(1);
	cout << test_list << endl;
	test_list.invert();
	cout << test_list << endl;
	system("pause");
	
}

template class List<int>;
template class ListIterator<int>;
ostream& operator<<(ostream& os, const List<int>& lst);


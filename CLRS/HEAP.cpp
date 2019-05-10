#include<iostream>
#include<vector>
#include<ostream>

using namespace std;

static int HeapSize;


template<class T>
class Node {
private:
	T data_;

};


template<class T>
class MinHeap {
private:
	T* HeapArray;//Heap the vector
	int EleCnt;
	int t;
public:
	/*
	A function with "const" in front of its definition 
	cannot change the value of class member
	*/

	MinHeap() : EleCnt(0), HeapArray(new T[HeapSize]), t(0){
		memset(HeapArray, 0, sizeof(T)*HeapSize);
	}

	template<typename a_char, typename a_trait, typename T >
	friend basic_ostream<a_char, a_trait>& operator<<(basic_ostream<a_char, a_trait>& os, const MinHeap<T>& mh);

	void Insert(const T& data) {
		if (EleCnt==0) {
			HeapArray[0] = data;
			EleCnt++;
			return;
		}
		int ptr = EleCnt;
		HeapArray[ptr] = data;
		int ptr_parent = ceil(ptr/2) - 1;
		while (1) {
			if (HeapArray[ptr_parent] < data) {
				EleCnt++;
				break;
			}
			T temp = HeapArray[ptr];
			HeapArray[ptr] = HeapArray[ptr_parent];
			HeapArray[ptr_parent] = temp;
			ptr = ptr_parent;
			ptr_parent = ceil(ptr / 2) - 1;

			
		}
		return;
	}

	T LeftChild(int ptr) const {//get left element.
		T l = HeapArray[2 * ptr];
		return l;
	}

	T RightChild(int ptr) const {
		T r = HeapArray[2 * ptr + 1];
		return r;
	}

	T Parent(int ptr) const {
		T p = HeapArray[ceil(ptr / 2) - 1];
		return p;
	}

	void max_heapify() {
	}
	void heapsort();
	int heap_size() {
		return heapSize;
	}

};

template<typename a_char, typename a_trait, typename T >
basic_ostream<a_char, a_trait>& operator<<(basic_ostream<a_char, a_trait>& os, const MinHeap<T>& mh) {
	for (int i = 0; i < mh.EleCnt; i++) {
		T d = mh.HeapArray[i];
		os << d << ", ";
	}
	os << endl;
	/*int t = mh.t;
	while (mh.t<=EleCnt) {
		int t = mh.t;
		os << mh.HeapArray[i] << ", ";
		if (mh.t * 2 <= mh.EleCnt) {
			mh.t = mh.t * 2;
			os = operator<<(os, mh);
		}
		if (mh.t * 2 + 1 <= mh.EleCnt) {
			mh.t = mh.t * 2 + 1;
			os = operator<<(os, mh);
		}
	}*/


	return os;
}

int main() {
	MinHeap<int> testheap;
	testheap.Insert(6);
	testheap.Insert(8);
	testheap.Insert(3);
	testheap.Insert(9);
	testheap.Insert(2);
	testheap.Insert(10);
	testheap.Insert(5);
	testheap.Insert(7);
	testheap.Insert(16);
	testheap.Insert(1);
	cout << testheap << endl;
	system("pause");
}
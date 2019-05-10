#include<iostream>
#include<algorithm>
#include"time.h"


using namespace std;

const int ArrayLen = 16;

void Merge(int* A, int beginning, int end) {
	if (beginning == end) {
		return;
	}
	//cout << "merge" << endl;
	int len = end - beginning + 1;
	int c = 0;
	while (c < len / 2) {
		cout << A[beginning + c] << ", " << A[end - c] << endl;
		if (A[beginning + c] > A[end - c]) {
			int temp = A[beginning + c];
			A[beginning + c] = A[end - c];
			A[end - c] = temp;
		}
		c++;
	}
	cout << "end merge" << endl;
}

void Sort(int *A, const int beginning, const int end) {
	if (beginning == end) {
		return;
	}
	int len = end - beginning + 1;
	int h = len / 2;
	for (int i = 0; i < h; i++) {
		//cout << A[beginning + i] << ", " << A[beginning + h + i] << endl;
		if (A[beginning + i] > A[beginning + h + i]) {
			int temp = A[beginning + i];
			A[beginning + i] = A[beginning + h + i];
			A[beginning + h + i] = temp;
		}
	}
	Sort(A, beginning, beginning + h - 1);
	Sort(A, beginning + h, end);
}

void BitonicSort(int* A, const int beginning, const int end) {
	int len = end - beginning + 1;
	int h = len / 2;
	if (len > 2) {
		BitonicSort(A, beginning, beginning + h - 1);
		BitonicSort(A, beginning + h, end);
	}
	Merge(A, beginning, end);
	Sort(A, beginning, end);
}

void BitonicSort(int* A) {

}

void main() {
	clock_t s, e;
	s = clock();
	int A[16] = { 1,16,3,2,9,5,2,7,14, 15,25,4,21,19,23,10 };
	int* n = new int[16];
	memset(n, 0, 16*sizeof(int));
	memcpy(n, &A, sizeof(int)*16);
	BitonicSort(n, 0, 15);
	for (int i = 0; i < 16; i++) {
		cout << n[i] << " ";
	}
	cout << endl;
	e = clock();
	int d = (e - s) / 60;
	cout << "d: " << d << endl;
	system("pause");
}

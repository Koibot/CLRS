#include<iostream>
#include<vector>
using namespace std;

const int permutation = 5;

//void Permutation(vector<int*> &result, int* p = 0, int* rest = 0) {
//	for (int i = 0; i < (sizeof(rest) / sizeof(int)); i++) {
//		int np = sizeof(p) / sizeof(int);
//		int* new_rest[sizeof(rest) - 1];
//		memset(p, 0, 5 - i);
//		p[np] = rest[i];
//		int *r;
//		for (int k = 0; k < i; k++) {
//			if (rest[k] != i) {
//				*(r + k) = rest[k];
//			}
//		}
//	}
//}
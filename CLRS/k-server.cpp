#include<iostream>
#include<vector>
#include<deque>

using namespace std;

void ks_main() {
	const int k = 3;
	int client[5] = { 9,3,7,7,1 };
	int ***L;
	L = new int**[k];
	for (int a = 0; a < k; a++) {
		L[a] = new int*[5];
	}
	for (int a = 0; a < k; a++) {
		for (int b = 0; b < 5; b++) {
			L[a][b] = new int[2];
			L[a][b][0] = 0;
			L[a][b][1] = 0;
		}
	}
	for (int i = 0; i < 5; i++) {
		int l = 0;
		int r = 5;
		while (l < i) {
			L[0][i][0] += (i - l + 1)*client[l];
			l++;
		}
		while (r >= i+1) {
			L[0][i][1] += (r - i)*client[r - 1];
			r--;
		}
	}
	for (int i = 0; i < 5; i++) {
		
		cout << "L[" << i << "][0]: " << L[0][i][0] << endl;
		cout << "L[" << i << "][1]: " << L[0][i][1] << endl;
	}
	for (int i = 1; i < k; i++) {
		int **K;
		K = new int*[5];
		int m = 1;
		for (int j = 0; j < 5; j++) {
			K[j] = new int[2];
		}
		for (m; m < 5; m++) {
			int j = 0;
			for (j; j < m; j++) {
				K[j][0] = L[i - 1][j][0];
				cout << "K[" << j << "][0]: " << K[j][0] << endl;
			}
			for (j; j < 5; j++) {
				K[j][1] = L[i - 1][j+1][1];
				cout << "K[" << j << "][0]: " << K[j][0] << endl;
			}
		}
		
		*(L + i) = K;
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			for (int n = 0; n < 2; n++) {
				cout << "L[" << i << "]["<<j<<"][" << n << "]: " << L[i][j][n] << endl;
			}
		}
	}
	system("pause");
}


#include<iostream>
#include<math.h>
#include"time.h"
using namespace std;

void e1(int n) {
	int exe = 0;
	clock_t s, e;
	s = clock();
	int ol = 0;
	int j = 5;
	while (j < log2(n)) {
		int k = 5;
		while (k < n) {
			cout << "execute something here" << endl;
			k = pow(k, 1.3);
			cout << "k: " << k << endl;
			exe++;
		}
		j = j*1.3;
		cout << "j: " << j << endl;

	}
	cout << "execution times: " << exe << endl;
	e = clock();
	int d = (e - s) / 60;
	cout << "d: " << d << endl;
	system("pause");


}

void looptest() {
	int i = 0;
	int j = 0;
	int n = 36;
	for (j; j < n; j++) {
		cout << "what the hell is this" << endl;
		j = n;
	}
}



int TCmain() {
	int n = 1024*1024;
	//e1(n);
	looptest();
	system("pause");
}
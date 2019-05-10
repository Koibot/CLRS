#include<iostream>

using namespace std;

const int r = 31;



void EuroEfcy_main() {


	unsigned int CurrencyCount[r];
	memset(CurrencyCount, 0, sizeof(unsigned int)*r);
	for (int i = 1; i < r; i++) {
		CurrencyCount[i] = 9;
	}
	CurrencyCount[1] = 1;
	CurrencyCount[2] = 1;
	CurrencyCount[17] = 1;
	//CurrencyCount[39] = 1;
	//CurrencyCount[46] = 1;
	//CurrencyCount[50] = 1;
	for (int i = 0; i < r; i++) {
		cout << CurrencyCount[i] << " ";
	}
	cout << endl;
	unsigned int temp[r];
	memset(temp, 0, sizeof(unsigned int)*r);
	memcpy(temp, CurrencyCount, sizeof(unsigned int)*r);
	cout << endl;
	int exit = 0;
	while (1) {
		/*memset(ncc, 0, sizeof(int) * r);
		memcpy(ncc, CurrencyCount, sizeof(int) * r);*/
		for (int i = 1; i < r; i++) {
			if (CurrencyCount[i] == 9) {
				for (int j = 0; j < i ; j++) {
					if (CurrencyCount[j] != 9) {
						if (CurrencyCount[i - j] != 9) {
							//cout << "find CurrencyCount[" << j << "] != 100 and " << endl;
							//cout<< "CurrencyCount[" << i-j << "] != 100" << endl;
							if (temp[i] > CurrencyCount[i - j] + CurrencyCount[j]) {
								temp[i] = CurrencyCount[i - j] + CurrencyCount[j];
							}
							//cout << "update c[" << i << "] = " << temp[i] << endl;
						}
						else if ((i + j < r - 1) && CurrencyCount[i + j] != 9) {
							//cout << "find CurrencyCount[" << j << "] != 100 and " << endl;
							//cout << "CurrencyCount[" << i + j << "] != 100" << endl;
							if (temp[i] > CurrencyCount[i + j] + CurrencyCount[j]) {
								temp[i] = CurrencyCount[i + j] + CurrencyCount[j];
							}
							//cout << "update c[" << i << "] = " << temp[i] << endl;
						}
					}
				}//end for j
				for (int k = i; k < r; k++) {
					if (k + i >= r) {
						break;
					}
					if (CurrencyCount[k] != 9) {
						if (CurrencyCount[k - i] != 9) {
							//cout << "find CurrencyCount[" << k << "] != 100 and ";
							//cout << "CurrencyCount[" << k - i << "] != 100" << endl;
							if (temp[i] > CurrencyCount[k - i] + CurrencyCount[k]) {
								temp[i] = CurrencyCount[k - i] + CurrencyCount[k];
							}
							//cout << "update c[" << i << "] = " << temp[i] << endl;
							//cout << "i:" << i << ", k:" << k << ", c[" << i + k << "]:" << CurrencyCount[i] + CurrencyCount[k] << endl;
						}
						else if (CurrencyCount[k + i] != 9) {
							//cout << "find CurrencyCount[" << k << "] != 100 and ";
							//cout << "CurrencyCount[" << k + i << "] != 100" << endl;
							if (temp[i] > CurrencyCount[k + i] + CurrencyCount[k]) {
								temp[i] = CurrencyCount[k + i] + CurrencyCount[k];
							}
							//cout << "update c[" << i << "] = " << temp[i] << endl;
						}
					}//end for k
				}//end if (CurrencyCount[i] != 0)

			}
			else {
				exit++;
			}
		}
		if (exit == r - 1) {
			break;
		}
		else {
			exit = 0;
			memcpy(CurrencyCount, temp, sizeof(int)*r);
			/*for (int k = 0; k < r; k++) {
				cout << CurrencyCount[k] << " ";
			}
			cout << endl;*/
		}
	}

	int avg = 0;
	for (int m = 0; m < r; m++) {
		avg += CurrencyCount[m];
		cout << CurrencyCount[m] << " ";
	}
	cout << "avg: " << avg << endl;
	cout << endl;
	cout << sizeof(temp) + sizeof(CurrencyCount) << endl;
	system("pause");
}
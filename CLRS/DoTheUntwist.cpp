#include<iostream>
#include<sstream>

using namespace std;

char* GenerateConvertionList() {
	char* CList = new char[28];
	CList[0] = '_';
	CList[27] = '.';
	int s = (int)'a';
	for (int i = 1; i < 27; i++) {
		CList[i] = (char)(s + i - 1);
		cout << i << ": " << CList[i] << ", ";
	}
	return CList;
}

int char_to_num(char c) {
	
	int n = (int)c - (int)'a' + 1;
	cout << n << endl;
	return n;
}

int GetPlainCodePosition(int i, int k, int s) {
	return (k*i)%s;
}


void DoTheUntwist_main() {

	char* clist = GenerateConvertionList();

	char* CipherCode = "thqqxw.lui.qswer";

	int k = 5;

	int s = strlen(CipherCode);

	cout << "s: " << s << endl;

	char* PlainCode = new char(s * sizeof(char));

	for (int i = 0; i < s; i++) {
		//calculate PlainCode position
		int pi = (k*i) % s;
		signed int n;
		/* n = (p[(k*i)%s] - i)%28 = c[i] */
		if (CipherCode[i] == '_') {
			n = 0;
		}
		else if (CipherCode[i] == '.') {
			n = 27;
		}
		else {
			n = (int)(CipherCode[i] - 'a') + 1;/*c[i]*/
		}
		cout << "n: " << n << endl;

		/*-s < p[(k*i)%s] - i < 27*/
		if (n + i < 28) {
			PlainCode[pi] = clist[n+i];
			cout << "PlainCode[pi]= " << PlainCode[pi] << endl;
		}
		else {
			//PlainCode[pi] = (char)(n - 28 - 1 + (int)'a' - 1);
			PlainCode[pi] = clist[n + i - 28];
			cout << "PlainCode[pi] " << PlainCode[pi] << endl;
		}
	}
	for (int m = 0; m < s; m++) {
		cout << PlainCode[m] << " ";
	}
	cout << endl;

	system("pause");
}
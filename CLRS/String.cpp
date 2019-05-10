#include<iostream>
#include<string>
#include<iomanip>//setw()

using namespace std;

class String {
private:
	char* STR;
	int Length = 0;
	signed int* FailureFunction;

public:

	String(char* c, int l) {

		cout << "start constructor" << endl;

		cout << "sizeof(*c): " << sizeof(*c) << endl;

		this->Length = l;
		cout << "Length: " << this->Length << endl;
		this->STR = new char[l];
		memset(STR, 0, l*sizeof(char));
		memcpy(STR, c, l*sizeof(char));

		cout << "start calculating failure function" << endl;

		this->FailureFunction = new int[l];
		memset(FailureFunction, -1, sizeof(unsigned int)*l);
		int i = 0, j = 0;
		FailureFunction[i] = -1;
		for (int j = 1; j < l; j++) {
			cout << "i = " << i << endl;
			cout << "j = " << j << endl;
			if (this->STR[j] == this->STR[i]) {
				cout << "STR[j]: " << STR[j] << endl;
				cout << "STR[i]: " << STR[i] << endl;
				FailureFunction[j] = FailureFunction[ j - 1] + 1;
				i++;
			}
			else {
				cout << "STR[j]: " << STR[j] << endl;
				cout << "STR[i]: " << STR[i] << endl;
				i = 0;
				FailureFunction[j] = -1;
			}
		}

		cout << "the failure function is: " << endl;
		for (int k = 0; k < l; k++) {
			cout << FailureFunction[k] << " " << endl;
		}

		cout << "STR: " << STR << endl;

		cout << "finish constructor" << endl;

	}

	~String() {
		delete[] STR;
	}

	int Find(String* pat) {
		int i = 0;
		int j = 0;
		while ((*(pat->STR+j) != NULL) && (*(this->STR+i) != NULL)) {
			while (j < pat->Length) {
				if (*(pat->STR + j) == *(this->STR + i)) {
					i++;
					j++;
				}
				else {//when different character occurs
					if (j == 0) {//even the first character in the pattern did not match
						i++;
					}
					else {
						j = this->FailureFunction[j - 1] + 1;
					}

				}
			}//end of while (j < pat -> Length)
			return i - j;
		}
		return -1;
	}
};

void String_main() {
	int p_l = 8;
	char* p = new char[p_l];
	memset(p, ' ', sizeof(char) * p_l);
	int s_l = 20;
	char* s = new char[s_l];
	memset(s, ' ', sizeof(char)*s_l);

	s[0] = 'm';
	s[1] = 'o';
	s[2] = 'e';
	s[3] = 'y';
	s[4] = 'a';
	s[5] = 'm';
	s[6] = 'a';
	s[7] = 'y';
	s[8] = 'a';
	s[9] = 'm';
	s[10] = 'a';
	s[11] = 'y';
	s[12] = 'a';
	s[13] = 'm';
	s[14] = 'a';
	s[15] = 'y';
	s[16] = 'a';
	s[17] = 'm';
	s[18] = 'i';
	s[19] = 'm';

	p[0] = 'y';
	p[1] = 'a';
	p[2] = 'm';
	p[3] = 'a';
	p[4] = 'y';
	p[5] = 'a';
	p[6] = 'm';
	p[7] = 'i';
	String pat(p, p_l);
	String* pat_ptr = &pat;
	String str(s, s_l);
	int r = str.Find(pat_ptr);
	cout << "result: " << r << endl;
	system("pause");

}

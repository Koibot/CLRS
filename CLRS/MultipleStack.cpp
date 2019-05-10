#include<iostream>

using namespace std;



template<class DataType>
class MultipleStack {
private:
	DataType* StackArray;
	int NumberOfStacks;
	int LengthOfEachStack;
	int* Base;
	int* Top;

public:
	MultipleStack(const int& n, const int& m) {
		this->NumberOfStacks = n;
		this->LengthOfEachStack = m;
		StackArray = new DataType[m*n];
		this->Base = new int[n];
		for (int i = 0; i < n; i++) {
			Base[i] = i*m - 1;
		}
		this->Top = new int[n];
		for (int i = 0; i < n; i++) {
			Top[i] = i*m - 1;
		}

	}
	~MultipleStack() {
		delete[] StackArray;
		delete[] Base;
		delete[] Top;
		this->NumberOfStacks = 0;
		this->Base = 0;
		this->Top = 0;
		this->StackArray = 0;
		this->LengthOfEachStack = 0;
	}

	bool IsStackFull(const int& i) {
		if (Top[i] == Base[i + 1]) return true;
		return false;
	}

	bool ExtendStack(const int& i) {
		int n = this->NumberOfStacks;
		for (int j = i + 1; j < n; j++) {
			if (Top[j] < Base[j + 1]) {
				for (int k = Top[j]+1; k > Base[i+1]+1; k--) {
					StackArray[k] = StackArray[k - 1];
				}
				for (int k = i+1; k < j; k++) {
					Top[k]++;
					Base[k]++;
				}
				return true;
			}
		}
		for (int j = i - 1; j > 0; j--) {
			if (Top[j] < Base[j + 1]) {
				for (int k = Top[j]; k < Top[i] + 1; k++) {
					StackArray[k] = StackArray[k + 1];
				}
				for (int k = j; k < i + 1; k++) {
					Top[k]--;
					Base[k]--;
				}
				return true;
			}
		}
		return false;
	}

	void push(const int& i, const DataType& data) {
		if (Top[i] == Base[i + 1]) {
			if (!ExtendStack(i)) {
				return;
			}
		}
		Top[i]++;
		StackArray[Top[i]] = data;
	}
};

void multiplestack_main() {
	MultipleStack<int> testMS(4, 4);
	testMS.push(3, 3);
	system("pause");
}
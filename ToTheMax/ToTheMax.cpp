#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

const int buffersize = 256;

const int s = 4;

class number {
public:
	int x_;
	int y_;
	int data_;
	int local_max_;
	number(int x, int y, int data):x_(x), y_(y), data_(data), local_max_(data){}
	number():x_(0), y_(0), data_(0), local_max_(0){}
	number& operator=(const number& o) {
		this->x_ = o.x_;
		this->y_ = o.y_;
		this->data_ = o.data_;
		this->local_max_ = o.local_max_;
		return *this;
	}
};

void read_2d_array(number**& matrix) {
	//number** matrix;
	char buffer[buffersize];
	ifstream file("test_ttm_2d_array.txt");
	if (!file.is_open()) {
		cout << "file is not opened" << endl;
	}
	int k = 0;
	while (!file.eof()) {
		file.getline(buffer, buffersize);
		stringstream ss(buffer);
		int i = 0;
		while (ss >> i) {
			int x = floor(k / 4);
			int y = k % 4;
			number n(x, y, i);
			cout << "test" << endl;
			cout << "k: " << k << " ";
			cout << "x: " << x << " ";
			cout << "y: " << y << " ";
			cout << n.data_ << endl;
			matrix[x][y] = n;
			k++;
		}
	}

}

void main() {
	number** matrix = new number*[4];
	for (int i = 0; i < 4; i++) {
		number* row = new number[4];
		matrix[i] = row;
	}
	read_2d_array(matrix);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << matrix[i][j].data_ << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			number* cur = &matrix[i][j];
			int addrow = cur->data_;
			int addcol = cur->data_;
			number w;
			if (j != 0) {
				w = matrix[i][j - 1];
			}
			else {
				w = number(i, j, 0);
			}
			number n; 
			if (i != 0) {
				n = matrix[i - 1][j];
			}
			else {
				n = number(i, j, 0);
			}
			for (int k = w.x_; k < i; k++) {
				addcol += matrix[k][j].data_;
			}
			for (int k = n.y_; k < j; k++) {
				addrow += matrix[i][k].data_;
			}

			cout << "addrow + n.local_max_: " << addrow + n.local_max_ << endl;
			cout << "addcol + w.local_max_: " << addcol + n.local_max_ << endl;
			cout << "n.local_max_: " << n.local_max_ << endl;
			cout << "w.local_max_: " << w.local_max_ << endl;

			if (addrow + n.local_max_ > addcol + w.local_max_) {
				cout << "a" << endl;
				cur->local_max_ = addrow + n.local_max_;
				cur->x_ = n.x_;
				cur->y_ = n.y_;
			}
			else {
				cout << "b" << endl;
				cur->local_max_ = addcol + w.local_max_;
				cur->x_ = w.x_;
				cur->y_ = w.y_;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << matrix[i][j].local_max_ << " ";
		}
		cout << endl;
	}

	system("pause");
}
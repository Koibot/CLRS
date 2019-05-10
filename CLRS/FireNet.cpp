#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;

const int buffersize = 2048;

char** map;

int k = 0;

int max = 0;

void FNReadFile(string FilePath) {
	char buffer[buffersize];

	ifstream file(FilePath);

	if (!file.is_open()) {
		cout << "fail to open the file" << endl;
		return;
	}


	file.getline(buffer, buffersize);
	stringstream ssf(buffer);
	ssf >> k;

	map = new char*[k];
	for (int i = 0; i < k; i++) {
		map[i] = new char[k];
	}

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {

		}
	}

	int i = 0;

	while (!file.eof()) {
		file.getline(buffer, buffersize);
		stringstream ss(buffer);
		char p;
		int j = 0;
		while (ss >> p) {
			map[i][j++] = p;
		}
		i++;
	}

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}

	return;

}

bool is_valid(int x, int y) {
	if (map[x][y] == 'X'||map[x][y]=='O') {
		return false;
	}
	else {
		for (int i = x + 1; i < k; i++) {
			if (map[i][y] == 'O') {
				return false;
			}
			else if (map[i][y] == 'X') {
				break;
			}
		}//end of iy

		for (int i = x - 1; i >= 0; i--) {
			if (map[i][y] == 'O') {
				return false;
			}
			else if (map[i][y] == 'X') {
				break;
			}
		}//end of iy

		for (int j = y - 1; j < k; j++) {
			if (map[x][j] == 'O') {
				return false;
			}
			else if (map[x][j] == 'X') {
				break;
			}
		}//end of xj

		for (int j = y - 1; j >= 0; j--) {
			if (map[x][j] == 'O') {
				return false;
			}
			else if (map[x][j] == 'X') {
				break;
			}
		}//end of xj

	}//end of else
	return true;
}

//void ReadFile(const char* filepath) {
//	FILE *file = fopen(filepath, "r");
//	
//	int k;
//
//	fscanf(file, "%d", &k);
//	for (int i = 0; i < k; i++) {
//		fscanf(file, "%c%c");
//	}
//
//
//
//}

void place_a_tower(int s, int m, int n) {

	if (s == n*n) {
		if (m > max) {
			max = m;
		}
		return;
	}

	int x = s / n;
	int y = s%n;
	if (is_valid(x, y)) {
		map[x][y] = 'O';
		place_a_tower(s + 1, m + 1, n);

		cout << "=====================" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << map[i][j] << " ";
			}
			cout << endl;
		}
		cout << "=====================" << endl;

		map[x][y] = '.';
	}
	place_a_tower(s + 1, m, n);

}




void FireNet_main() {
	string fp = "data.txt";
	FNReadFile(fp);
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < 4; j++) {
			cout << is_valid(i, j); " ";
		}
		cout<<endl;
	}
	place_a_tower(0, 0, k);
	cout << "max: " << max << endl;
	system("pause");
}
#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<bitset>

const int buffersize = 2048;

using namespace std;

bool Can_Match(int EdgeA, int EdgeB) {
	bool r;
	if (EdgeA^EdgeB == 255) {
		r = true;
		cout << "matching edges found" << endl;
	}
	else {
		r = false;
	}
	return r;
}

void Cube(string FileName) {
	char buffer[buffersize];
	fstream file;
	file.open(FileName);
	if (!file.is_open()) {
		cout << "can't open file" << endl;
		return;
	}

	//read number of sinarios
	file.getline(buffer, buffersize);
	stringstream ssnum(buffer);
	int scenarios;
	ssnum >> scenarios;

	for (int sce = 0; sce < scenarios; sce++) {
		int Block_1[36];
		int Block_2[36];
		int Block_3[36];
		int Block_4[36];
		int Block_5[36];
		int Block_6[36];
		int* Blocks[6] = { Block_1, Block_2, Block_3, Block_4, Block_5, Block_6 };
		while (!file.eof()) {
			int blockspointer = 0;

			char c;
			int base = 0;
			int increment = 0;
			while (file.get(c)) {
				if (c == '!') {
					if (file.peek() == '/n') {
						blockspointer = 0;
						base += increment;
						increment = 0;
						continue;
					}
					else {
						blockspointer++;
						increment = 0;
						continue;
					}
				}
				else {
					Blocks[blockspointer][base+increment] = c;
					increment++;
				}
			}
		}
	}


}

void Cube_main() {

}

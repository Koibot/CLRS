#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

//#define _CRT_SECURE_NO_WARNINGS;

using namespace std;

const int buffersize = 2048;


void ReadFile(string Filename) {
	char buffer[buffersize];

	//initialize a ifstream instance
	ifstream File(Filename);
	if (!File.is_open()) {
		cout << "file is not opened" << endl;
	}

	vector<int> parameters;

	while (!File.eof()) {
		File.getline(buffer, 256);
		stringstream ss(buffer);
		int p;
		while (ss >> p) {
			parameters.push_back(p);
		}
		parameters.clear();
	}

}

void ReadFile() {
	char buffer[buffersize];

	/*when a fstream object is initialized, a filebuf is constructed, then filebuf::open is called with filename and mode as arguments*/
	fstream fs("test.txt", std::fstream::in | std::fstream::out);
	if (!fs.is_open()) {
		cout << "fail to open the file" << endl;
	}
}

//an oj style(?) file scanning function
//number of lines of data in the file 
//and number of data in one line should
//be announced ahead
void ReadFile(const char* filepath) {
	if (!filepath) {
		return;
	}

	FILE* fp = fopen(filepath, "r");
	int datalines;
	fscanf(fp, "data%d", &datalines);

	float a[3];//a random array to show you how to retrieve data from each line
	for (int i = 0; i < datalines; i++) {
		fscanf(fp, "%f%f%f", &a[0], &a[1], a[2]);
	}
	
	/*mayby do something else here*/
}



#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;

char*** ReadMaze(const string& f) {
	char buffer[256];
	char** Maze = new char*[9];
	memset(Maze, 0, sizeof(char*) * 9);
	for (int i = 0; i < 9; i++) {
		char* MazeRow = new char[9];
		memset(MazeRow, 0, sizeof(char) * 9);
		Maze[i] = MazeRow;
	}
	ifstream file;
	file.open(f);
	if (!file.is_open()) {
		cout << "fail to open file " << f << endl;
		return 0;
	}
	int RowCounter = 0;
	while (!file.eof()) {
		int Buffer[256];
		file.getline(buffer, 256);
		stringstream ss(buffer);
		char n;
		int c = 0;
		char temp[9];
		while (ss >> n) {
			temp[c] = n;
			c++;
		}
		memcpy(Maze[RowCounter], &temp, sizeof(char) * 9);
		RowCounter++;
		cout << endl;
	}
	return &Maze;
}

void Maze_main() {
	char*** Maze = ReadMaze("TestMaze.txt");
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << Maze[i][j] << " " ;
		}
		cout << endl;
	}
	system("pause");
}
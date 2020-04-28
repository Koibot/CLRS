// tetris.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#include <Windows.h>
#include <iostream>


using namespace std;

std::wstring elements[7];
int FieldHeight = 18;
int FieldWidth = 12;
unsigned char* pField = nullptr;

int ScreenHeight = 30;
int ScreenWidth = 80;

int Rotate(int i, int j, int c) {
	switch (c%4)
	{
	case 0: return (4 * i) + j;
	case 1: return 12 + i - (4 * j);
	case 2: return 15 - (4 * i) - j;
	case 3: return 3 + (4 * j) - i;
	}
	return 0;
}

int main()
{
	elements[0].append(L"..X.");
	elements[0].append(L"..X.");
	elements[0].append(L"..X.");
	elements[0].append(L"..X.");

	elements[1].append(L"..X.");
	elements[1].append(L".XX.");
	elements[1].append(L".X..");
	elements[1].append(L"....");

	elements[2].append(L"....");
	elements[2].append(L".XX.");
	elements[2].append(L".XX.");
	elements[2].append(L"....");

	elements[3].append(L".X..");
	elements[3].append(L".XX.");
	elements[3].append(L"..X.");
	elements[3].append(L"....");

	elements[4].append(L"XX..");
	elements[4].append(L".X..");
	elements[4].append(L".X..");
	elements[4].append(L"....");

	elements[5].append(L"....");
	elements[5].append(L".X..");
	elements[5].append(L".XX.");
	elements[5].append(L".X..");

	elements[6].append(L".XX.");
	elements[6].append(L".X..");
	elements[6].append(L".X..");
	elements[6].append(L"....");

	pField = new unsigned char[FieldHeight*FieldWidth];

	for (int j = 0; j < FieldWidth; j++) {
		for (int i = 0; i < FieldHeight; i++) {
			pField[FieldWidth*i + j] = (i == FieldHeight - 1 || j == 0 || j == FieldWidth - 1) ? 9 : 0;
		}
	}

	wchar_t *screen = new wchar_t[ScreenHeight*ScreenWidth];
	for (int i = 0; i < ScreenHeight*ScreenWidth; i++) {
		screen[i] = L'X';
	}
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	bool IsGameOver = false;

	

	while (!IsGameOver) {

		for (int j = 0; j < FieldWidth; j++) {
			for (int i = 0; i < FieldHeight; i++) {
				screen[(i + 2)*ScreenWidth + (j + 2)] = L" ABCDEFG=#"[pField[i*FieldWidth+j]];
			}
		}

		WriteConsoleOutputCharacter(hConsole, screen, ScreenWidth*ScreenHeight, { 0,0 }, &dwBytesWritten);

	}

	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file






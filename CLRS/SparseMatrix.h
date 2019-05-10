#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
using namespace std;

const int MaxTerms = 100;

#define min(a, b) (a>=b)?b:a

#define max(a, b) (a>=b)?a:b

class SparseMatrix;

class MatrixTerm {
private:
	int Row;
	int Col;
	int Data;

	friend ostream& operator<<(ostream& os, const MatrixTerm& t);

	friend class SparseMatrix;
public:
	MatrixTerm() {

	}

	MatrixTerm(int row, int col) {
		this->Row = row;
		this->Col = col;
	}

	MatrixTerm(int row, int col, int data) {
		this->Row = row;
		this->Col = col;
		this->Data = data;
	}

	void SetData(int data) {
		this->Data = data;
	}
	
	int GetData() {
		return this->Data;
	}

	int GetRow() {
		return Row;
	}

	int GetCol() {
		return Col;
	}
};

class SparseMatrix {
private:
	int Rows;
	int Cols;
	int Terms;
	MatrixTerm SMA[MaxTerms];

public:

	friend ostream& operator<<(ostream& os, const SparseMatrix& sm);

	SparseMatrix() {
		this->Rows = 100;
		this->Cols = 100;
		this->Terms = 0;
		cout << "a sparse matrix is created" << endl;
		cout << "default columns and rows number are both 100" << endl;
	}

	SparseMatrix(int rows, int cols) {
		this->Rows = rows;
		this->Cols = cols;
		this->Terms = 0;
		cout << "a sparse matrix is created" << endl;
	}

	int GetTerms() {
		return this->Terms;
	}

	int GetTerm(int i, int j) {
		for (int k = 0; k < Terms; k++) {
			if (SMA[k].Row == i) {
				if (SMA[k].Col == j) {
					return SMA[k].Data;
				}
				if (SMA[k].Col > j) {
					break;
				}
			}
			if (SMA[k].Row > i) {
				break;
			}
		}
		return -1;
	}

	int GetRows() {
		return this->Rows;
	}

	int GetCols() {
		return this->Cols;
	}

	void AddTerm(MatrixTerm &t) {
		//cout << "add term " << t << endl;
		if (Terms == 0) {
			SMA[0] = t;
			Terms++;
		}
		if (this->Terms+1 >= MaxTerms) {
			cout << "the number of term exceeds max amount of terms" << endl;
			return;
		}
		int TermRow = t.GetRow();
		int TermCol = t.GetCol();
		if (TermRow > Rows || TermCol > Cols) {
			cout << "the term exceed the range of matrix" << endl;
			return;
		}
		for (int c = 0; c < Terms; c++) {
			MatrixTerm curr = SMA[c];
			//cout << "curr.GetRow(): " << curr.GetRow() << endl;
			//cout << "curr.GetCol(): " << curr.GetCol() << endl;
			//cout << "TermRow: " << TermRow << endl;
			//cout << "TermCol: " << TermCol << endl;
			if ((curr.GetRow() >= TermRow) && (curr.GetCol() >= TermCol)) {
				if ((curr.GetRow() == TermRow) && (curr.GetCol() == TermCol)) {
					//cout << "position (" << TermRow << ", " << TermCol << ") is occupied" << endl;
					return;
				}
				else {
					for (int i = Terms; i < c; i--) {
						SMA[i] = SMA[i - 1];
					}
					SMA[c] = t;
					Terms++;
					break;
				}
			}
			else if (c == (Terms - 1)) {
				SMA[c + 1] = t;
				Terms++;
				break;
			}
		}//end for
		//cout << "new term added" << endl;
		//cout << endl;
	}

	void AddTerm(int row, int col, int data) {
		MatrixTerm* t = new MatrixTerm(row, col, data);
		AddTerm(*t);
	}

	void DeleteTerm(int row, int col) {
		for (int c = 0; c < Terms; c++) {
			MatrixTerm curr = SMA[c];
			if ((curr.GetRow() == row) && (curr.GetCol() == col)) {
				cout << "entry found, ready to delete" << endl;
				for (int i = c; i < Terms; i++) {
					SMA[i] = SMA[i + 1];
				}
				Terms--;
				break;
			}
			else if (c == (Terms - 1) || curr.GetRow() > row) {
				cout << "no such node in sparse matrix" << endl;
				break;
			}
		}
	}

	SparseMatrix FastTransPose() {
		cout << "starting fast transpose" << endl;
		int* ColCount = new int[Cols+1]();
		int* TransRowStart = new int[Cols+1]();
		for (int i = 0; i < this->Terms; i++) {
			ColCount[SMA[i].GetCol()]++;
		}
		for (int i = 0; i < this->Cols+1; i++) {
			cout << ColCount[i] << ", ";
		}
		cout << endl;
		for (int i = 1; i < this->Cols + 1; i++) {
			TransRowStart[i] = TransRowStart[i - 1] + ColCount[i - 1];
		}
		for (int i = 0; i < this->Cols + 1; i++) {
			cout << TransRowStart[i] << ", ";
		}
		cout << endl;
		SparseMatrix  Transposed(Cols, Rows);
		for (int i = 0; i < this->Terms; i++) {
			MatrixTerm t = this->SMA[i];
			cout << t << endl;
			int c = t.GetCol();
			MatrixTerm n(t.GetCol(), t.GetRow(), t.GetData());
			int l = TransRowStart[c];
			Transposed.SMA[l] = n;
			Transposed.Terms++;
			TransRowStart[c]++;
		}
		delete[]ColCount;
		delete[]TransRowStart;
		return Transposed;
	}

	SparseMatrix Multiply(SparseMatrix B) {
		cout << "start matrix multiplication" << endl;
		SparseMatrix C(this->Rows, B.Cols);
		if (B.Rows != this->Cols) {
			cout << "the size of the matrix doesn't match" << endl;
			return C;
		}

		SparseMatrix BX = B.FastTransPose();

		int LastRow = this->SMA[this->Terms-1].Row, LastCol = BX.SMA[B.Terms-1].Row;
		this->SMA[this->Terms].Row = LastRow + 1;
		BX.SMA[B.Terms].Row = LastCol + 1;
		/*int CurrentRow = this->SMA[0].Row, CurrentCol = BX.SMA[0].Row;*/
		int CurrentRow = 0, CurrentCol = 0;
		int InRow = 0, InCol = 0;
		/*in matrixA, row r, matrixB, row c*/
		/*cout <<
			"CurrentRow: " << CurrentRow << endl;
		cout <<
			"CurrentCol: " << CurrentCol << endl;
		cout <<
			"InRow: " << InRow << endl;
		cout <<
			"InCol: " << InCol << endl;
		cout <<
			"LastRow: " << LastRow << endl;
		cout <<
			"LastCol: " << LastCol << endl;*/
		int sumij;
		while (this->SMA[CurrentRow].Row <= LastRow) {
			while (BX.SMA[CurrentCol].Row <= LastCol) {
				sumij = 0;
				/*in same row and column, accumulate sum*/
				while ((this->SMA[InRow].Row == this->SMA[CurrentRow].Row) && (BX.SMA[InCol].Row == BX.SMA[CurrentCol].Row)) {
					cout <<
						"this->SMA[InRow].Row: " << this->SMA[InRow].Row << endl;
					cout <<
						"BX.SMA[InCol].Row: " << BX.SMA[InCol].Row << endl;
					cout <<
						"InRow: " << InRow << endl;
					cout <<
						"InCol: " << InCol << endl;
					signed int s = this->SMA[InRow].Col - BX.SMA[InCol].Col;
					cout << s << " = " << this->SMA[InRow].Col << " - " << BX.SMA[InCol].Col << endl;
					cout << "why s is not going into if statement?" << endl;
					if (s < 0.0) {
						cout << "InRow++" << endl;
						InRow++;
					}
					else if (s == 0.0) {
						sumij += this->SMA[InRow].Data * BX.SMA[InCol].Data;
						InRow++;
						InCol++;
					}
					else if (s > 0.0) {
						cout << "InCol++" << endl;
						InCol++;
					}
				}//end of while(in same row and column)
				cout << "sumij: " << sumij << endl;
				C.AddTerm(this->SMA[CurrentRow].Row, BX.SMA[CurrentCol].Row, sumij);
				 //matrix B: go to next column
				if (BX.SMA[InCol].Row != BX.SMA[CurrentCol].Row) {
					CurrentCol = InCol;
					InRow = CurrentRow;
				}
				if (this->SMA[InRow].Row != this->SMA[CurrentRow].Row) {
					InRow = CurrentRow;
					while (BX.SMA[InCol].Row == BX.SMA[CurrentCol].Row) {
						InCol++;
					}
					CurrentCol = InCol;
				}
				//matrix A: back to the begining of the same row
				InRow = CurrentRow;
				cout <<
					"	this->SMA[InRow].Row: " << this->SMA[InRow].Row << endl;
				cout <<
					"	BX.SMA[InCol].Row: " << BX.SMA[InCol].Row << endl;
				cout <<
					"	InRow: " << InRow << endl;
				cout <<
					"	InCol: " << InCol << endl;
			}//end of while(CurrentCol <= LastCol)
			//matrix A: go to next row, skip the rest of the same row
			while (this->SMA[CurrentRow].Row == this->SMA[InRow].Row) {
				InRow++;
			}
			CurrentRow = InRow;
			cout << "		change row" << endl;
			cout << "		CurrentRow: " << CurrentRow << endl;
			//matrix B: go back to the beginning of the matrix
			CurrentCol = 0;
			InCol = CurrentCol;
		}
		return C;
		
	}//end of Multiply function

	/*SparseMatrix Multiply(SparseMatrix B) {
		SparseMatrix C;
		if (B.Rows != this->Cols || B.Cols != this->Rows) {
			cout << "the size of the matrix doesn't match" << endl;
			return C;
		}
		B = B.FastTransPose();
		int* RowCounter = new int[this->Rows + 1]();
		for (int i = 0; i < this->Terms; i++) {
			MatrixTerm t = this->SMA[i];
			RowCounter[t.GetRow()]++;
		}
		int *RowStartingPoint = new int[this->Rows]();
		for (int i = 1; i < this->Rows + 1; i++) {
			RowStartingPoint[i] = RowStartingPoint[i - 1] + RowCounter[i - 1];
		}

		int p = 1;
		int start = RowStartingPoint[p];
		int next = RowStartingPoint[p + 1];
		while (p <= this->Rows) {
			for (int bl = 0; bl < B.Terms; bl++) {
				for (int onerow = start; onerow < next; onerow++) {
					if (this->SMA[onerow].Row == B.SMA[bl].Row) {
						//sum += this->SMA[onerow].GetData()*B.SMA[bl].GetData();
					}
					//MatrixTerm newterm(this->SMA[onerow].Row,
					//	)
					//C.AddTerm
				}
			}
		}


		return C;
	}*/

};

//ostream& operator<<(ostream& os, const MatrixTerm& t) {
//	os << "|(" << t.Row << ", " << t.Col << ")| " << t.Data;
//	return os;
//}
//
//ostream& operator<<(ostream& os, const SparseMatrix& sm) {
//	for (int i = 0; i < sm.Terms; i++) {
//		MatrixTerm t = sm.SMA[i];
//		os << t << ", ";
//	}
//	//os << sm.SMA[sm.Terms - 1] << ". ";
//	os << endl;
//	return os;
//}



//SparseMatrix ReadMatrixTermData(const string filename) {
//	char buffer[256];
//	SparseMatrix* sm = new SparseMatrix(10, 10);
//	ifstream MatrixTermData(filename);
//	if (!MatrixTermData.is_open()) {
//		cout << "fail to read the file" << endl;
//	}
//	
//	vector<int> parameters;
//	int p;
//	while (!MatrixTermData.eof()) {
//		MatrixTermData.getline(buffer, 256);
//		stringstream ss(buffer);
//		parameters.clear();
//		while (ss >> p) {
//			parameters.push_back(p);
//		}
//		sm->AddTerm(parameters[0], parameters[1], parameters[2]);
//
//	}
//	MatrixTermData.close();
//	return *sm;
//}

//void SparseMatrix_main() {
//
//	SparseMatrix smA = ReadMatrixTermData("MatrixA.txt");
//	SparseMatrix smB = ReadMatrixTermData("MatrixB2.txt");
//	SparseMatrix smC = smA.Multiply(smB);
//	cout << smC << endl;
//	
//	system("pause");
//} 

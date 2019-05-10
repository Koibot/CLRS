#include<iostream>
#include<queue>
#include"SparseMatrix.h"

using namespace std;

struct Bucket {
	int volumn;
	int current;
	int prev;
};

struct state {
	int AC;
	int BC;
};

const int OPnum = 6;

const int Target = 4;

const int AV = 5;

const int BV = 7;

int op[OPnum] = { 1,2,3,4,5,6 };
/*
1: empty a
2: empty b
3: a->b
4: b->a
5: fill a
6: fill b

*/


SparseMatrix status(81, 81);

queue<state> to_be_visit;




bool ExistSameState(int A_Current, int B_Current){
	int i = status.GetTerm(A_Current, B_Current);
	if (i == 1) {
		return true;
	}
	status.AddTerm(A_Current, B_Current, 1);
	return false;
}

void Lokum() {
	state s = to_be_visit.front();
	cout << "s.AC: " << s.AC << endl;
	cout << "s.BC: " << s.BC << endl;
	if (s.AC == Target || s.BC == Target) {
		cout << "solution found" << endl;
		return;
	}
	int temp_a = s.AC;
	int temp_b = s.BC;
	for (int r = 1; r <= 6; r++) {
		s.AC = temp_a;
		s.BC = temp_b;
		if (r == 1) {
			//cout << "try to empty A" << endl;
			if (s.AC != 0) {
				s.AC = 0;
				if (ExistSameState(s.AC, s.BC)) {
					continue;
				}
				state* ns = new state;
				ns->AC = s.AC;
				ns->BC = s.BC;
				to_be_visit.push(*ns);
			}
			/*else {
				cout << "try to empty A but A is already emptied" << endl;
			}*/
		}
		if (r == 2) {
			//cout << "try to empty B" << endl;
			if (s.BC != 0) {
				s.BC = 0;
				if (ExistSameState(s.AC, s.BC)) {
					continue;
				}
				state* ns = new state;
				ns->AC = s.AC;
				ns->BC = s.BC;
				to_be_visit.push(*ns);
			}
			/*else {
				cout << "try to empty B but B is already emptied" << endl;
			}*/
		}
		if (r == 3) {
			//cout << "try A->B" << endl;
			if ((s.BC<BV) && (s.AC != 0)) {
				//cout << "A->B" << endl;
				int Br = BV - s.BC;
				if (s.AC <= Br) {
					s.BC += s.AC;
					s.AC = 0;
				}
				else if (s.AC > Br) {
					s.BC = BV;
					s.AC -= Br;
				}
				if (ExistSameState(s.AC, s.BC)) {
					continue;
				}
				state* ns = new state;
				ns->AC = s.AC;
				ns->BC = s.BC;
				to_be_visit.push(*ns);
			}
			/*else {
				cout << "invalid operation for A->B" << endl;
			}*/
		}
		if (r == 4) {
			//cout << "try B->A" << endl;
			if ((AV != s.AC) && (s.BC != 0)) {
				//cout << "B->A" << endl;
				int Ar = AV - s.AC;
				if (s.BC <= Ar) {
					s.AC += s.BC;
					s.BC = 0;

				}
				else if (s.BC > Ar) {
					s.AC = AV;
					s.BC -= Ar;
				}//end of s.BC <= || > Ar
				if (ExistSameState(s.AC, s.BC)) {
					continue;
				}
				state* ns = new state;
				ns->AC = s.AC;
				ns->BC = s.BC;
				to_be_visit.push(*ns);
			}
			/*else {
				cout << "invalid operation for B->A" << endl;
			}*/
		}
		if (r == 5) {
			//cout << "fill A" << endl;
			if (s.AC < AV) {
				s.AC = AV;
				if (ExistSameState(s.AC, s.BC)) {
					continue;
				}
				//cout << "A is actually filled" << endl;
				state* ns = new state;
				ns->AC = s.AC;
				ns->BC = s.BC;
				to_be_visit.push(*ns);
			}
			//else {
			//	//cout << "invalid operation in filling A" << endl;
			//}
		}
		if (r == 6) {
			//cout << "fill B" << endl;
			if (s.BC < BV) {
				s.BC = BV;
				if (ExistSameState(s.AC, s.BC)) {
					continue;
				}
				//cout << "B is actually filled" << endl;
				state* ns = new state;
				ns->AC = s.AC;
				ns->BC = s.BC;
				to_be_visit.push(*ns);
			}
			//else {
			//	//cout << "s.BC: " << s.BC << endl;
			//	//cout << "BV: " << BV << endl;
			//	//cout << "invalid operation in filling B" << endl;
			//}
		}
	}
	to_be_visit.pop();
	Lokum();
}

void Jugs_main() {
	Bucket A;
	Bucket B;
	A.current = 0;
	A.prev = 0;
	B.prev = 0;
	B.current = 0;
	state s;
	s.AC = 0;
	s.BC = 0;
	to_be_visit.push(s);
	status.AddTerm(0, 0, 1);
	Lokum();
	system("pause");
}
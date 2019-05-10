#include<iostream>

using namespace std;

/*somehow feels like anagrams by stack */

template<class T>
class Railroad {
private:
	int ltop;
	int rtop;
	int vtop;
	T* RightRailroad;
	T* LeftRailroad;
	T* VerticalRailroad;
	int NumberOfCars;
public:
	Railroad(T* CarsArray, int cnum) {
		cout << "constructor" << endl;
		NumberOfCars = cnum;
		RightRailroad = new T[NumberOfCars];
		LeftRailroad = new T[NumberOfCars];
		VerticalRailroad = new T[NumberOfCars];
		RightRailroad = CarsArray;
		rtop = NumberOfCars - 1;//right railroad is full at the beginning
		ltop = -1;
		vtop = -1;
	}

	//~RailRoad();

	bool is_left_empty();
	bool is_vertical_empty();
	bool is_right_empty();

	void right_to_vertical();
	void vertical_to_right();
	void vertical_to_left();
	void left_to_vertical();

	void show_railroad(int i);
	/*
	i = 0: left
	i = 1: vertical
	i = 2: right
	*/

	void permutation() {
		cout << "left: ";
		show_railroad(0);
		cout << endl;
		/*cout << "vertical: ";
		show_railroad(1);
		cout << endl;
		cout << "right: ";
		show_railroad(2);
		cout << endl;*/
		//cout << ltop << ", " << vtop << ", " << rtop << endl;
		if (ltop == NumberOfCars - 1) {
			/*for (int i = 0; i <= ltop; i++) {
				cout << LeftRailroad[i] << " ";
			}
			cout << endl;*/
			return;
		}
		
		if (rtop > -1) {
			right_to_vertical();
			permutation();
			
			vertical_to_right();
		}
		if (vtop > -1) {
			vertical_to_left();
			permutation();
			
			left_to_vertical();
		}
		//left_to_vertical();
	}

};


template<class T>
bool Railroad<T>::is_left_empty() {
	if (ltop == -1) {
		return true;
	}
	return false;
}

template<class T>
bool Railroad<T>::is_right_empty() {
	if (rtop == -1) {
		return true;
	}
	return false;
}

template<class T>
bool Railroad<T>::is_vertical_empty() {
	if (vtop == -1) {
		return true;
	}
	return false;
}

template<class T>
void Railroad<T>::right_to_vertical() {
	if (is_right_empty()) {
		cout << "right railroad is empty" << endl;
		return;
	}
	T temp = RightRailroad[rtop];
	rtop--;
	vtop++;
	VerticalRailroad[vtop] = temp;
	return;
}

template<class T>
void Railroad<T>::left_to_vertical() {
	if (is_left_empty()) {
		cout << "left railroad is empty" << endl;
		return;
	}
	T temp = LeftRailroad[ltop];
	ltop--;
	vtop++;
	VerticalRailroad[vtop] = temp;
	return;
}

template<class T>
void Railroad<T>::vertical_to_left() {
	if (is_vertical_empty()) {
		cout << "no cars in vertical railroad" << endl;
		return;
	}
	T temp = VerticalRailroad[vtop];
	vtop--;
	ltop++;
	LeftRailroad[ltop] = temp;
	return;
}


template<class T>
void Railroad<T>::vertical_to_right() {
	if (is_vertical_empty()) {
		cout << "no cars in vertical railroad" << endl;
		return;
	}
	T temp = VerticalRailroad[vtop];
	vtop--;
	rtop++;
	RightRailroad[rtop] = temp;
	return;
}


template<class T>
void Railroad<T>::show_railroad(int i) {
	T* r = LeftRailroad;
	int end = 0;
	int s = 0;
	switch(i) {
		case 0: {
			r = LeftRailroad;
			end = ltop;
			for (int i = s; i <= end; i++) {
				cout << r[i] << " ";
			}
			cout << endl;
			break;
		}
		case 1: {
			r = VerticalRailroad;
			end = vtop;
			for (int i = s; i <= end; i++) {
				cout << r[i] << " ";
			}
			cout << endl;
			break;
		}
		case 2: {
			r = RightRailroad;
			s = rtop;
			end = NumberOfCars - 1;
			for (int i = 0; i <= rtop; i++) {
				cout << r[i] << ",";
			}
			cout << endl;
			break;
		}
	}
	return;
}

void rail_road_main() {
	char* cars = "left";
	int s = strlen(cars);

	char* n = new char[s];
	memcpy(n, cars, sizeof(char)*s);

	Railroad<char> testRailroad(n, s);
	testRailroad.show_railroad(2);
	//testRailroad.right_to_vertical();
	testRailroad.show_railroad(1);
	testRailroad.show_railroad(2);

	testRailroad.permutation();

	system("pause");
}
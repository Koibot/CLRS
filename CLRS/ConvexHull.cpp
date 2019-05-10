#include<iostream>
#include<vector>
#include<deque>
#include<cmath>
#include<iomanip>
#include<bitset>

using namespace std;


class Range {
public:
	int start;
	int end;
	int length;
	Range(int a, int b) {
		this->start = a;
		this->end = b;
	}

	int GetLength() {
		return end - start;
	}
	Range() {

	}
};

class Point {
public:
	float X = 0;
	float Y = 0;

	Point(float x, float y) {
		this->X = x;
		this->Y = y;
	}
	Point() {
		cout << "a point at (" << X << ", " << Y << ") is created" << endl;
	}

	friend ostream& operator<<(ostream& os, const Point& pt);

	void MoveTo(float x, float y) {
		if (this->X != x&&this->Y != y) {
			cout << "Point move from (" << X << ", " << Y << ") to (";
			this->X = x;
			this->Y = y;
			cout << X << ", " << Y << ")" << endl;
		}
		else {
			cout<<"There's already a point at this position, try another one " << endl;
		}
	}

};

class CircularLinkedList {
private:
	Point p;
	Point* Next;
	Point* Prev;
};


class Plane {
private:
	deque<Point> *PointSetPtr;
	deque<Point>::iterator it_left_most;
	deque<Point>::iterator it_right_most;
	unsigned int lr;
public:
	Plane() {
		
	}
	Plane(deque<Point> &ps) {
		PointSetPtr = &ps;
		it_left_most = ps.begin();
		it_right_most = ps.end() - 1;
	}


	Plane(Plane &p) {
		this->PointSetPtr = p.GetPointSet();
		it_left_most = p.GetBeginIterator();
		it_right_most = p.GetEndIterator();
	}

	void SetLeft() {
		this->lr = 0;
		Rotate();
	}

	void SetRight() {
		this->lr = 1;
		Rotate();
	}



	void Rotate() {//clockwise point set, start from the left-most element
		/*int left_end_val = 1000;
		int right_end_val = 0;*/
		/*for (deque<Point>::iterator it = PointSetPtr->begin(), end_iterator = PointSetPtr->end(); it < end_iterator; ++it) {
			int c = it->X;
			cout << "left_end val: " << left_end_val << endl;
			cout << "right_end_val: " << right_end_val << endl;
			cout << "c: " << c << endl;
			if (c > right_end_val) {
				cout << "update right_end point" << endl;
				cout << "*it: " << *it << endl;
				right_end_val = c;
				it_right_most = it;
			}
			if (c < left_end_val) {
				cout << "update left_end point" << endl;
				cout << "*it: " << *it << endl;
				left_end_val = c;
				it_left_most = it;
				cout << "*it_left_most: " << *it_left_most << endl;
			}
		}*/
		if (this->lr == 1) {
			cout << "lr == 1" << endl;
			int elements_in_between = std::distance(this->it_left_most, this->PointSetPtr->begin());
			cout << "elements in between: " << elements_in_between << endl;
			rotate(PointSetPtr->begin(), it_left_most, PointSetPtr->end());
			PointSetPtr->insert(PointSetPtr->end(), *PointSetPtr->begin());
			it_left_most = PointSetPtr->begin();
			it_right_most = PointSetPtr->end() - elements_in_between - 2;
			cout << "*it_right_most: " << *it_right_most << endl;
			cout << "*it_left_most: " << *it_left_most << endl;
		}
		else if (this->lr == 0) {
			cout << "lr == 0" << endl;
			int elements_in_between = std::distance(this->it_left_most, this->it_right_most);
			cout << "elements in between: " << elements_in_between << endl;
			rotate(PointSetPtr->begin(), it_right_most, PointSetPtr->end());
			PointSetPtr->insert(PointSetPtr->end(), *PointSetPtr->begin());
			it_right_most = PointSetPtr->begin();
			it_left_most = PointSetPtr->end() - elements_in_between - 1;
			cout << "*it_right_most: " << *it_right_most << endl;
			cout << "*it_left_most: " << *it_left_most << endl;
		}
		cout << "*it_right_most: " << *it_right_most << endl;
		cout << "*it_left_most: " << *it_left_most << endl;
		cout << "push back" << endl;/*
		cout << "*it_right_most: " << *it_right_most << endl;
		cout << "*it_left_most: " << *it_left_most << endl;*/
		cout << "elements after rearrangement" << endl;
		for (deque<Point>::iterator it = PointSetPtr->begin(), end_iterator = PointSetPtr->end(); it < end_iterator; ++it) {
			cout << *it << "  " << endl;
		}
		cout << "*it_right_most: " << *it_right_most << endl;
		cout << "*it_left_most: " << *it_left_most << endl;
		cout << endl;
	}
	
	deque<Point>* GetPointSet() {
		return PointSetPtr;
	}

	deque<Point>::iterator GetBeginIterator() {
		return it_right_most;
	}

	deque<Point>::iterator GetEndIterator() {
		return it_left_most;
	}

	friend float VSec(deque<Point>::iterator &i, deque<Point>::iterator &j, int x_val);


	void UpperTangent(Plane& r_plane, deque<Point>::iterator &upper_left_it, deque<Point>::iterator &upper_right_it) {
		cout << "in function UpperTangent" << endl;
		deque<Point>::iterator lit = this->it_right_most;
		cout << "*lit: " << *lit << endl;
		deque<Point>::iterator rit = r_plane.it_left_most;
		cout << "*rit: " << *rit << endl;
		if (r_plane.PointSetPtr->size() == 1 && this->PointSetPtr->size() == 1) {
			upper_left_it = this->PointSetPtr->begin();
			upper_right_it = r_plane.PointSetPtr->begin();
			return;
		}
		int mid = ((lit)->X + (rit)->X) / 2;
		bool active_plane = 1; //1 when right plane is active
		float mid_intsct = 0;
		float prev_mid_intsct = 0;
		bitset<2> status = 2;
		cout << "status: " << status << endl;
		while (status != 0 && lit < this->it_left_most && rit < r_plane.PointSetPtr->end()) {
			cout << "*lit: " << *lit << endl;
			cout << "*rit: " << *rit << endl;
			mid_intsct = VSec(lit, rit, mid);
			if (mid_intsct > prev_mid_intsct) {
				if (active_plane == 1) rit++;
				else lit--;
				prev_mid_intsct = mid_intsct;
				status = 2;
				cout << "status: " << status << endl;
			}
			else {
				if (active_plane == 1) active_plane = 0;
				else if (active_plane == 0) active_plane = 1;
				status = status >> 1;
				cout << "status: " << status << endl;
			}
		}
		upper_left_it = lit;
		upper_right_it = rit;
		cout << "*upper_left_it: " << *upper_left_it << endl;
		cout << "*upper_right_it: " << *upper_right_it << endl;
		cout << "now exit function UpperTangent" << endl;
		cout << endl;
	}

	void LowerTangent(Plane& r_plane, deque<Point>::iterator &lower_left_it, deque<Point>::iterator &lower_right_it) {
		/*cout << "in function LowerTangent" << endl;
		cout << "r_plane.GetPointSet()->size(): " << r_plane.GetPointSet()->size() << endl;
		cout << "*this->it_left_most: " << *(PointSetPtr->begin()) << endl;*/
		deque<Point>::iterator lit = this->it_right_most;
		//cout << "*lit: " << *lit << endl;
		deque<Point>::iterator rit = r_plane.PointSetPtr->end() - 1;
		//cout << "*rit: " << *rit << endl;
		int mid = ((lit)->X + (rit)->X) / 2;
		cout << "mid: " << mid << endl;
		bool active_plane = 1; //1 when right plane is active
		float mid_intsct = 0;
		float prev_mid_intsct = 1000;
		bitset<2> status = 2;
		int t = 2;
		while (status != 0 && t != 0 /*&& lit < this->PointSetPtr->end() && rit > r_plane.PointSetPtr->begin()*/) {
			/*if ((lit == this->PointSetPtr->end() - 1) || (rit == r_plane.PointSetPtr->begin() + 1)) {
				cout << "decrease t by one" << endl;
				t--;
			}*/
			mid_intsct = VSec(lit, rit, mid);
			cout << "prev_mid_intsct: " << prev_mid_intsct << endl;
			cout << "mid_intsct: " << mid_intsct << endl;
			cout << "active_plane: " << active_plane << endl;
			cout << "status: " << status << endl;
			if (mid_intsct <= prev_mid_intsct) {
				if (active_plane == 1) {
					prev_mid_intsct = mid_intsct;
					if (rit > r_plane.PointSetPtr->begin()+1) {
						rit--;
					}
					else {
						active_plane = 0;
						t--;
						cout << "decrease t by one" << endl;
					}
					cout << "111111111" << endl;
				}
				else if (active_plane == 0) {
					prev_mid_intsct = mid_intsct;
					if (lit < this->PointSetPtr->end()-1) {
						lit++;
					}
					else {
						active_plane = 1;
						t--;
						cout << "decrease t by one" << endl;
					}
					cout << "333333333333333" << endl;
				}
				status = 2;
			}
			else if (mid_intsct > prev_mid_intsct) {
				if (active_plane == 1) {
						active_plane = 0;
						rit++;
						cout << "right panel Pointer go backward" << endl;
					
				}
				else if (active_plane == 0) {
						active_plane = 1;
						lit--;
						cout << "left panel pointer go backward" << endl;
					
				}
				status = status >> 1;
			}
		}
		lower_left_it = lit;
		lower_right_it = rit;
		cout << "now exit function LowerTangent" << endl;
		cout << endl;
	}

	void operator+(Plane& r_plane) {
		deque<Point>::iterator upper_left_itr;
		deque<Point>::iterator upper_right_itr;
		deque<Point>::iterator lower_left_itr;
		deque<Point>::iterator lower_right_itr;
		LowerTangent(r_plane, lower_left_itr, lower_right_itr);
		UpperTangent(r_plane, upper_left_itr, upper_right_itr);
		cout << "*upper_left_itr" << *upper_left_itr << endl;
		cout << "*upper_right_itr" << *upper_right_itr << endl;
		cout << "*lower_left_itr" << *lower_left_itr << endl;
		cout << "*lower_right_itr" << *lower_right_itr << endl;
		this->PointSetPtr->erase(upper_left_itr, lower_left_itr);
		this->PointSetPtr->insert(upper_left_itr, upper_right_itr, lower_right_itr);
		this->it_right_most = r_plane.it_right_most;
	}

};

ostream& operator<<(ostream& os, const Point& pt) {
	os << "(" << pt.X << ", " << pt.Y << ")";
	return os;
}

class Line{
private:
	Point a;
	Point b;

public:
	float Length() {
		float d = sqrt(pow((this->b.Y - this->a.Y), 2) + pow((this->b.X - this->a.X), 2));
		return d;
	}

	float Slope() {
		float k = (this->b.Y - this->a.Y) / (this->b.X - this->a.X);
		return k;
	}

	Point GetStartPoint() {
		return a;
	}

	Point GetEndPoint() {
		return b;
	}
};


float VSec(deque<Point>::iterator &i, deque<Point>::iterator &j, int x_val) {//finding the intercept of  x = x_val and line Lij
	float y_itcpt;
	y_itcpt = ((j->Y - i->Y) / (j->X - i->X))*(x_val - i->X) + i->Y;
	//cout << "(j.Y - i.Y) / (j.X - i.X): " << (j.Y - i.Y) / (j.X - i.X) << endl;
	float test_y_itcpt = ((j->Y - i->Y) / (j->X - i->X))*(x_val - j->X) + j->Y;
	//cout << "just to test correctness of the formula: " << "y_itcpt= " << y_itcpt << " and test_y_itcpt = " << test_y_itcpt << endl;
	return y_itcpt;
}

float VSec(Point i, Point j, int x_val) {//finding the intercept of  x = x_val and line Lij
	float y_itcpt;
	y_itcpt = ((j.Y - i.Y) / (j.X - i.X))*(x_val - i.X) + i.Y;
	//cout << "(j.Y - i.Y) / (j.X - i.X): " << (j.Y - i.Y) / (j.X - i.X) << endl;
	float test_y_itcpt = ((j.Y - i.Y) / (j.X - i.X))*(x_val - j.X) + j.Y;
	//cout << "just to test correctness of the formula: " << "y_itcpt= " << y_itcpt << " and test_y_itcpt = " << test_y_itcpt << endl;
	return y_itcpt;
}

float Slope(deque<Point>::reverse_iterator &i, deque<Point>::iterator &j) {
	float k = (j->Y - i->Y) / (j->X - i->X);
	return k;
}







//void Merge(deque<Point> &PointSet, Range l, Range r, deque<Point>::iterator &right_it, deque<Point>::iterator &left_it) {
//	unsigned int status = 0x10;
//	Range left_endpoints = FindEndPoints(PointSet, l);
//	Range right_endpoints = FindEndPoints(PointSet, r);
//	//left_rit = PointSet.rbegin()+PointSet.size() - left_endpoints.end;
//	left_it = PointSet.begin() + left_endpoints.end;
//	right_it = PointSet.begin() + right_endpoints.start;
//	int mid = (left_it->X + right_it->Y)/2;
//	deque<Point>::iterator active_iterator = right_it;
//	float mid_intsct;
//	float prev_mid_intsct = 0;
//	while (status != 0x00) {
//		mid_intsct = V(left_it, right_it, mid);
//		if (mid_intsct > prev_mid_intsct) {
//			if(active_iterator == right_it) active_iterator++;
//			else active_iterator--;
//			prev_mid_intsct = mid_intsct;
//			status = 0x10;
//		}
//		else if (mid_intsct < prev_mid_intsct) {
//			if (active_iterator == right_it) active_iterator = left_it;
//			else if (active_iterator == left_it) active_iterator = right_it;
//			status>>1;
//		}
//	}
//
//}

//vector<Point> Merge(deque<Point> a, deque<Point> b, int x_val) {
//	Rearrange(a, x_val);
//	Rearrange(b, x_val);
//	float upper_tangent = 0;
//	float _upper_tangent = 0;
//	int i = 0;
//	int j = 0;
//	cout << "starting upper_tangent: right panel points rotate" << endl;
//	for (j; j <= b.size() - 1; j++) {
//		_upper_tangent = V(a[i], b[j], x_val);
//		cout << "i: " << i << ", j: " << j << endl;
//		cout << "_upper_tangent" << _upper_tangent << endl;
//		if (_upper_tangent >= upper_tangent) {
//			cout << "find a larger value" << endl;
//			cout << "update upper_tangent=" << _upper_tangent << endl;
//			upper_tangent = _upper_tangent;
//		}
//		else {
//			break;
//		}
//	}
//
//	cout << "found j: " << j << endl;
//
//	reverse(a.begin() + 1, a.end());
//	for (int x = 0; x <= 2; x++) {
//		cout << a[x] << endl;
//	}
//	i++;
//
//	cout << "starting upper_tangent: left panel points rotate" << endl;
//	cout << "upper_tangent" << upper_tangent << endl;
//	for (i; i <= a.size() - 1; i++) {
//		_upper_tangent = V(a[i], b[j], x_val);
//		cout << "i: " << i << ", j: " << j << endl;
//		cout << "_upper_tangent" << _upper_tangent << endl;
//		if (_upper_tangent >= upper_tangent) {
//			cout << "find a larger value" << endl;
//			cout << "update upper_tangent=" << _upper_tangent << endl;
//			upper_tangent = _upper_tangent;
//		}
//		else {
//			break;
//		}
//	}
//
//	cout << "found i: " << i << endl;
//
//	float lower_tangent = 10000;
//	float _lower_tangent = 1000;
//	int m = 0;
//	int n = 0;
//	reverse(a.begin() + 1, a.end());
//	reverse(b.begin() + 1, b.end());
//
//	cout << "starting lower_tangent: right panel points rotate" << endl;
//	for (n; n <= b.size() - 1; n++) {
//		_lower_tangent = V(a[m], b[n], x_val);
//		cout << "m: " << m << ", :n " << n << endl;
//		cout << "_lower_tangent" << _lower_tangent << endl;
//		if (_lower_tangent <= lower_tangent) {
//			cout << "find a lower value" << endl;
//			cout << "update lower_tangent=" << _lower_tangent << endl;
//			lower_tangent = _lower_tangent;
//		}
//		else {
//			break;
//		}
//	}
//	cout << "found n: " << n << endl;
//	m++;
//	_lower_tangent = lower_tangent;
//	cout << "start lower_tangent: left panel points rotate" << endl;
//	for (m; m <= a.size() - 1; m++) {
//		cout << "_lower_tangent" << _lower_tangent << endl;
//		_lower_tangent = V(a[m], b[n], x_val);
//		cout << "m: " << m << ", :n " << n << endl;
//		if (_lower_tangent <= lower_tangent) {
//			cout << "find a smaller value" << endl;
//			cout << "update lower_tangent=" << _lower_tangent << endl;
//			lower_tangent = _lower_tangent;
//		}
//		else {
//			break;
//		}
//	}
//
//	cout << "found m: " << m << endl;
//
//	reverse(b.begin() + 1, b.end());
//
//	vector<Point> merged;
//	while (j!=n) {
//		cout << "j: " << j << endl;
//		merged.push_back(b[j]);
//		j++;
//
//	}
//	while (i != m) {
//		merged.push_back(a[m]);
//		m--;
//	}
//	return merged;
//}

void cv_main() {
	
	cout << "starting main" << endl;
	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	float test = 4.00 / 3.00;
	cout << "test: " << test << endl;
	Point p0(1, 11);
	Point p1(6, 8);
	Point p2(3, 4);
	Point p3(9, 7);
	Point p4(10, 5);
	Point p5(12, 10);
	Point pt_arr_l[] = { p0, p2 };
	Point pt_arr_r[] = { p1, p3 };
	deque<Point> pt_vec_l(pt_arr_l, pt_arr_l + 2);
	deque<Point> pt_vec_r(pt_arr_r, pt_arr_r + 2);
	Plane LP(pt_vec_l);
	Plane RP(pt_vec_r);
	LP.SetLeft();
	RP.SetRight();
	LP + RP;
	cout << "zeeeeeeeeeeeeeeeee" << endl;
	Point p6(12, 11);
	Point p7(15, 7);
	Point p8(16, 23);
	Point p9(16, 16);
	Point p10(20, 28);
	Point p11(22, 15);
	Point p12(15, 19);
	Point p13(24, 13);
	Point p14(14, 8);
	Point pt_arr_t[] = {p10, p11, p13, p7, p6, p9 };
	deque<Point> pt_arr_test(pt_arr_t, pt_arr_t + 6);
	Plane TestPlane(pt_arr_test);
	system("pause");

}



#include<iostream>
#include<algorithm>
//#define min(a, b) (a >= b) ? b : a
//#define max(a, b) (a > b) ? a : b
using namespace std;

class MultiDimensionalArray {
private:
	float* Element_Array;
	int* UpperBound;
	int* LowerBound;
	int Dimension = 0;
	int ArraySize = 0;
	int NumberOfElements = 0;
public:
	MultiDimensionalArray(int* lowerbound, int* upperbound, int d ) {
		cout << "start constructor" << endl;
		this->UpperBound = upperbound;
		this->LowerBound = lowerbound;
		this->Dimension = d;
		this->ArraySize = 1;
		for (int i = 0; i < d; i++) {
			int r = upperbound[i] - lowerbound[i] + 1;
			NumberOfElements *= r;
		}
		cout << "ArraySize: " << ArraySize << endl;
		float* E = new float[ArraySize];
		memset(E, 0, ArraySize * sizeof(float));
		this->Element_Array = E;
		cout << "end constructor" << endl;
	}

	~MultiDimensionalArray() {
		delete[]  Element_Array;
		Element_Array = 0;
	}

	void TestData(float* testdata) {
		this->Element_Array = testdata;
		this->ArraySize = 120;
	}

	int GetDimension() {
		return Dimension;
	}

	int* GetUpperBoundArray() {
		return this->UpperBound;
	}

	int* GetLowerBoundArray() {
		return this->LowerBound;
	}

	float* GetElementsArray() {
		return this->Element_Array;
	}

	void ChangeRange(int dim, int lb_new, int ub_new) {
		cout << "start processing the range changing in dimension "  << dim << endl;
		int u = this->UpperBound[dim];
		int l = this->LowerBound[dim];
		cout << "u original: " << u << endl;
		cout << "l original: " << l << endl;
		int range = u - l + 1;
		cout << "original range: " << range << endl;
		int range_new = ub_new - lb_new + 1;
		cout << "new range: " << range_new << endl;
		//calculate number of elements in this dimension
		int elems_in_dim = 1;
		for (int i = dim; i < this->Dimension; i++) {
			int r = u - l + 1;
			elems_in_dim *= r;
		}
		cout << "number of elements in dimension " << dim << ", elems_in_dim, is " << elems_in_dim << endl;

		//create a new array
		int step = this->ArraySize / elems_in_dim;
		signed int add_elems = step*(range_new - range);//could be a negative number
		signed int new_array_size = add_elems + this->ArraySize;
		float* new_element_array = new float[new_array_size];
		memset(new_element_array, 0, (new_array_size) * sizeof(float));
		cout << "new array is created, size " << sizeof(new_element_array) << endl;


		//add new dimension to the begining of d
		int step_length;
		int step_length_new;
		int copy_length = elems_in_dim + min(0, ub_new - u) + min(0, lb_new - l);
		cout << "min(0, ub_new - u): " << min(0, ub_new - u) << endl;
		step_length = elems_in_dim;
		step_length_new = new_array_size / step ;
		cout << "step_length: " << step_length << endl;
		cout << "step_length_new: " << step_length_new << endl;
		cout << "copy_length: " << copy_length << endl;
		cout << "step: " << step << endl;
		for (int i = 0; i < step; i++) {
			/*copy starting at new_element_array[p_new + ub_new - u]
			because the first (ub_new - u) elements are new and are set 0*/
			int pt = i*step_length - min(0, ub_new - u);
			cout << "pt: " << pt << endl;
			int p_b = i*(step_length_new);
			cout << "p_b: " << p_b << endl;
			for (int j = 0; j < copy_length; j++) {
				new_element_array[p_b + j] = this->Element_Array[pt + j];
			}// end of copying data to new array


		}//end of adding dimension

		for (int i = 0; i < ArraySize; i++) {
			cout << Element_Array[i] << ", " << new_element_array[i] << endl;
		}

		//delete[] Element_Array;
		this->Element_Array = new_element_array;
		this->UpperBound[dim] = ub_new;
		this->LowerBound[dim] = lb_new;
		this->ArraySize = new_array_size;

	}
};

void MDArray_main() {
	int d = 5;
	int* test_ub = new int[d];
	memset(test_ub, 0, d * sizeof(int));
	int* test_lb = new int[d];
	memset(test_lb, 0, d * sizeof(int));
	test_ub[0] = 5;
	test_ub[1] = 4;
	test_ub[2] = 2;
	test_ub[3] = 4;
	test_ub[4] = 6;
	test_lb[0] = 4;
	test_lb[1] = 2;
	test_lb[2] = 1;
	test_lb[3] = 3;
	test_lb[4] = 2;

	float testdata[120];
	for (int i = 0; i < 120; i++) {
		testdata[i] = rand()%10;
	}

	MultiDimensionalArray mda(test_lb, test_ub, d);
	cout << "test_ub: " << test_ub << endl;
	cout << "test_lb: " << test_lb << endl;
	cout << "UpperBound: " << mda.GetUpperBoundArray() << endl;
	cout << "LowerBound" << mda.GetLowerBoundArray() << endl;
	cout << "elements array address: " << mda.GetElementsArray() << endl;
	float* tdpointer = testdata;
	mda.TestData(tdpointer);
	mda.ChangeRange(2, 1, 3);
	system("pause");

}
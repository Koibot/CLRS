#include<iostream>

typedef struct DNAString{
	char* dna_string;
	int sortedness;
	DNAString(char* ds, int s) :dna_string(ds), sortedness(s) {}
	DNAString operator= (DNAString* d) {
		dna_string = d->dna_string;
		sortedness = d->sortedness;
	}
}DNAString;


int main() {
	int case_number = 0;
	int array_length = 0;
	std::cin >> array_length >> case_number;
	DNAString** sorted_string = new DNAString*[case_number];
	for (int c = 0; c < case_number; c++) {
		//possible characters are A, C, G, T
		int A_count = 0;
		int C_count = 0;
		int G_count = 0;
		int T_count = 0;
		int inverse = 0;
		char* arr = new char[array_length];
		std::cin >> arr;

		//calculate inverse, aka sortedness
		for (int i = array_length - 1; i >= 0; i--) {
			if (arr[i] == 'A') {
				A_count++;
			}
			else if (arr[i] =='C') {
				C_count++;
				inverse += A_count;
			}
			else if (arr[i] == 'G') {
				G_count++;
				inverse += A_count + C_count;
			}
			else if (arr[i] == 'T') {
				T_count++;
				inverse += A_count + C_count + G_count;
			}
		}//end sortedness calculation
		
		
		//insertion sort dna_string
		for (int i = 0; i <= c; i++) {
			if (c == 0) {
				sorted_string[0] = new DNAString(arr, inverse);
				break;
			}
			else if (i == c) {
				sorted_string[i] = new DNAString(arr, inverse);
				break;
			}
			else if (sorted_string[i]->sortedness <= inverse) {
				continue;
			}
			else if (sorted_string[i]->sortedness > inverse) {
				for (int r = c; r >= i; r--) {
					sorted_string[r+1] = sorted_string[r];
				}//end for
				sorted_string[i] = new DNAString(arr, inverse);
				break;
			}

		}//end insertion sort


	}
	for (int i = 0; i < case_number; i++) {
		std::cout << sorted_string[i]->dna_string << std::endl;
	}

	return 0;
}



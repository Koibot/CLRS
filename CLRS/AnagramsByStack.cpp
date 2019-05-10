#include<iostream>
#include<vector>

using namespace std;

void CauseIamLookingForAnAnswer(vector<char> stack, vector<char> output, char* s, char* dest, int l, int pstr) {
	/*for (int i = 0; i < strlen(output); i++) {
		if (output[i] != s[i]) {
			cout << "branch abandoned" << endl;
			return;
		}
	}*/

	cout << "stack, size " << stack.size() << endl;
	for (int i = 0; i <stack.size(); i++) {
		cout << stack[i] <<" ";
	}
	cout << endl;
	cout << "output. size " << output.size() << endl;
	for (int i = 0; i < output.size(); i++) {
		cout << output[i] << " ";
	}
	cout << endl;
	cout << "dest: ";
	for (int i = 0; i < output.size(); i++) {
		cout << dest[i] << " ";
	}
	cout << endl;

	if (!output.empty()) {
		if (output.back() != dest[output.size() - 1]) {
			cout << "abandon invalid branch" << endl;
			return;
		}
	}


	if (output.size() == l) {
		cout << "matched" << endl;
		return;
	}

	if (((stack.empty()) && (pstr != 0))) {
		cout << "end of the path, turn back" << endl;
		return;
	}


	if (stack.size() < l && pstr != l) {//push
		cout << "i " << endl;
		stack.push_back(s[pstr]);
		pstr++;
		CauseIamLookingForAnAnswer(stack, output, s, dest, l, pstr);
		//stack[ps] = '0';
		stack.pop_back();
		pstr--;

	}
	if (!stack.empty()) {//pop
		cout << "o " << endl;
		output.push_back(stack.back());
		char temp = stack.back();
		//cout << "stack[ps-1]: " << stack[ps - 1] << endl;
		//stack[ps - 1] = '0';
		stack.pop_back();
		//po++;
		//ps--;
		CauseIamLookingForAnAnswer(stack, output, s, dest, l, pstr);
		stack.push_back(temp);
		output.pop_back();
		/*po--;
		ps++;
		stack[ps - 1] = output[po];
		output[po] = '0';*/
	}
	cout << "ever been here?" << endl;
}

void anagram_main() {
	char* s = "cata";
	char* dest = "atac";
	int clen = strlen(s);
	vector<char> stack;
	vector<char> output;
	CauseIamLookingForAnAnswer(stack, output, s, dest, clen, 0);
	system("pause");
}
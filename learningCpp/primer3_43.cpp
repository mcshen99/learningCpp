#include <iostream>

using namespace std;

int main() {
	int ia[3][4] = { { 0, 1, 2, 3 }, {4, 5, 6, 7}, {8, 9, 10, 11} };

	//range
	for (int (&row)[4] : ia) {
		for (int &col: row) {
			cout << col << " ";
		}
	}

	//subscript
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 4; ++j) {
			cout << ia[i][j] << " ";
		}
	}

	//pointer
	using int_array = int[4];
	typedef int int_array[4];
	for (int_array *p = ia; p != ia + 3; ++p) {
		for (int *q = *p; q != *p + 4; ++q) {
			cout << *q << " ";
		}
	}

	return 0;
}
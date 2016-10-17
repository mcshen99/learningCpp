#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//makes a vector u containing 100 ten times and copies them to a new vector v.
int main() {
	vector<int> u(10, 100);
	for (vector<int>::const_iterator iter = u.begin(); iter != u.end(); ++iter) {
		cout << *iter << " ";
	}
	cout << endl;

	vector<int> v;	
	copy(u.begin(), u.end(), v.begin());

	for (vector<int>::const_iterator iter = v.begin(); iter != v.end(); ++iter) {
		cout << *iter << " ";
	}
	cout << endl;

	return 0;
}


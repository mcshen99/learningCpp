#include <iostream>
#include <numeric>
#include <vector>
#include <string>

using namespace std;

int main() {
	string x;
	vector<string> v;
	while (cin >> x) {
		v.push_back(x);
	}

	//runtime: O(n)
	string ans = accumulate(v.begin(), v.end(), string(""));
	cout << ans << endl;
}
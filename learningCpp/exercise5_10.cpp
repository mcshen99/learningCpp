#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isPal(string);

int main() {
	string x;
	vector<string> palindromes;
	vector<string> longest;
	string::size_type maxlen = 0;
	while (cin >> x) {
		if (isPal(x)) {
			palindromes.push_back(x);
			if (x.size() > maxlen) {
				maxlen = x.size();
				longest.clear();
				longest.push_back(x);
			} else if (x.size() == maxlen) {
				longest.push_back(x);
			}
		}
	}	

	cout << "maxlen: " << maxlen << endl;
	for (vector<string>::const_iterator it = longest.begin(); it != longest.end(); ++it) {
		cout << *it << endl;
	}

	return 0;
}

bool isPal(string s) {
	string newS;
	for (string::const_iterator it = s.end() - 1; it != s.begin() - 1; --it) {
		newS += *it;
	}

	return newS == s;
}
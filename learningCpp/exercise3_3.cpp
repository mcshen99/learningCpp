#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
string intToString(int x);

int main() {
	cout << "Please enter total number of words: ";
	int n;
	cin >> n;
	cout << "Please enter words: ";
	string x;
	vector<string> words;
	vector<int> freq;
	for (int i = 0; i < n; ++i) {
		cin >> x;
		words.push_back(x);
	}
	sort(words.begin(), words.end());

	vector<string> finalWords;
	string last = "";
	int count = 0;
	for (string word : words) {
		if (last == word) {
			++count;
		} else {
			finalWords.push_back(last + " " + intToString(count));
			count = 1;
			last = word;
		}
	}
	finalWords.push_back(last + " " + intToString(count));

	for (string s : finalWords) {
		cout << s << endl;
	}

	return 0;
}

string intToString(int x) {
	string ans = "";
	while (x > 0) {
		ans += "0123456789"[x % 10];
		x /= 10;
	}
	reverse(ans.begin(), ans.end());

	return ans;
}
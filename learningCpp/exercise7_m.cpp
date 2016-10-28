#include <iostream> 
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <queue>
#include <random>
#include <time.h>

using namespace std;

string getLastK(deque<char> last, int k);

int main() {
	string str;
	cout << "Enter name of existing text file: ";
	getline(cin, str);
	ifstream is(str);

	cout << "Enter n: ";
	getline(cin, str);
	size_t n = stoi(str);

	map<string, map<char, int>> stringMap;

	deque<char> last;
	char c;
	while (is.get(c)) {
		for (size_t i = 0; i <= n; i++) {
			if (last.size() >= i) {
				string key = getLastK(last, i);
				++stringMap[key][c];
			}
		}

		last.push_back(c);
		if (last.size() > n) {
			last.pop_front();
		}
	}

	cout << "Enter length: ";
	string lengthStr;
	getline(cin, lengthStr);
	int length = stoi(lengthStr);
	string text;
	cout << "Enter text: ";
	getline(cin, text);

	default_random_engine generator(clock());
	for (int count = 0; count < length; count++) {
		auto textLength = text.size();
		auto& currKey = stringMap[""];
		for (int i = min(n, textLength); i >= 0; --i) {
			string s = text.substr(textLength - i);
			if (stringMap.find(s) != stringMap.end()) {
				currKey = stringMap[s];
				break;
			}
		}

		vector<int> d;
		for (auto& ent : currKey) {
			d.push_back(ent.second);
		}

		discrete_distribution<int> distribution(d.begin(), d.end());
		int pos = distribution(generator);
		auto it = currKey.begin();
		for (int i = 0; i < pos; i++) {
			++it;
		}
		text += it->first;
	}

	cout << "'" << text << "'";

	return 0;
}

string getLastK(deque<char> last, int k) {
	string str;
	for (auto it = last.cend() - k; it != last.cend(); ++it) {
		str += *it;
	}

	return str;
}
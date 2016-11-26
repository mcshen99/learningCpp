#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

string original;
map<string, long long> lookup;

long long rev(string& s) {
	if (lookup.find(s) != lookup.end()) {
		return lookup[s];
	}
	if (s.size() <= 2) {
		return 1;
	}

	long long sum = 1;
	for (size_t i = s.size() - 1; i >= 0; --i) {
		string sub = s.substr(0, i);
		string cut = s.substr(i, s.size() - i);
		if (sub.size() <= cut.size()) {
			break;
		}

		string found1 = sub.substr(0, cut.size());
		string found2 = sub.substr(sub.size() - cut.size(), cut.size());
		//cout << sub << " " << cut << " " << found1 << " " << found2 << endl;
		if (found1 == cut) {
			sum += rev(sub);
		}
		if (found2 == cut) {
			sum += rev(sub);
		}
	}

	for (size_t i = 1; i < s.size(); ++i) {
		string sub = s.substr(i, s.size() - i);
		string cut = s.substr(0, i);
		if (sub.size() <= cut.size()) {
			break;
		}

		string found1 = sub.substr(0, cut.size());
		string found2 = sub.substr(sub.size() - cut.size(), cut.size());
		//cout << sub << " " << cut << " " << found1 << " " << found2 << endl;
		if (found1 == cut) {
			sum += rev(sub);
		}
		if (found2 == cut) {
			sum += rev(sub);
		}
	}

	sum %= 2014;
	lookup[s] = sum;
	return sum;
}

int main() {
	ifstream f("scode.in");
	ofstream out("scode.out");
	
	f >> original;
	out << (rev(original) - 1) % 2014 << endl;
	/*for (auto& entry : lookup) {
		cout << entry.first << " " << entry.second << endl;
	}*/

	return 0;
}
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using namespace std;

int main() {
	ifstream f("cownomics.in");
	ofstream out("cownomics.out");
	int N, M;
	f >> N >> M;
	
	vector<string> spotty, plain;
	for (int i = 0; i < N; ++i) {
		string x;
		f >> x;
		spotty.push_back(x);
	}
	for (int i = 0; i < N; ++i) {
		string x;
		f >> x;
		plain.push_back(x);
	}

	for (int i = 1; i <= M; ++i) {
		bool works = true;
		for (int j = 0; j < M - i + 1; ++j) {
			vector<string> iList;
			for (int k = 0; k < N; ++k) {
				iList.push_back(plain[k].substr(j, i));
			}
			works = true;
			for (int k = 0; k < N; ++k) {
				if (find(iList.begin(), iList.end(), spotty[k].substr(j, i)) != iList.end()) {
					works = false;
					break;
				}
			}

			if (works) {
				break;
			}
		}

		if (works) {
			out << i << endl;
			break;
		}
	}

	return 0;
}

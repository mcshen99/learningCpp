#include <fstream>
#include <string>
#include <vector>

using namespace std;
bool closeVec(int N, vector<int> vec1, vector<int> vec2);

int main() {
	ifstream f("combo.in");
	ofstream out("combo.out");

	int N;
	f >> N;
	
	int x;
	vector<int> farmer;
	for (int i = 0; i < 3; ++i) {
		f >> x;
		farmer.push_back(x);
	}
	vector<int> master;
	for (int i = 0; i < 3; ++i) {
		f >> x;
		master.push_back(x);
	}
	
	int count = 0;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			for (int k = 1; k <= N; ++k) {
				vector<int> test;
				test.push_back(i);
				test.push_back(j);
				test.push_back(k);
				if (closeVec(N, test, farmer) || closeVec(N, test, master)) {
					++count;
				}
			}
		}
	}

	out << count << endl;

	return 0;
}

bool closeInt(int N, int n1, int n2) {
	return abs(n1 - n2) <= 2 || abs(n1 - n2) >= N - 2;
}

bool closeVec(int N, vector<int> vec1, vector<int> vec2) {
	for (int i = 0; i < 3; ++i) {
		if (!closeInt(N, vec1[i], vec2[i])) {
			return false;
		}
	}

	return true;
}
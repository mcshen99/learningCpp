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
				if (closeVec(N, test, farmer) == true || closeVec(N, test, master) == true) {
					++count;
				}
			}
		}
	}

	out << count << endl;

	return 0;
}

bool closeInt(int N, int n1, int n2) {
	if (n1 - n2 <= 2 && n1 - n2 >= -2) {
		return true;
	} else if (n1 - n2 >= N - 2 || n2 - n1 >= N - 2) {
		return true;
	} else {
		return false;
	}
}

bool closeVec(int N, vector<int> vec1, vector<int> vec2) {
	for (int i = 0; i < 3; ++i) {
		if (!closeInt(N, vec1[i], vec2[i])) {
			return false;
		}
	}

	return true;
}
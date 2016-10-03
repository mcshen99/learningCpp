#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int X, Y, Z;

int main() {
	ifstream f("milktemp.in");
	ofstream out("milktemp.out");
	
	int N;
	f >> N >> X >> Y >> Z;

	vector<int> A, B;
	for (int i = 0; i < N; ++i) {
		int a;
		int b;
		f >> a >> b;
		A.push_back(a);
		B.push_back(b);
	}
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());
	A.push_back(1000000001);
	B.push_back(1000000001);

	int max = N*X;
	int i = 0;
	int j = 0;
	int score = max;
	while (i < N && j < N) {
		if (A[i] > B[j]) {
			score += Z - Y;
			++j;
		} else {
			score += Y - X;
			++i;
		}
		if (max < score) {
			max = score;
		}
	}

	out << max << endl;

	return 0;
}
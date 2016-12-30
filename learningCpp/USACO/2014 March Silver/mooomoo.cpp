#include <fstream>
#include <iostream>

using namespace std;

const int maxN = 100;
const int maxB = 20;
const int maxV = 100001;
int N, B;
int breeds[maxB];
int inFields[maxN];
int fields[maxN];
int dp[maxV];

int main() {
	ifstream f("mooomoo.in");
	ofstream out("mooomoo.out");

	f >> N >> B;

	for (int i = 0; i < B; ++i) {
		f >> breeds[i];
	}
	for (int i = 0; i < N; ++i) {
		f >> inFields[i];
	}
	fields[0] = inFields[0];
	for (int i = 1; i < N; ++i) {
		if (inFields[i - 1] != 0) {
			fields[i] = inFields[i] - (inFields[i - 1] - 1);
		} else {
			fields[i] = inFields[i];
		}
	}

	for (int i = 0; i < maxV; ++i) {
		dp[i] = maxV + 1;
	}
	dp[0] = 0;
	for (int i = 0; i < B; ++i) {
		dp[breeds[i]] = 1;
	}
	for (int i = 0; i < maxV; ++i) {
		int minCows = dp[i];
		for (int j = 0; j < B; ++j) {
			int k = i - breeds[j];
			if (k >= 0) {
				if (dp[k] + 1 < minCows) {
					minCows = dp[k] + 1;
				}
			}
		}

		dp[i] = minCows;
	}

	int sum = 0;
	for (int i = 0; i < N; ++i) {
		if (dp[fields[i]] > maxV) {
			sum = -1;
			break;
		}
		sum += dp[fields[i]];
	}
	out << sum;

	return 0;
}
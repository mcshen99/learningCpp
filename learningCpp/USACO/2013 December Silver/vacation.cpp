#include <fstream>
#include <vector>

using namespace std;

int main() {
	ifstream f("vacation.in");
	ofstream out("vacation.out");
	const int largeNumber = 1000 * 1000000;

	int N, M, K, Q;
	f >> N >> M >> K >> Q;

	int shortest[205][205];
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (i != j) {
				shortest[i][j] = largeNumber;
			} else {
				shortest[i][j] = 0;
			}
		}
	}

	for (int i = 0; i < M; ++i) {
		int u, v, d;
		f >> u >> v >> d;
		shortest[u - 1][v - 1] = d;
	}

	for (int x = 0; x < N; ++x) {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				int a = shortest[i][x], b = shortest[x][j];
				if (a + b < shortest[i][j]) {
					shortest[i][j] = a + b;
				}
			}
		}
	}

	int validTrips = 0;
	long long cost = 0;
	for (int i = 0; i < Q; ++i) {
		int a, b;
		f >> a >> b;
		int min = largeNumber;
		for (int j = 0; j < K; ++j) {
			int d1 = shortest[a - 1][j], d2 = shortest[j][b - 1];
			if (d1 + d2 < min) {
				min = d1 + d2;
			}
		}
		if (min != largeNumber) {
			validTrips++;
			cost += min;
		}
	}

	out << validTrips << endl;
	out << cost << endl;

	return 0;
}
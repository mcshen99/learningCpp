#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int maxN = 50000;
int N;

int main() {
	ifstream f("circlecross.in");
	ofstream out("circlecross.out");

	f >> N;
	bool visited[maxN];
	pair<int, int> indices[maxN];
	for (int i = 0; i < 2 * N; ++i) {
		int index;
		f >> index;
		if (!visited[index - 1]) {
			indices[index - 1].first = i;
			visited[index - 1] = true;
		} else {
			indices[index - 1].second = i;
		}
	}
	sort(indices, indices + N);
	int sum = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = i + 1; j < N; ++j) {
			if (indices[j].first > indices[i].second) {
				break;
			}
			if (indices[j].second > indices[i].second) {
				++sum;
			}
		}
	}

	out << sum << endl;

	return 0;
}
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int maxN = 100001;
int N;
pair<int, int> cows[maxN];

bool cmp(const pair<int, int>& a, const int b) {
	return a.second > b;
}

int main() {
	ifstream f("fairphoto.in");
	ofstream out("fairphoto.out");

	f >> N;
	for (int i = 0; i < N; ++i) {
		char color;
		f >> cows[i].first >> color;
		int col = color == 'W' ? 1 : -1;
		cows[i].second = col;
	}
	sort(cows, cows + N);

	for (int i = 1; i < N; ++i) {
		cows[i].second += cows[i - 1].second;
	}

	int best = -1;
	for (int mod = 0; mod < 2; mod++) {
		vector<pair<int, int>> left;
		if (mod == 1) {
			left.push_back({ cows[0].first, 0 });
		}
		for (int i = mod; i < N; i += 2) {
			int prefix = cows[i].second;
			auto it = lower_bound(left.cbegin(), left.cend(), prefix, cmp);
			if (it != left.cend()) {
				best = max(best, cows[i].first - it->first);
			}

			if (i < N - 1 && (left.empty() || prefix < left.back().second)) {
				left.push_back({ cows[i + 1].first, prefix });
			}
		}
	}

	out << best << endl;
	out.close();
	return 0;
}

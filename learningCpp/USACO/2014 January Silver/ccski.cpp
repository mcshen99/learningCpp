#include <fstream>
#include <queue>
#include <utility>
#include <iostream>

using namespace std;

int elevations[500][500];
int dirs[2][4] = { {1, -1, 0, 0}, {0, 0, 1, -1} };
int m, n;
vector<pair<int, int>> waypoints;

bool bfs(int, int, int);
bool inBounds(int, int);

int main() {
	ifstream f("ccski.in");
	ofstream out("ccski.out");

	f >> m >> n;

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			int x;
			f >> x;
			elevations[i][j] = x;
		}
	}
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			int x;
			f >> x;
			if (x == 1) {
				waypoints.push_back({ i, j });
			}
		}
	}

	int a = 0;
	int b = 1000000000;
	while (a < b) {
		//cout << a << " " << b << endl;
		int mid = (a + b) / 2;
		if (bfs(mid, waypoints[0].first, waypoints[0].second)) {
			b = mid;
		} else {
			a = mid + 1;
		}
	}

	out << a << endl;

	return 0;
}

bool bfs(int diff, int a, int b) {
	bool visited[500][500] = { false };

	queue<pair<int, int>> q;
	q.push({ a, b });
	visited[a][b] = true;

	while (!q.empty()) {
		pair<int, int>& next = q.front();
		q.pop();
		//cout << next.first << ", " << next.second << endl;
		for (int i = 0; i < 4; ++i) {
			int x = next.first + dirs[0][i];
			int y = next.second + dirs[1][i];
			if (inBounds(x, y) && !visited[x][y] && abs(elevations[x][y] - elevations[next.first][next.second]) <= diff) {
				q.push({ x, y });
				visited[x][y] = true;
			}
		}
	}

	for (auto p : waypoints) {
		if (!visited[p.first][p.second]) {
			return false;
		}
	}
	return true;
}

bool inBounds(int i, int j) {
	return i >= 0 && j >= 0 && i < m && j < n;
}
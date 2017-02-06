#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

const int maxN = 10000;
const int maxM = 50000;
const int infinity = 1000000001;
int N, M;
vector<pair<int, int>> gps1[maxN];
vector<pair<int, int>> gps2[maxN];
vector<pair<int, int>> g[maxN];
int dist[3][maxN];
bool visited[maxN];

void dijkstras(vector<pair<int, int>> v[maxN], int a);

int main() {
	ifstream f("gpsduel.in");
	ofstream out("gpsduel.out");

	f >> N >> M;
	for (int i = 0; i < M; ++i) {
		int x, y, p, q;
		f >> x >> y >> p >> q;
		gps1[y - 1].push_back({ x - 1, p });
		gps2[y - 1].push_back({ x - 1, q });
	}

	dijkstras(gps1, 0);
	dijkstras(gps2, 1);

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < gps1[i].size(); ++j) {
			int x = 0;
			int end = gps1[i][j].first;
			if (dist[0][end] - dist[0][i] != gps1[i][j].second) {
				x++;
			}
			if (dist[1][end] - dist[1][i] != gps2[i][j].second) {
				x++;
			}
			g[i].push_back({ end, x });
		}
	}
	//cout << endl;
	
	dijkstras(g, 2);

	out << dist[2][0] << endl;
	out.close();

	return 0;
}

void dijkstras(vector<pair<int, int>> graph[maxN], int a) {
	for (int i = 0; i < N; ++i) {
		dist[a][i] = infinity;
		visited[i] = false;
	}
	dist[a][N - 1] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	q.push({ 0, N - 1 });

	while (!q.empty()) {
		int u = q.top().second;
		q.pop();

		if (visited[u]) {
			continue;
		}

		visited[u] = true;

		for (int i = 0; i < graph[u].size(); ++i) {
			int weight = graph[u][i].second;
			int v = graph[u][i].first;
			if (dist[a][u] + weight < dist[a][v]) {
				dist[a][v] = dist[a][u] + weight;
				q.push({ dist[a][v], v });
			}
		}
	}
}
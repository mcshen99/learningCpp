#include <fstream>
#include <iostream>

using namespace std;

int adj[250][250];
long distances[250];
int parent[250];
long infinity = 1000001 * 250;
bool visited[250];
int n, m;

void dijkstras();

int main() {
	ifstream f("rblock.in");
	ofstream out("rblock.out");

	f >> n >> m;
	for (int i = 0; i < m; ++i) {
		int a, b, l;
		f >> a >> b >> l;
		adj[a - 1][b - 1] = l;
		adj[b - 1][a - 1] = l;
	}

	dijkstras();
	int path[250];
	int count = 0;
	int k = n - 1;
	while (k != -1) {
		path[count] = k;
		++count;
		k = parent[k];
	}
	int originalShortest = distances[n - 1];

	int max = -1;
	for (int i = 0; i < count - 1; ++i) {
		adj[path[i]][path[i + 1]] *= 2;
		adj[path[i + 1]][path[i]] *= 2;

		dijkstras();
		int newShortest = distances[n - 1];
		if (newShortest - originalShortest > max) {
			max = newShortest - originalShortest;
		}

		adj[path[i]][path[i + 1]] /= 2;
		adj[path[i + 1]][path[i]] /= 2;
	}

	out << max << endl;

	return 0;
}

void dijkstras() {
	for (int i = 0; i < n; ++i) {
		distances[i] = infinity;
		visited[i] = false;
		parent[i] = -1;
	}
	distances[0] = 0;
	int nodesVisited = 0;

	while (nodesVisited < n) {
		int leastDist = infinity;
		int node = -1;
		for (int i = 0; i < n; ++i) {
			if (!visited[i]) {
				if (distances[i] < leastDist) {
					leastDist = distances[i];
					node = i;
				}
			}
		}

		visited[node] = true;
		if (node == n - 1) {
			break;
		}

		for (int i = 0; i < n; ++i) {
			int weight = adj[node][i];
			if (weight == 0 && node != i) {
				weight = infinity;
			}
			if (distances[node] + weight < distances[i]) {
				distances[i] = distances[node] + weight;
				parent[i] = node;
			}
		}
	}
}
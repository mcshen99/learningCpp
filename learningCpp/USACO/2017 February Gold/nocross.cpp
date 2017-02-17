#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int maxN = 1000;
int N;

int biggest(pair<int, int> graph[]);

int main() {
	ifstream f("nocross.in");
	ofstream out("nocross.out");

	f >> N;
	pair<int, int> graph[maxN];
	pair<int, int> graph2[maxN];
	for (int i = 0; i < N; ++i) {
		int x;
		f >> x;
		graph[i].first = x - 1;
	}
	for (int i = 0; i < N; ++i) {
		int x;
		f >> x;
		graph[i].second = x - 1;
	}
	for (int i = 0; i < N; ++i) {
		graph2[i].first = graph[N - 1 - i].first;
		graph2[i].second = graph[N - 1 - i].second;
	}
	for (int i = 0; i < N; ++i) {
		cout << graph[i].first << " " << graph[i].second << endl;
	}
	cout << endl;

	int a = biggest(graph);
	int b = biggest(graph2);
	if (a >= b) {
		out << a << endl;
	} else {
		out << b << endl;
	}

	return 0;
}

int biggest(pair<int, int> graph[]) {
	//find biggest going up for 1, 2, ..., N and down for 1, 2, ..., N
	vector<int> edges[maxN];
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (abs(graph[i].first - graph[j].second) <= 4) {
				edges[i].push_back(j);
			}
		}
	}
	for (int i = 0; i < N; ++i) {
		cout << i << ": ";
		for (int j = 0; j < edges[i].size(); ++j) {
			cout << edges[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	vector<int> back[maxN];
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (abs(graph[i].first - graph[j].second) <= 4) {
				back[j].push_back(i);
			}
		}
	}
	for (int i = 0; i < N; ++i) {
		cout << i << ": ";
		for (int j = 0; j < back[i].size(); ++j) {
			cout << back[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	//going down
	int max = -1;
	for (int i = 0; i < N; ++i) {
		int last = -1;
		int sum = 0;
		for (int node = i; node < N; ++node) {
			vector<int>::iterator up = upper_bound(edges[node].begin(), edges[node].end(), last);
			if (up != edges[node].cend()) {
				int temp = edges[node][up - edges[node].begin()];
				int minX = N;
				for (int x = last; x < temp; ++x) {
					vector<int>::iterator backUp = upper_bound(back[node].begin(), edges[node].end(), temp);
					if (backUp != back[temp].cend()) {
						int backTemp = back[temp][backUp - back[temp].begin()];
						if (backTemp < minX) {
							minX = backTemp;
						}
					}
				}
			}
		}

		if (sum > max) {
			max = sum;
		}
		cout << endl;
	}

	return max;
}
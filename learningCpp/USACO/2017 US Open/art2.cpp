#include <fstream>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>

	using namespace std;

const int maxN = 100000;
int N;
set<int> available;
vector<int> painting;

set<int> needRectangle(int&, set<int>&);
bool containsAll(set<int>&);

int main() {
	ifstream f("art2.in");
	ofstream out("art2.out");

	f >> N;
	map<int, set<int>> picowso;
	for (int i = 0; i < N; ++i) {
		int x;
		f >> x;
		painting.push_back(x);
		set<int> list = picowso[x];
		list.insert(i);
		picowso[x] = list;
	}

	map<int, set<int>> need;
	for (auto it = picowso.begin(); it != picowso.end(); ++it) {
		int key = it->first;
		if (key != 0) {
			need[key] = needRectangle(key, picowso[key]);
		}
	}
	set<int> never = picowso[0];
	for (auto it = need.begin(); it != need.end(); ++it) {
		for (int j : it->second) {
			if (find(never.begin(), never.end(), j) != never.end()) {
				out << -1 << endl;
				return 0;
			}
		}
	}

	int count = 0;
	map<int, bool> visited;
	set<int> keySet;
	for (auto it = need.begin(); it != need.end(); ++it) {
		keySet.insert(it->first);
	}
	while (!keySet.empty()) {
		count++;
		set<int> toAdd;
		for (auto it = need.begin(); it != need.end(); ++it) {
			int key = it->first;
			if (!visited[key]) {
				if (containsAll(need[key])) {
					toAdd.insert(picowso[key].begin(), picowso[key].end());
					visited[key] = true;
					keySet.erase(key);
				}
			}
		}

		available.insert(toAdd.begin(), toAdd.end());
	}

	out << count << endl;

	return 0;
}

set<int> needRectangle(int& c, set<int>& list) {
	set<int> need;
	int smallest = N;
	int biggest = -1;
	for (int i : list) {
		if (i > biggest) {
			biggest = i;
		}
		if (i < smallest) {
			smallest = i;
		}
	}

	for (int i = smallest; i <= biggest; ++i) {
		if (painting[i] != c) {
			need.insert(i);
		}
	}

	return need;
}

bool containsAll(set<int>& list) {
	for (int i : list) {
		if (available.find(i) == available.end()) {
			return false;
		}
	}

	return true;
}
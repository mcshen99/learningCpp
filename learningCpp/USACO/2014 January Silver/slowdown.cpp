#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	ifstream f("slowdown.in");
	ofstream out("slowdown.out");

	int n;
	f >> n;

	vector<int> t;
	vector<int> d;
	for (int i = 0; i < n; ++i) {
		string s;
		int x;
		f >> s >> x;
		if (s == "T") {
			t.push_back(x);
		} else {
			d.push_back(x);
		}
	}

	sort(t.begin(), t.end());
	sort(d.begin(), d.end());

	/*cout << "t: ";
	for (auto i : t) {
		cout << i << " ";
	}
	cout << endl << "d: ";
	for (auto i : d) {
		cout << i << " ";
	}
	cout << endl;
	cout << endl;*/

	double currSpeed = 1.0;
	double tFirst = t[0];
	double dFirst = d[0];
	long double totalTime = 0;
	long double totalDistance = 0;
	int count = 1;
	while (!t.empty() || !d.empty()) {
		//cout << tFirst << " " << dFirst << endl;
		double timeToD = (dFirst) / currSpeed;
		double distToT = (tFirst) * currSpeed;
		//cout << timeToD << " " << distToT << endl;
		if (t.empty()) {
			//cout << "A" << endl;
			totalTime += timeToD;
			totalDistance += dFirst;
			d.erase(d.begin());
			dFirst = d[0] - totalDistance;
		} else if (d.empty()) {
			//cout << "B" << endl;
			totalTime += tFirst;
			totalDistance += distToT;
			t.erase(t.begin());
			tFirst = t[0] - totalTime;
		} else {
			if (timeToD < tFirst) {
				//cout << "C" << endl;
				totalTime += timeToD;
				totalDistance += dFirst;
				d.erase(d.begin());
				dFirst = d[0] - totalDistance;
				tFirst -= timeToD;
			} else {
				//cout << "D" << endl;
				totalTime += tFirst;
				totalDistance += distToT;
				t.erase(t.begin());
				tFirst = t[0] - totalTime;
				dFirst -= distToT;
			}
		}

		/*cout << "t: ";
		for (auto i : t) {
			cout << i << " ";
		}
		cout << endl << "d: ";
		for (auto i : d) {
			cout << i << " ";
		}
		cout << endl;
		cout << "totals: " << totalTime << " " << totalDistance;
		cout << endl;
		cout << endl;*/

		count++;
		currSpeed = 1.0 / count;
	}
	//cout << totalTime << endl;

	if (totalDistance >= 1000) {
		long long tot = round(totalTime);
		//cout << tot << endl;
		out << tot << endl;
	} else {
		double dLeft = 1000 - totalDistance;
		int tLeft = dLeft / currSpeed;
		totalTime += tLeft;
		//cout << "changedTime: " << totalTime << endl;
		long long tot = round(totalTime);
		//cout << tot << endl;
		out << tot << endl;
	}

	return 0;
}
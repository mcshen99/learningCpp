#include <fstream>
#include <queue>
#include <list>
#include <vector>

using namespace std;

struct Cow {
	int g;
	int d;
};

bool sortAll(const Cow&, const Cow&);

int main() {
	ifstream f("msched.in");
	ofstream out("msched.out");

	int N;
	f >> N;

	list<Cow> allCows;
	for (int i = 0; i < N; ++i) {
		Cow c;
		f >> c.g >> c.d;
		allCows.push_back(c);
	}
	allCows.sort(sortAll);

	int sum = 0;

	std::priority_queue<int> q;

	list<Cow>::const_iterator it = allCows.begin();
	int largestDeadline = (*it).d;
	for (int i = largestDeadline; i > 0; --i) {
		while ((*it).d == i && it != allCows.end()) {
			q.push((*it).g);
			++it;
		}

		if (!q.empty()) {
			sum += q.top();
			q.pop();
		}
	}

	out << sum << endl;

	return 0;
}

bool sortAll(const Cow& a, const Cow& b) {
	return a.d > b.d;
}
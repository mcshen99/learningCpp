#include <vector>
#include <memory>
#include <iostream>

using namespace std;

auto make() {
	return make_shared<vector<int>>();
}

auto read(shared_ptr<vector<int>> p) {
	cout << "Enter values: " << endl;
	int x;

	while (cin >> x) {
		p->push_back(x);
	}

	return p;
}

auto print(shared_ptr<vector<int>> p) {
	for (int i : *p) {
		cout << i << " ";	
	}
}

int main() {
	auto p = read(make());
	print(p);

	return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<class T, class InputIterator> T median(InputIterator begin, InputIterator end) {
	if (begin == end) {
		throw domain_error("median of an empty vector");
	}

	vector<T> temp;
	while (begin != end) {
		temp.push_back(*begin);
		++begin;
	}
	sort(temp.begin(), temp.end());

	typedef typename vector<T>::size_type vec_sz;
	vec_sz size = temp.size();
	vec_sz mid = size / 2;

	return size % 2 == 0 ? (temp[mid] + temp[mid - 1]) / 2 : temp[mid];
}

int main() {
	int arr[9] = { 3, 4, 5, 1, 7, 2, 6, 9, 8 };
	cout << median<int>(begin(arr), end(arr)) << endl;
	vector<int> v;
	for (int i : arr) {
		v.push_back(i);
		cout << i << " ";
	}
	cout << endl;
	cout << median<int>(v.begin(), v.end()) << endl;
}
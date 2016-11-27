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
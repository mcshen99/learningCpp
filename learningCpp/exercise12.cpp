#include <vector>
#include<iterator>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

class Str {
	friend std::istream& operator >> (std::istream& is, Str& s) {
		s.data.clear();

		char c;
		while (is.get(c) && isspace(c));
		if (is) {
			do {
				s.data.push_back(c);
			} while (is.get(c) && !isspace(c));

			if (is) {
				is.unget();
			}
		}

		return is;
	}
public:
	Str& operator+=(const Str& s) {
		std::copy(s.data.begin(), s.data.end(), std::back_inserter(data));
		return *this;
	}

	typedef std::vector<char>::size_type size_type;

	Str() { }
	Str(size_type n, char c) : data(n, c) { }
	Str(const char* cp) {
		std::copy(cp, cp + std::strlen(cp), std::back_inserter(data));
	}
	template<class In> Str(In b, In e) {
		std::copy(b, e, std::back_inserter(data));
	}

	size_type size() const { return data.size(); }

	char& operator[](size_type i) { return data[i]; }
	const char& operator[](size_type i) const { return data[i]; }

	operator bool() const { return data.size() > 0; }

private:
	std::vector<char> data;
};

ostream& operator<<(ostream& os, const Str& s) {
	for (Str::size_type i = 0; i != s.size(); ++i) {
		os << s[i];
	}
	return os;
}

Str operator+(const Str& s, const Str& t) {
	Str r = s;
	r += t;
	return r;
}

Str operator+(const Str& s, const char* t) {
	Str r = s;
	r += t;
	return r;
}

Str operator+(const char* s, const Str& t) {
	Str r = s;
	r += t;
	return r;
}

bool operator<(const Str& lhs, const Str& rhs) {
	std::vector<char>::size_type lhs_size = lhs.size();
	for (std::vector<char>::size_type i = 0; i < rhs.size(); ++i) {
		if (lhs_size <= i) {
			return true;
		}
		int cmp = strcmp(&lhs[i], &rhs[i]);
		if (cmp < 0) {
			return true;
		} else if (cmp > 0) {
			return false;
		}
	}

	return false;
}

bool operator<=(const Str& lhs, const Str& rhs) {
	std::vector<char>::size_type lhs_size = lhs.size();
	for (std::vector<char>::size_type i = 0; i < rhs.size(); ++i) {
		if (lhs_size <= i) {
			return true;
		}
		int cmp = strcmp(&lhs[i], &rhs[i]);
		if (cmp < 0) {
			return true;
		} else if (cmp > 0) {
			return false;
		}
	}

	return true;
}

bool operator>(const Str& lhs, const Str& rhs) {
	std::vector<char>::size_type lhs_size = lhs.size();
	for (std::vector<char>::size_type i = 0; i < rhs.size(); ++i) {
		if (lhs_size <= i) {
			return false;
		}
		int cmp = strcmp(&lhs[i], &rhs[i]);
		if (cmp < 0) {
			return false;
		} else if (cmp > 0) {
			return true;
		}
	}

	return false;
}

bool operator>=(const Str& lhs, const Str& rhs) {
	std::vector<char>::size_type lhs_size = lhs.size();
	for (std::vector<char>::size_type i = 0; i < rhs.size(); ++i) {
		if (lhs_size <= i) {
			return false;
		}
		int cmp = strcmp(&lhs[i], &rhs[i]);
		if (cmp < 0) {
			return false;
		} else if (cmp > 0) {
			return true;
		}
	}

	return true;
}

bool operator==(const Str& lhs, const Str& rhs) {
	if (lhs.size() != rhs.size()) {
		return false;
	}
	for (std::vector<char>::size_type i = 0; i < rhs.size(); ++i) {
		int cmp = strcmp(&lhs[i], &rhs[i]);
		if (cmp != 0) {
			return false;
		}
	}

	return true;
}

bool operator!=(const Str& lhs, const Str& rhs) {
	if (lhs.size() != rhs.size()) {
		return true;
	}
	for (std::vector<char>::size_type i = 0; i < min(lhs.size(), rhs.size()); ++i) {
		int cmp = strcmp(&lhs[i], &rhs[i]);
		if (cmp != 0) {
			return true;
		}
	}

	return false;
}

int main() {
	double d = 10;
	double d2;
	d2 = 10;

	Str s("hello");
	Str t = "hello";
	s = "hello";

	Str name;
	cout << "Enter your name: ";
	cin >> name;
	const Str greeting = "Hello, " + name + "! ";

	Str foo = "alpha";
	Str bar = "alpha";

	if (foo == bar) std::cout << "foo and bar are equal\n";
	if (foo != bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
	if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";

	Str test;
	if (test) {
		cout << "test is not empty." << endl;
	} else {
		cout << "test is empty." << endl;
	}
	Str me = "me";
	if (me) {
		cout << "me is not empty." << endl;
	} else {
		cout << "me is empty." << endl;
	}

	return 0;
}
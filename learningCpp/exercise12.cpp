#include <vector>
#include<iterator>
#include <iostream>

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

	return 0;
}
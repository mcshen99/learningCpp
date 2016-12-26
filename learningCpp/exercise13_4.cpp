#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

istream& read_hw(istream&, vector<double>&);
double median(vector<double>);

class Core {
	friend class Student_info;

public:
	virtual ~Core() { }
	Core() : midterm(0), final(0) { }
	Core(std::istream& is) { read(is); }

	std::string name() const;

	virtual std::istream& read(std::istream&);
	virtual double grade() const;
	void regrade(double d) { final = d; }
	virtual void regrade(double d, double = 0) { final = d; }
	virtual std::string letter_grade();

protected:
	std::istream& read_common(std::istream&);
	double midterm, final;
	std::vector<double> homework;
	virtual Core* clone() const { return new Core(*this); }

private:
	std::string n;
};

class Grad : public Core {
public:
	Grad() : thesis(0) { }
	Grad(std::istream& is) { read(is); }

	double grade() const;
	std::istream& read(std::istream&);
	void regrade(double d1, double d2) { final = d1; thesis = d2; }
	string letter_grade();

protected:
	Grad* clone() const { return new Grad(*this); }

private:
	double thesis;
};

class Student_info {
public:
	Student_info() : cp(0) { }
	Student_info(std::istream& is) : cp(0) { read(is); }
	Student_info(const Student_info& s) : cp(0) {
		if (s.cp) {
			cp = s.cp->clone();
		}
	}
	Student_info& operator= (const Student_info& s) {
		if (&s != this) {
			delete cp;
			if (s.cp) {
				cp = s.cp->clone();
			} else {
				cp = 0;
			}
		}

		return *this;
	}
	~Student_info() { delete cp; }

	std::istream& read(std::istream& is) {
		delete cp;

		char ch;
		is >> ch;

		if (ch == 'U') {
			cp = new Core(is);
		} else {
			cp = new Grad(is);
		}

		return is;
	}

	std::string name() const {
		if (cp) {
			return cp->name();
		} else {
			throw std::runtime_error("uninitialized Student");
		}
	}

	double grade() const {
		if (cp) {
			return cp->grade();
		} else {
			throw std::runtime_error("uninitialized Student");
		}
	}

	static bool compare(const Student_info& s1, const Student_info& s2) {
		return s1.name() < s2.name();
	}

private:
	Core* cp;
};

string Core::name() const { return n; }

double grade(double midterm, double final, double homework) {
	return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

double grade(double midterm, double final, const vector<double>& hw) {
	if (hw.size() == 0) {
		throw domain_error("student has done no homework");
	}
	return grade(midterm, final, median(hw));
}

double median(vector<double> vec) {
	typedef vector<double>::size_type vec_sz;
	vec_sz size = vec.size();
	if (size == 0) {
		throw domain_error("median of an empty vector");
	}
	sort(vec.begin(), vec.end());

	vec_sz mid = size / 2;
	return size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}

double Core::grade() const {
	return ::grade(midterm, final, homework);
}

istream& Core::read_common(istream& in) {
	in >> n >> midterm >> final;
	return in;
}

istream& read_hw(istream& in, vector<double>& hw) {
	if (in) {
		hw.clear();

		double x;
		while (in >> x) {
			hw.push_back(x);
		}

		in.clear();
	}
	return in;
}

istream& Core::read(istream& in) {
	read_common(in);
	read_hw(in, homework);
	return in;
}

istream& Grad::read(istream& in) {
	read_common(in);
	in >> thesis;
	read_hw(in, homework);
	return in;
}

double Grad::grade() const {
	return min(Core::grade(), thesis);
}

bool compare(const Core& c1, const Core& c2) {
	return c1.name() < c2.name();
}

bool compare_grades(const Core& c1, const Core& c2) {
	return c1.grade() < c2.grade();
}

bool compare_Core_ptrs(const Core* cp1, const Core* cp2) {
	return compare(*cp1, *cp2);
}

string Core::letter_grade() {
	static const double numbers[] = { 97, 94, 90, 87, 84, 80, 77, 74, 70, 60, 0 };
	static const char* const letters[]{ "A+", "A", "A-", "B+", "B-", "C+", "C", "C-", "D", "F" };

	static const size_t ngrades = sizeof(numbers) / sizeof(*numbers);

	double grade = this->grade();
	for (size_t i = 0; i < ngrades; ++i) {
		if (grade >= numbers[i]) {
			return letters[i];
		}
	}

	return "?\?\?";
}

string Grad::letter_grade() {
	static const double numbers[] = { 97, 94, 90, 87, 84, 80, 77, 74, 70, 60, 0 };
	static const char* const letters[]{ "A+", "A", "A-", "B+", "B-", "C+", "C", "C-", "D", "F" };

	static const size_t ngrades = sizeof(numbers) / sizeof(*numbers);

	double grade = this->grade();
	for (size_t i = 0; i < ngrades; ++i) {
		if (grade >= numbers[i]) {
			return letters[i];
		}
	}

	return "?\?\?";
}

int main() {
	Core c(cin);
	cout << c.grade() << " " << c.letter_grade() << endl;
	
	Grad g(cin);
	cout << g.grade() << " " << g.letter_grade() << endl;

	return 0;
}
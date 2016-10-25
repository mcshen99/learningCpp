#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector <string> Rule;
typedef vector<Rule> Rule_collection;
typedef map<string, Rule_collection> Grammar;

vector<string> split(const string&);
map<string, vector<int>> xref(istream&, vector<string> find_words(const string&) = split);
Grammar read_grammar(istream&);
vector<string> gen_sentence(const Grammar&);

int main() {
	/*map<string, vector<int> > ret = xref(cin);

	for (map<string, vector<int> >::const_iterator it = ret.begin(); it != ret.end(); ++it) {
		cout << it->first << " occurs on line(s): ";
		vector<int>::const_iterator line_it = it->second.begin();
		cout << *line_it;

		++line_it;
		while (line_it != it->second.end()) {
			cout << ", " << *line_it;
			++line_it;
		}

		cout << endl;
	}*/



	vector<string> sentence = gen_sentence(read_grammar(cin));

	vector<string>::const_iterator it = sentence.begin();
	if (!sentence.empty()) {
		cout << *it;
		++it;
	}

	while (it != sentence.end()) {
		cout << " " << *it;
		++it;
	}

	cout << endl;



	return 0;
}

bool space(char c) {
	return isspace(c);
}

bool not_space(char c) {
	return !isspace(c);
}

vector<string> split(const string& str) {
	typedef string::const_iterator iter;
	vector <string> ret;

	iter i = str.begin();
	while (i != str.end()) {
		i = find_if(i, str.end(), not_space);
		iter j = find_if(i, str.end(), space);

		if (i != str.end()) {
			ret.push_back(string(i, j));
		}

		i = j;
	}

	return ret;
}

map<string, vector<int>> xref(istream& in, vector<string> find_words(const string&)) {
	string line;
	int line_number = 0;
	map<string, vector<int>> ret;

	while (getline(in, line)) {
		++line_number;

		vector<string> words = find_words(line);

		for (vector<string>::const_iterator it = words.begin(); it != words.end(); ++it) {
			ret[*it].push_back(line_number);
		}
	}

	return ret;
}

Grammar read_grammar(istream& in) {
	Grammar ret;
	string line;

	while (getline(in, line)) {
		vector<string> entry = split(line);

		if (!entry.empty()) {
			ret[entry[0]].push_back(Rule(entry.begin() + 1, entry.end()));
		}
	}

	return ret;
}

bool bracketed(const string& s) {
	return s.size() > 1 && s[0] == '<' && s[s.size() - 1] == '>';
}

int nrand(int n) {
	if (n <= 0 || n > RAND_MAX) {
		throw domain_error("Argument to nrand is out of range");
	}

	const int bucket_size = RAND_MAX / n;
	int r;

	do r = rand() / bucket_size;
	while (r >= n);

	return r;
}

void gen_aux(const Grammar& g, const string& word, vector<string>& ret) {
	if (!bracketed(word)) {
		ret.push_back(word);
	} else {
		Grammar::const_iterator it = g.find(word);
		if (it == g.end()) {
			throw logic_error("empty rule");
		}

		const Rule_collection& c = it->second;

		const Rule& r = c[nrand(c.size())];

		for (Rule::const_iterator i = r.begin(); i != r.end(); ++i) {
			gen_aux(g, *i, ret);
		}
	}
}

vector<string> gen_sentence(const Grammar& g) {
	vector<string> ret;
	gen_aux(g, "<sentence>", ret);
	return ret;
}
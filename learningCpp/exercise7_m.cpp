//Exercise 7-m (Markov chain for text generation). Keep a map that stores a count of what 
//the next character is, given the last j characters for all j <= n = 5  
//(you should be able to vary n later). Read in a file character by character 
//(http://www.cplusplus.com/reference/istream/istream/get/) using a loop, 
//and store the frequencies in the map. Then, from standard input, have the user specify a length 
//and then a line of text. Generate that many characters by randomly choosing a letter 
//given the last n and if the pattern from the last n doesn’t exist, try again with one less character. 
//Discrete_distribution will work here again, but it only returns integers, so you will have to use 
//the map iterator to convert to characters.

#include <iostream> 
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <queue>
#include <random>
#include <time.h>

using namespace std;

string queueToString(queue<char>, int);

int main() {
	string str;

	cout << "Enter name of existing text file: ";
	getline(cin, str);

	int n = 5;
	map<string, map<char, int>> stringMap;
	map<char, int> forBlankString;
	for (int i = 1; i <= n; ++i) {
		queue<char> queue;
		ifstream is(str);

		char c;
		while (is.get(c)) {
			if (i == 1) {
				++forBlankString[c];
			}
			queue.push(c);
			if (queue.size() == i + 1) {
				string key = queueToString(queue, i);
				queue.pop();
				map<char, int> currKey = stringMap[key];
				++currKey[c];
				stringMap[key] = currKey;
			}
		}
	}
	stringMap[""] = forBlankString;

	cout << "Enter length: ";
	string lengthStr;
	getline(cin, lengthStr);
	int length = stoi(lengthStr);
	string text;
	cout << "Enter text: ";
	getline(cin, text);

	int count = 0;
	while (count < length) {
		int textLength = text.size();
		map<char, int> currKey = stringMap[""];
		for (int i = n; i >= 0; --i) {
			if (i < textLength) {
				string s = text.substr(textLength - i);
				currKey = stringMap[s];
				if (!currKey.empty()) {
					break;
				}
			}
		}

		vector<int> d;
		for (map<char, int>::const_iterator it = currKey.begin(); it != currKey.end(); ++it) {
			d.push_back(it->second);
		}

		default_random_engine generator(clock());
		discrete_distribution<int> distribution(d.begin(), d.end());

		int pos = distribution(generator);

		int sum = 0;
		char addOn;
		for (map<char, int>::const_iterator it = currKey.begin(); it != currKey.end(); ++it) {
			sum += it->second;
			if (sum >= pos) {
				addOn = it->first;
				break;
			}
		}

		text += addOn;
		count++;
	}

	cout << text;

	return 0;
}

string queueToString(queue<char> queue, int k) {
	string str;
	int count = 0;
	while (k != count) {
		str += queue.front();
		queue.pop();
		count++;
	}

	return str;
}
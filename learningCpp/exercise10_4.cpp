#include <string>
#include <iostream>

using namespace std;

class String_node {
public: 
	String_node(string v0) : value(v0), next(nullptr) {
		//cout << "creating " << value << endl;
	}
	String_node(string v0, String_node* n0) : value(v0), next(n0) { 
		//cout << "creating " << value << endl; 
	}
	//~String_node() { cout << "destroying " << value << endl; }
	String_node* next;
	string value;
};

class String_list {
public:
	String_list() : head(nullptr) {}
	void push_front(string s);
	void insert(int pos, string s);
	void erase(int pos);
	void pop_front();
	String_node* iterator() { return head; }

private:
	String_node* head;
};

void String_list::push_front(string s) {
	head = new String_node(s, head);
}

void String_list::insert(int pos, string s) {
	if (pos != 0) {
		String_node* itr = head;
		for (int count = 0; count < pos - 1; ++count) {
			itr = itr->next;
		}

		itr->next = new String_node(s, itr->next);
	} else {
		push_front(s);
	}
}

void String_list::erase(int pos) {
	if (pos != 0) {
		String_node* itr = head;

		for (int count = 0; count < pos - 1; ++count) {
			itr = itr->next;
		}

		String_node* temp = itr->next;
		itr->next = itr->next->next;
		delete temp;
	} else {
		pop_front();
	}
}

void String_list::pop_front() {
	String_node* temp = head;
	head = head->next;
	delete temp;
}

int main() {
	String_list l; 
	l.push_front("world");
	l.push_front("hello");
	for (String_node* itr = l.iterator(); itr != nullptr; itr = itr->next) {
		cout << itr->value << " ";
	}
	cout << endl;

	l.insert(1, "xd");
	for (String_node* itr = l.iterator(); itr != nullptr; itr = itr->next) {
		cout << itr->value << " ";
	}
	cout << endl;

	l.pop_front();
	for (String_node* itr = l.iterator(); itr != nullptr; itr = itr->next) {
		cout << itr->value << " ";
	}
	cout << endl;

	l.push_front("hello");
	l.erase(1);
	for (String_node* itr = l.iterator(); itr != nullptr; itr = itr->next) {
		cout << itr->value << " ";
	}
	cout << endl;
}
#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Virus {
public:
	list<int> host;
	list<int>::iterator curNode;

	Virus(list<int> host) {
		this->host = host;
		reset();
	}

	void show(bool debug = false) {
		for (auto iter = host.begin(); iter != host.end(); ++iter) {
			if (debug) cout << (iter == curNode ? "[" : "") << *iter << (iter == curNode ? "] " : " ");
			else cout << *iter << '\n';
		}
	}

	void reset() {
		curNode = host.begin();
	}

	bool deadEnd() {
		auto nextNode = curNode;
		++nextNode;

		if (nextNode == host.end()) {
			return true;
		}
		return false;
	}

	void next() {
		if (deadEnd()) {
			reset();
			return;
		}
		++curNode;
	}

	void insertBefore(int x) {
		host.insert(curNode, x);
	}

	void insertAfter(int x) {
		auto nextIter = curNode;
		++nextIter;

		auto newIter = host.insert(nextIter, x);
		curNode = --newIter;
	}
};

void test() {
	Virus virus = Virus({1, 2, 3});
	virus.insertBefore(100);
	virus.next();
	virus.insertAfter(500);
	virus.reset();
	virus.next();
	virus.next();
	virus.next();
	virus.next();
	virus.insertBefore(50);
	virus.next();
	virus.insertAfter(99);

	virus.show(true);
}

int main(void) {
	// test();

	int hostSize, queries;
	int hostInput;
	cin >> hostSize >> queries;

	auto host = list<int>();
	for (int i = 0; i < hostSize; i++) {
		cin >> hostInput;
		host.push_back(hostInput);
	}

	Virus virus = Virus(host);
	int command, input;
	
	for (int i = 0; i < queries; i++) {
		cin >> command;
		switch (command) {
		case 1:
			virus.reset();
			break;
		case 2:
			virus.next();
			break;
		case 3:
			cin >> input;
			virus.insertBefore(input);
			break;
		case 4:
			cin >> input;
			virus.insertAfter(input);
			break;
		}
	}

	virus.show();

	return 0;
}
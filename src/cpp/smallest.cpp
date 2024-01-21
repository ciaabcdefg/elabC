#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void show(vector<int> v) {
	for (auto x : v) {
		cout << x << ' ';
	}
	cout << '\n';
}

class minVectors {
public:
	vector<int> minVector;
	vector<int> inversedVector;
};

minVectors minVector(vector<int> v) {
	vector<int> minVec;
	vector<int> invVec;

	int min = 1000000001;
	for (auto x : v) {
		if (x < min) {
			min = x;
		}
		minVec.push_back(min);
	}
	invVec = minVec;
	reverse(invVec.begin(), invVec.end());

	minVectors container;
	container.minVector = minVec;
	container.inversedVector = invVec;

	return container;
}

void test() {
	vector<int> heights{ 100, 240, 80, 90, 75 };
	
	auto container = minVector(heights);
	vector<int> minVec = container.minVector;
	vector<int> invVec = container.inversedVector;

	int height = 80;

	show(heights);
	show(invVec);
	auto lower = lower_bound(invVec.begin(), invVec.end(), height);
	auto upper = upper_bound(invVec.begin(), invVec.end(), height);

	if (lower != invVec.end()) {
		//cout << *lower << ": " << invVec.end() - lower << '\n';
	}
	if (upper != invVec.end()) {
		//cout << *upper << ": " << invVec.end() - upper << '\n';
	}

	if (lower == invVec.end()) {
		cout << '0';
	}
	else {
		cout << *lower << ": " << invVec.end() - lower << '\n';
	}
}

int main(void) {
	// test();

	int n, queries, input;
	cin >> n >> queries;

	vector<int> heights;

	for (int i = 0; i < n; i++) {
		cin >> input;
		heights.push_back(input);
	}

	auto container = minVector(heights);
	vector<int> minVec = container.minVector;
	vector<int> invVec = container.inversedVector;

	int questionType, argument;
	for (int i = 0; i < queries; i++) {
		cin >> questionType >> argument;

		if (questionType == 1) {
			cout << minVec[argument - 1] << '\n';
		}
		else {
			auto lower = lower_bound(invVec.begin(), invVec.end(), argument);
			if (lower == invVec.end()) {
				cout << "0\n";
			}
			else {
				cout << invVec.end() - lower << '\n';
			}
		}
	}
	
	return 0;
}
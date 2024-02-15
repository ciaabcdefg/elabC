#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Task {
public:
	int start;
	int end;
	int weight;

	Task(int start=0, int end=0, int weight=0) {
		this->start = start;
		this->end = end;
		this->weight = weight;
	}

	void show() {
		cout << '(' << start << ", " << end << ')' << " = " << weight;
	}
	
	bool overlap(const Task& other) {
		if (start < other.end && end > other.start) {
			return true;
		}
		return false;
	}

	friend bool operator<(const Task& a, const Task& b) {
		return a.end < b.end;
	}
};

void show(vector<Task>& tasks) {
	for (auto& task : tasks) {
		task.show();
		cout << '\n';
	}
}

int getGreatestNonOverlapper(vector<Task>& tasks, int index) {
	int low = 0;
	int high = index;
	int mid;

	while (true) {
		mid = (low + high) / 2;

		if (tasks[mid].overlap(tasks[index])) {
			if (high == 0 && low == 0) {
				low = -1;
				break;
			}
			high = mid;
		}
		else {
			if (high - low <= 1) break;
			low = mid;
		}
	}
	
	return low;
}

void schedule(vector<Task>& tasks) {
	vector<int> greatestNonOverlapper(tasks.size());

	for (int i = 0; i < tasks.size(); i++) {
		greatestNonOverlapper[i] = getGreatestNonOverlapper(tasks, i);
	}

	vector<int> costs(tasks.size() + 1);
	costs[0] = 0;

	for (int i = 1; i <= tasks.size(); i++) {
		int nonOverlapperCost = tasks[i - 1].weight + costs[1 + greatestNonOverlapper[i - 1]];
		int prevCost = costs[i - 1];

		costs[i] = max(nonOverlapperCost, prevCost);
		// cout << costs[i] << '\n';
	}

	cout << costs[tasks.size()] << '\n';
	vector<int> scheduledTasks;

	for (int i = costs.size() - 1; i > 0;) {
		int nonOverlapperCost = tasks[i - 1].weight + costs[1 + greatestNonOverlapper[i - 1]];
		int prevCost = costs[i - 1];

		if (nonOverlapperCost >= prevCost) {
			// cout << i << "\n";
			scheduledTasks.push_back(i);
			i = 1 + greatestNonOverlapper[i - 1];
		}
		else {
			i--;
		}
	}

	cout << scheduledTasks.size() << '\n';
	for (auto x : scheduledTasks) {
		cout << x << ' ';
	}
	cout << '\n';
}

int main(void) {
	vector<Task> tasks;
	int n, taskBegin, taskEnd, weight;
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> taskBegin >> taskEnd >> weight;
		tasks.push_back(Task(taskBegin, taskEnd, weight));
	}

	sort(tasks.begin(), tasks.end());

	// show(tasks);
	schedule(tasks);

	return 0;
}
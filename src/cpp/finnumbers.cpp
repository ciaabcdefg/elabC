#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int maxReward(vector<int>& rewards, vector<int>& required, int n) {
	vector<int> memo(n + 1);
	vector<int> requiredCount(n + 1);

	if (n <= 3) return 0;

	memo[0] = rewards[0];
	requiredCount[0] = required[0];
	
	for (int i = 1; i <= n; i++) {
		int maximum = INT_MIN;
		int maximumRequiredCount = requiredCount[i - 1];

		// cout << "FOR i = " << i << ": " << maximumRequiredCount << "\n\n";

		for (int j = 1; j <= 4; j++) {
			if (i - j < 0) {
				if (maximumRequiredCount != 0) break;

				maximum = max(maximum, 0);
				continue;
			}

			if (requiredCount[i - j] < maximumRequiredCount) break;

			maximum = max(maximum, memo[i - j]);
			// cout << i << " -> " << maximum << ": " << requiredCount[i - j] << '\n';
		}

		memo[i] = (i == n ? 0 : rewards[i]) + maximum;
		requiredCount[i] = (i == n ? 0 : required[i]) + maximumRequiredCount;
	}

	return memo[n];
}

int main(void) {
	int n;
	cin >> n;

	vector<int> ladder(n);
	vector<int> required(n);

	for (int i = 0; i < n; i++) {
		cin >> ladder[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> required[i];
	}

	cout << maxReward(ladder, required, n) << '\n';

	return 0;
}
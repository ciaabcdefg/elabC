#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class Graph {
public:
	vector<vector<int>> adj;
	vector<int> factories;	

	Graph(int nodes, int numFactories) {
		nodes += 1;
		adj = vector<vector<int>>(nodes);
		factories.reserve(numFactories);
	}

	void addSource(int u) {
		insert(0, u);
	}

	void addFactory(int u) {
		factories.push_back(u);
	}

	void insert(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	unordered_map<int, int> bfs() {
		unordered_map<int, int> distances;
		queue<int> queue;

		queue.push(0);
		distances.insert({0, 0});

		while (!queue.empty()) {
			auto front = queue.front();
			queue.pop();

			/*
			cout << front << '\n';
			if (front == dest) {
				return distances[front];
			}*/

			for (auto neighbor : adj[front]) {
				if (distances.find(neighbor) != distances.end()) continue;
				distances.insert({neighbor, distances[front] + 1});
				queue.push(neighbor);
			}
		}

		return distances;
	}

	void showShipmentCosts() {
		auto allCosts = bfs();
		for (auto factoryIndex : factories) {
			cout << allCosts[factoryIndex] - 1 << '\n';
		}
	}
};

void show(unordered_map<int, int> map) {
	for (auto& x : map) {
		cout << x.first << ": " << x.second - 1 << '\n';
	}
}

int main(void) {
	int n, m;
	int u, v;
	int sourceCount, factoryCount;

	cin >> n >> m >> sourceCount >> factoryCount;
	Graph graph = Graph(n, factoryCount);

	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		graph.insert(u, v);
	}

	for (int i = 0; i < sourceCount; i++) {
		cin >> u;
		graph.addSource(u);
	}

	for (int i = 0; i < factoryCount; i++) {
		cin >> u;
		graph.addFactory(u);
	}

	graph.showShipmentCosts();

	return 0;
}
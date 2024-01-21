#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

void display(unordered_map<int, unordered_set<int>> map) {
	for (auto outer : map) {
		cout << outer.first << ": ";
		for (auto inner : outer.second) {
			cout << inner << " ";
		}
		cout << '\n';
	}
}

class Map {
public:
	vector<vector<int>> grid;
	vector<vector<int>> uid;
	int sizeX, sizeY;

	Map(int x, int y) {
		sizeX = x;
		sizeY = y;
		grid = vector<vector<int>>(sizeY, vector<int>(sizeX));
		uid = vector<vector<int>>(sizeY, vector<int>(sizeX));
		
		int curUID = 0;
		for (int i = 0; i < sizeY; i++) {
			for (int j = 0; j < sizeX; j++) {
				uid[i][j] = curUID;
				curUID++;
			}
		}
	}

	bool isOOB(int x, int y) {
		if ((x < 0) || (x >= sizeX)) return true;
		if ((y < 0) || (y >= sizeY)) return true;
		return false;
	}

	int getUID(int x, int y) {
		if (isOOB(x, y)) return -1;
		return uid[y][x];
	}

	pair<int, int> fromUID(int uid) {
		return { uid % sizeX, uid / sizeX };
	}

	unordered_map<int, unordered_set<int>> getConnections() {
		unordered_map<int, unordered_set<int>> border;

		for (int y = 0; y < sizeY; y++) {
			for (int x = 0; x < sizeX; x++) {
				int country = grid[y][x];

				for (auto neighbor : getNeighbors(x, y)) {
					if (neighbor == -1) continue;

					auto pos = fromUID(neighbor);
					int curX = pos.first;
					int curY = pos.second;

					int neighborCountry = grid[curY][curX];
					if (country != neighborCountry) {
						border[country].insert(neighborCountry);
						border[neighborCountry].insert(country);
					}
				}
			}
		}
		// display(border);
		return border;
	}

	void show() {
		for (auto y : grid) {
			for (auto x : y) {
				cout << x << " ";
			}
			cout << '\n';
		}
	}

private:
	vector<int> getNeighbors(int x, int y) {
		vector<int> neighbors { getUID(x + 1, y), getUID(x - 1, y), getUID(x, y - 1), getUID(x, y + 1) };
		return neighbors;
	}
};

void bfs(unordered_map<int, unordered_set<int>> graph, int start, int goal) {
	queue<int> queue;
	unordered_map<int, int> visited;

	queue.push(start);
	visited.insert({ start, 0 });

	while (!queue.empty()) {
		auto front = queue.front();
		queue.pop();

		if (front == goal) {
			cout << visited[front] << '\n';
			return;
		}

		for (auto neighbor : graph[front]) {
			if (visited.find(neighbor) != visited.end()) continue;
			
			queue.push(neighbor);
			visited.insert({ neighbor, visited[front] + 1 });
		}
	}
}

int main(void) {

	int rows, columns;
	cin >> rows >> columns;

	int startX, startY, goalX, goalY;
	cin >> startX >> startY >> goalX >> goalY;

	Map map = Map(columns, rows);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cin >> map.grid[i][j];
		}
	}
	// cout << '\n';

	int startCountry = map.grid[startX - 1][startY - 1];
	int goalCountry = map.grid[goalX - 1][goalY - 1];

	// map.show();
	// cout << startCountry << " " << goalCountry << '\n';
	bfs(map.getConnections(), startCountry, goalCountry);

	return 0;
}

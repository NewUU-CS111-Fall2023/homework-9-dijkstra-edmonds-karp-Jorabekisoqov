#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>

class Problem4 {
private:
    std::unordered_map<int, std::vector<std::pair<int, int>>> graph;
    int n; // Number of nodes

public:
    Problem4(int nodes) : n(nodes) {}

    void addEdge(int u, int v, int w) {
        graph[u].emplace_back(v, w);
    }

    int minimumTime(int k) {
        std::vector<int> dist(n + 1, INT_MAX); // Initialize distances with infinity
        dist[k] = 0;

        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        pq.push({0, k});

        while (!pq.empty()) {
            int curDist = pq.top().first;
            int curNode = pq.top().second;
            pq.pop();

            for (const auto& neighbor : graph[curNode]) {
                int nextNode = neighbor.first;
                int weight = neighbor.second;

                if (curDist + weight < dist[nextNode]) {
                    dist[nextNode] = curDist + weight;
                    pq.push({dist[nextNode], nextNode});
                }
            }
        }

        int maxTime = *std::max_element(dist.begin() + 1, dist.end());

        return (maxTime == INT_MAX) ? -1 : maxTime;
    }
};
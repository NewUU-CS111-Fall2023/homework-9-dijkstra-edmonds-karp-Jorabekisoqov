#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>

class Problem5 {
private:
    std::unordered_map<int, std::vector<std::pair<int, int>>> graph;
    int n; // Number of cities

public:
    Problem5(int cities) : n(cities) {}

    void addFlight(int from, int to, int price) {
        graph[from].emplace_back(to, price);
    }

    int findCheapestPrice(int src, int dst, int k) {
        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<std::vector<int>>> pq;
        pq.push({0, src, k + 1}); // {cost, node, remaining stops}

        while (!pq.empty()) {
            auto current = pq.top();
            pq.pop();

            int currentCost = current[0];
            int currentNode = current[1];
            int stops = current[2];

            if (currentNode == dst) {
                return currentCost;
            }

            if (stops > 0) {
                for (const auto& neighbor : graph[currentNode]) {
                    int nextNode = neighbor.first;
                    int costToNextNode = neighbor.second;

                    pq.push({currentCost + costToNextNode, nextNode, stops - 1});
                }
            }
        }

        return -1;
    }
};
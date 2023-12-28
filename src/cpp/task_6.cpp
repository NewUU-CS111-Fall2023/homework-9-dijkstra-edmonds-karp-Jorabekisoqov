#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>

class Problem6 {
private:
    std::unordered_map<int, std::vector<std::tuple<int, int, int, int>>> graph;
    int n; // Number of cities

public:
    Problem6(int cities) : n(cities) {}

    void addFlight(int from, int to, int distance, int ars) {
        graph[from].emplace_back(to, distance, ars, 0); // The last value represents fuel
    }

    int findShortestPath(int src, int dst, int k, int initialFuel) {
        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<std::vector<int>>> pq;
        pq.push({0, src, k + 1, initialFuel});

        while (!pq.empty()) {
            auto current = pq.top();
            pq.pop();

            int currentCost = current[0];
            int currentNode = current[1];
            int stops = current[2];
            int currentFuel = current[3];

            if (currentNode == dst) {
                return currentCost;
            }

            if (stops > 0) {
                for (const auto& flight : graph[currentNode]) {
                    int nextNode = std::get<0>(flight);
                    int distance = std::get<1>(flight);
                    int ars = std::get<2>(flight);
                    int fuel = std::get<3>(flight);

                    if (currentFuel >= distance) {
                        int newFuel = currentFuel - distance + ars;
                        pq.push({currentCost + distance, nextNode, stops - 1, newFuel});
                    }
                }
            }
        }

        return -1;
    }
};
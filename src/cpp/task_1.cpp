/*
 * Author:
 * Date:
 * Name:
 */

class Problem1 {
private:
    std::vector<std::vector<std::pair<int, T>>> graph;
    int vertices;

public:
    Problem1(int n) : vertices(n), graph(n) {}

    void addEdge(int u, int v, T weight) {
        graph[u].emplace_back(v, weight);
        graph[v].emplace_back(u, weight); // Assuming undirected graph
    }

    std::vector<T> dijkstra(int start) {
        std::vector<T> dist(vertices, std::numeric_limits<T>::max());
        dist[start] = 0;

        std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, std::greater<std::pair<T, int>>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            T curDist = pq.top().first;
            int curNode = pq.top().second;
            pq.pop();

            if (curDist > dist[curNode]) {
                continue; // Skip if we already have a shorter path to this node
            }

            for (const auto& neighbor : graph[curNode]) {
                int nextNode = neighbor.first;
                T weight = neighbor.second;

                if (curDist + weight < dist[nextNode]) {
                    dist[nextNode] = curDist + weight;
                    pq.push({dist[nextNode], nextNode});
                }
            }
        }

        return dist;
    }
};
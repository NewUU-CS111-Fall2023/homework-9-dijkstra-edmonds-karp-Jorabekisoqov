#include <iostream>
#include <vector>
#include <queue>
#include <climits>

struct Edge {
    int to;
    int capacity;
    int flow;
};

class Problem2 {
private:
    std::vector<std::vector<Edge>> graph;
    int source, sink;

public:
    Problem2(int n) : graph(n), source(0), sink(n - 1) {}

    void addEdge(int from, int to, int capacity) {
        Edge forwardEdge{to, capacity, 0};
        Edge backwardEdge{from, 0, 0}; 
        graph[from].push_back(forwardEdge);
        graph[to].push_back(backwardEdge);
    }

    int edmondsKarp() {
        int maxFlow = 0;
        std::vector<int> pred(graph.size(), -1);

        while (bfs()) {
            int pathFlow = INT_MAX;
            for (int v = sink; v != source; v = pred[v]) {
                int u = pred[v];
                for (auto& edge : graph[u]) {
                    if (edge.to == v) {
                        pathFlow = std::min(pathFlow, edge.capacity - edge.flow);
                        break;
                    }
                }
            }

            for (int v = sink; v != source; v = pred[v]) {
                int u = pred[v];
                for (auto& edge : graph[u]) {
                    if (edge.to == v) {
                        edge.flow += pathFlow;
                        break;
                    }
                }

                for (auto& edge : graph[v]) {
                    if (edge.to == u) {
                        edge.flow -= pathFlow;
                        break;
                    }
                }
            }

            maxFlow += pathFlow;
        }

        return maxFlow;
    }

private:
    bool bfs() {
        std::queue<int> q;
        q.push(source);

        std::vector<int> pred(graph.size(), -1);

        while (!q.empty() && pred[sink] == -1) {
            int cur = q.front();
            q.pop();

            for (const auto& edge : graph[cur]) {
                if (pred[edge.to] == -1 && edge.to != source && edge.capacity > edge.flow) {
                    pred[edge.to] = cur;
                    q.push(edge.to);
                }
            }
        }

        return pred[sink] != -1;
    }
};
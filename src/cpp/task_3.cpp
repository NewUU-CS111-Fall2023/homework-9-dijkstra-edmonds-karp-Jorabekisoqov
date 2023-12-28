#include <iostream>
#include <vector>
#include <queue>

class Problem3 {
private:
    std::vector<std::vector<char>> maze;
    int rows, cols;
    std::vector<std::vector<int>> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Up, Down, Left, Right

public:
    Problem3(const std::vector<std::string>& input) {
        rows = input.size();
        cols = input[0].size();
        maze.resize(rows, std::vector<char>(cols));

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                maze[i][j] = input[i][j];
            }
        }
    }

    int shortestPath() {
        std::vector<std::vector<int>> distance(rows, std::vector<int>(cols, -1));
        std::queue<std::pair<int, int>> q;

        // Find the starting point
        int startX, startY;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (maze[i][j] == 'S') {
                    startX = i;
                    startY = j;
                    break;
                }
            }
        }

        q.push({startX, startY});
        distance[startX][startY] = 0;

        while (!q.empty()) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();

            for (const auto& dir : directions) {
                int nx = x + dir[0];
                int ny = y + dir[1];

                if (isValid(nx, ny) && maze[nx][ny] == '.' && distance[nx][ny] == -1) {
                    distance[nx][ny] = distance[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }

        // Find the exit
        int exitX, exitY;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (maze[i][j] == 'E') {
                    exitX = i;
                    exitY = j;
                    break;
                }
            }
        }

        return distance[exitX][exitY];
    }

private:
    bool isValid(int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols;
    }
};
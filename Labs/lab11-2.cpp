#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Define a structure to represent a chessboard coordinate
struct Coordinate {
    int x, y;
    Coordinate(int x, int y) : x(x), y(y) {}
};

// Define all possible knight moves relative to the current position
int knight_moves[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

// Check if the given coordinates are valid on the 8x8 chessboard
bool isValid(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

// Function to find the shortest path from start to target using BFS
vector<Coordinate> findShortestPath(const Coordinate& start, const Coordinate& target) {
    vector<Coordinate> path;
    queue<vector<Coordinate>> q;
    vector<vector<bool>> visited(8, vector<bool>(8, false));

    q.push({start});
    visited[start.x][start.y] = true;

    while (!q.empty()) {
        vector<Coordinate> currentPath = q.front();
        Coordinate current = currentPath.back();
        q.pop();

        if (current.x == target.x && current.y == target.y) {
            return currentPath;
        }

        for (int i = 0; i < 8; ++i) {
            int new_x = current.x + knight_moves[i][0];
            int new_y = current.y + knight_moves[i][1];
            if (isValid(new_x, new_y) && !visited[new_x][new_y]) {
                visited[new_x][new_y] = true;
                vector<Coordinate> newPath = currentPath;
                newPath.push_back({new_x, new_y});
                q.push(newPath);
            }
        }
    }

    // If no path is found, return an empty path
    return path;
}

int main() {
    int startX, startY, targetX, targetY;
    cout << "Enter the starting coordinates (e.g., 'x y'): ";
    cin >> startX >> startY;
    cout << "Enter the target coordinates (e.g., 'x y'): ";
    cin >> targetX >> targetY;

    Coordinate start(startX, startY);
    Coordinate target(targetX, targetY);

    vector<Coordinate> path = findShortestPath(start, target);

    if (!path.empty()) {
        cout << "The simplest path is:" << endl;
        for (const Coordinate& coord : path) {
            cout << coord.x << " " << coord.y << endl;
        }
        cout << "Total number of moves: " << path.size() - 1 << endl;
    } else {
        cout << "No valid path found." << endl;
    }

    return 0;
}

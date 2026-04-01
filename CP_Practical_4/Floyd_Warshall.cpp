#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>

const int INF = std::numeric_limits<int>::max() / 2;

class FloydWarshall {
public:
    int n;
    std::vector<std::vector<int>> dist;
    std::vector<std::vector<int>> next;

    FloydWarshall(int vertices) : n(vertices),
        dist(vertices, std::vector<int>(vertices, INF)),
        next(vertices, std::vector<int>(vertices, -1)) {
        for (int i = 0; i < n; i++)
            dist[i][i] = 0;
    }

    void addEdge(int u, int v, int weight) {
        dist[u][v] = weight;
        next[u][v] = v;
    }

    // Core algorithm: O(V^3)
    // For each intermediate vertex k, try to improve dist[i][j]
    // via the path i -> ... -> k -> ... -> j
    bool solve() {
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF &&
                        dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
        // Negative cycle: any node i where dist[i][i] < 0
        for (int i = 0; i < n; i++)
            if (dist[i][i] < 0) return false;
        return true;
    }

    // Reconstruct shortest path from u to v using next[][] matrix
    std::vector<int> getPath(int u, int v) {
        if (next[u][v] == -1) return {};
        std::vector<int> path;
        path.push_back(u);
        while (u != v) {
            u = next[u][v];
            path.push_back(u);
        }
        return path;
    }

    void printDistMatrix() const {
        std::cout << "\n=== All-Pairs Shortest Path Distance Matrix ===\n";
        std::cout << "     ";
        for (int j = 0; j < n; j++)
            std::cout << std::setw(6) << j;
        std::cout << "\n";
        for (int i = 0; i < n; i++) {
            std::cout << std::setw(4) << i << " ";
            for (int j = 0; j < n; j++) {
                if (dist[i][j] == INF)
                    std::cout << std::setw(6) << "INF";
                else
                    std::cout << std::setw(6) << dist[i][j];
            }
            std::cout << "\n";
        }
    }
};

int main() {
    std::cout << "=== Floyd-Warshall Algorithm ===\n";
    std::cout << "Graph (directed, 4 vertices):\n";
    std::cout << "  0->1 (3), 0->3 (7)\n";
    std::cout << "  1->0 (8), 1->2 (2)\n";
    std::cout << "  2->0 (5), 2->3 (1)\n";
    std::cout << "  3->0 (2)\n";

    FloydWarshall fw(4);
    fw.addEdge(0, 1, 3);
    fw.addEdge(0, 3, 7);
    fw.addEdge(1, 0, 8);
    fw.addEdge(1, 2, 2);
    fw.addEdge(2, 0, 5);
    fw.addEdge(2, 3, 1);
    fw.addEdge(3, 0, 2);

    if (!fw.solve()) {
        std::cout << "\nNegative cycle detected — no solution.\n";
        return 1;
    }

    fw.printDistMatrix();

    // Print all-pairs paths
    std::cout << "\n=== Shortest Paths ===\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) continue;
            std::cout << i << " -> " << j << ": ";
            if (fw.dist[i][j] == INF) {
                std::cout << "unreachable\n";
                continue;
            }
            auto path = fw.getPath(i, j);
            for (int k = 0; k < (int)path.size(); k++) {
                std::cout << path[k];
                if (k + 1 < (int)path.size()) std::cout << " -> ";
            }
            std::cout << "  (cost: " << fw.dist[i][j] << ")\n";
        }
    }

    // Negative-cycle detection test
    std::cout << "\n=== Negative Cycle Test ===\n";
    FloydWarshall fwNeg(3);
    fwNeg.addEdge(0, 1,  1);
    fwNeg.addEdge(1, 2, -3);
    fwNeg.addEdge(2, 0,  1); // cycle 0->1->2->0 has weight -1
    if (!fwNeg.solve())
        std::cout << "Correctly detected negative cycle.\n";

    return 0;
}

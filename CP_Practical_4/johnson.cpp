#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <limits>
#include <functional>

const int INF = std::numeric_limits<int>::max() / 2;

struct Edge {
    int to, weight;
};

class Johnson {
public:
    int n;
    std::vector<std::vector<Edge>> adj;
    std::vector<std::vector<int>> dist;

    Johnson(int vertices) : n(vertices), adj(vertices),
        dist(vertices, std::vector<int>(vertices, INF)) {}

    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
    }

    // Phase 1: Bellman-Ford from a virtual source (simulated by setting h[v]=0 for all v)
    // Computes potentials h[v] used to reweight edges to non-negative values.
    // Returns false if a negative-weight cycle is detected.
    bool bellmanFord(std::vector<int>& h) {
        h.assign(n, 0); // virtual source has 0-weight edge to every vertex

        for (int iter = 0; iter < n - 1; iter++) {
            bool updated = false;
            for (int u = 0; u < n; u++) {
                if (h[u] == INF) continue;
                for (const Edge& e : adj[u]) {
                    if (h[u] + e.weight < h[e.to]) {
                        h[e.to] = h[u] + e.weight;
                        updated = true;
                    }
                }
            }
            if (!updated) break;
        }

        // Negative cycle check: one more relaxation should change nothing
        for (int u = 0; u < n; u++)
            for (const Edge& e : adj[u])
                if (h[u] + e.weight < h[e.to]) return false;

        return true;
    }

    // Phase 2: Dijkstra on reweighted graph from source src
    // Reweighted edge: w'(u,v) = w(u,v) + h[u] - h[v]  (always >= 0)
    std::vector<int> dijkstra(int src, const std::vector<int>& h) {
        std::vector<int> d(n, INF);
        d[src] = 0;

        std::priority_queue<std::pair<int,int>,
                            std::vector<std::pair<int,int>>,
                            std::greater<std::pair<int,int>>> pq;
        pq.push(std::make_pair(0, src));

        while (!pq.empty()) {
            int du = pq.top().first;
            int u  = pq.top().second;
            pq.pop();

            if (du > d[u]) continue;

            for (const Edge& e : adj[u]) {
                int w_prime = e.weight + h[u] - h[e.to];
                if (d[u] + w_prime < d[e.to]) {
                    d[e.to] = d[u] + w_prime;
                    pq.push(std::make_pair(d[e.to], e.to));
                }
            }
        }
        return d;
    }

    // Main solve: O(V^2 log V + VE)
    // 1. Reweight via Bellman-Ford
    // 2. Run Dijkstra from every vertex
    // 3. Restore true distances: dist(s,v) = d'(s,v) + h[v] - h[s]
    bool solve() {
        std::vector<int> h;
        if (!bellmanFord(h)) return false;

        for (int s = 0; s < n; s++) {
            std::vector<int> d = dijkstra(s, h);
            for (int v = 0; v < n; v++) {
                dist[s][v] = (d[v] == INF) ? INF : d[v] + h[v] - h[s];
            }
        }
        return true;
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
    std::cout << "=== Johnson's Algorithm ===\n";
    std::cout << "Graph (directed, 4 vertices):\n";
    std::cout << "  0->1 (3), 0->3 (7)\n";
    std::cout << "  1->0 (8), 1->2 (2)\n";
    std::cout << "  2->0 (5), 2->3 (1)\n";
    std::cout << "  3->0 (2)\n";

    Johnson j(4);
    j.addEdge(0, 1, 3);
    j.addEdge(0, 3, 7);
    j.addEdge(1, 0, 8);
    j.addEdge(1, 2, 2);
    j.addEdge(2, 0, 5);
    j.addEdge(2, 3, 1);
    j.addEdge(3, 0, 2);

    if (!j.solve()) {
        std::cout << "\nNegative cycle detected — no solution.\n";
        return 1;
    }
    j.printDistMatrix();

    // Test with a negative-weight edge (no negative cycle)
    std::cout << "\n=== Negative Edge Test (edge 1->3 weight -4) ===\n";
    Johnson jneg(4);
    jneg.addEdge(0, 1,  3);
    jneg.addEdge(0, 3,  7);
    jneg.addEdge(1, 0,  8);
    jneg.addEdge(1, 2,  2);
    jneg.addEdge(1, 3, -4);
    jneg.addEdge(2, 0,  5);
    jneg.addEdge(2, 3,  1);
    jneg.addEdge(3, 0,  2);

    if (jneg.solve()) jneg.printDistMatrix();
    else std::cout << "Negative cycle detected.\n";

    // Negative cycle detection test
    std::cout << "\n=== Negative Cycle Test ===\n";
    Johnson jcyc(3);
    jcyc.addEdge(0, 1,  1);
    jcyc.addEdge(1, 2, -3);
    jcyc.addEdge(2, 0,  1);
    if (!jcyc.solve())
        std::cout << "Correctly detected negative cycle.\n";

    return 0;
}

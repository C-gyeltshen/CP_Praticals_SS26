#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

struct Edge {
    int u, v, weight;
};

// Union-Find (DSU) with path compression + union by rank
class DSU {
public:
    std::vector<int> parent, rank_;

    DSU(int n) : parent(n), rank_(n, 0) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // path compression
        return parent[x];
    }

    bool unite(int u, int v) {
        int pu = find(u), pv = find(v);
        if (pu == pv) return false;
        if (rank_[pu] < rank_[pv]) std::swap(pu, pv);
        parent[pv] = pu;
        if (rank_[pu] == rank_[pv]) rank_[pu]++;
        return true;
    }
};

class Boruvka {
public:
    int n;
    std::vector<Edge> edges;
    std::vector<Edge> mstEdges;
    long long mstWeight = 0;

    Boruvka(int vertices) : n(vertices) {}

    void addEdge(int u, int v, int weight) {
        edges.push_back({u, v, weight});
    }

    // Core algorithm: O(E log V)
    // Each phase finds the cheapest edge leaving every component,
    // adds those edges to the MST, and merges components.
    // At least half the components merge each phase => O(log V) phases total.
    long long solve() {
        DSU dsu(n);
        int components = n;
        mstWeight = 0;
        mstEdges.clear();

        while (components > 1) {
            // cheapest[i] = index into edges[] of the cheapest edge
            // leaving the component whose root is i. -1 = none found yet.
            std::vector<int> cheapest(n, -1);

            for (int i = 0; i < (int)edges.size(); i++) {
                int cu = dsu.find(edges[i].u);
                int cv = dsu.find(edges[i].v);
                if (cu == cv) continue; // same component, skip

                if (cheapest[cu] == -1 || edges[i].weight < edges[cheapest[cu]].weight)
                    cheapest[cu] = i;
                if (cheapest[cv] == -1 || edges[i].weight < edges[cheapest[cv]].weight)
                    cheapest[cv] = i;
            }

            // Merge components using the cheapest edges found
            for (int c = 0; c < n; c++) {
                if (cheapest[c] == -1) continue;
                int i = cheapest[c];
                int cu = dsu.find(edges[i].u);
                int cv = dsu.find(edges[i].v);
                if (cu == cv) continue; // already merged this phase

                dsu.unite(cu, cv);
                mstEdges.push_back(edges[i]);
                mstWeight += edges[i].weight;
                components--;
            }
        }
        return mstWeight;
    }

    void printMST() const {
        std::cout << "\n=== Minimum Spanning Tree ===\n";
        std::cout << "Edges:\n";
        for (const Edge& e : mstEdges)
            std::cout << "  " << e.u << " -- " << e.v << "  (weight: " << e.weight << ")\n";
        std::cout << "Total MST Weight: " << mstWeight << "\n";
    }
};

int main() {
    // Test 1: small textbook graph
    std::cout << "=== Boruvka's Algorithm ===\n";
    std::cout << "Graph (undirected, 4 vertices):\n";
    std::cout << "  0-1 (10), 0-2 (6), 0-3 (5), 1-3 (15), 2-3 (4)\n";
    std::cout << "Expected MST: 2-3(4), 0-3(5), 0-1(10)  =>  weight 19\n";

    Boruvka b1(4);
    b1.addEdge(0, 1, 10);
    b1.addEdge(0, 2,  6);
    b1.addEdge(0, 3,  5);
    b1.addEdge(1, 3, 15);
    b1.addEdge(2, 3,  4);
    b1.solve();
    b1.printMST();

    // Test 2: 5-vertex graph
    std::cout << "\nGraph (undirected, 5 vertices):\n";
    std::cout << "  0-1(2), 0-3(6), 1-2(3), 1-3(8), 1-4(5), 2-4(7), 3-4(9)\n";
    std::cout << "Expected MST weight: 16\n";

    Boruvka b2(5);
    b2.addEdge(0, 1, 2);
    b2.addEdge(0, 3, 6);
    b2.addEdge(1, 2, 3);
    b2.addEdge(1, 3, 8);
    b2.addEdge(1, 4, 5);
    b2.addEdge(2, 4, 7);
    b2.addEdge(3, 4, 9);
    b2.solve();
    b2.printMST();

    return 0;
}

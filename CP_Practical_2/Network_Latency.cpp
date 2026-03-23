#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef long long ll;
typedef pair<ll, int> pli; // {distance, node}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== Network Latency ===" << endl;

    int N, M;
    cout << "Enter N (routers) and M (cables): ";
    cin >> N >> M;

    // Adjacency list: adj[u] = { {v, weight}, ... }
    vector<vector<pair<int, ll>>> adj(N + 1);

    cout << "Enter " << M << " connections (u v latency):" << endl;
    for (int i = 0; i < M; i++) {
        int u, v;
        ll w;
        cout << "  Cable " << (i + 1) << ": ";
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // bidirectional
    }

    // ─── Dijkstra from node 1 ───────────────────────────────────────────────
    vector<ll> dist(N + 1, LLONG_MAX);
    priority_queue<pli, vector<pli>, greater<pli>> pq; // min-heap

    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        pli top = pq.top();
        pq.pop();
        ll d = top.first;
        int u = top.second;

        // Skip if we already found a shorter path to u
        if (d > dist[u]) continue;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            ll w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    // ─── Output ─────────────────────────────────────────────────────────────
    cout << "\nMinimum latency from router 1 to router " << N << ": ";
    if (dist[N] == LLONG_MAX)
        cout << -1 << " (no path exists)" << endl;
    else
        cout << dist[N] << endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// ─── Segment Tree (Range Max + Point Update) ───────────────────────────────
struct SegTree {
    int n;
    vector<long long> tree;

    SegTree(int n) : n(n), tree(2 * n, LLONG_MIN) {}

    // Build from array
    void build(const vector<long long>& A) {
        for (int i = 0; i < n; i++)
            tree[n + i] = A[i];
        for (int i = n - 1; i >= 1; i--)
            tree[i] = max(tree[2 * i], tree[2 * i + 1]);
    }

    // Point update: set A[pos] = val (0-indexed)
    void update(int pos, long long val) {
        pos += n;
        tree[pos] = val;
        for (pos >>= 1; pos >= 1; pos >>= 1)
            tree[pos] = max(tree[2 * pos], tree[2 * pos + 1]);
    }

    // Range max query [l, r] inclusive (0-indexed)
    long long query(int l, int r) {
        long long res = LLONG_MIN;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = max(res, tree[l++]);
            if (r & 1) res = max(res, tree[--r]);
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== Maximum in Sliding Window with Updates ===" << endl;
    cout << "Enter N (array size), K (window size), Q (queries): ";

    int N, K, Q;
    cin >> N >> K >> Q;

    vector<long long> A(N);
    cout << "Enter " << N << " integers: ";
    for (int i = 0; i < N; i++) cin >> A[i];

    SegTree seg(N);
    seg.build(A);

    cout << "\nEnter " << Q << " queries:" << endl;
    cout << "  Type 1 (update): 1 pos val  (0-indexed pos)" << endl;
    cout << "  Type 2 (query):  2 i        (window [i-K+1 .. i], 0-indexed)" << endl;
    cout << endl;

    for (int q = 0; q < Q; q++) {
        int type;
        cout << "Query " << (q + 1) << ": ";
        cin >> type;

        if (type == 1) {
            // Update A[pos] = val
            int pos;
            long long val;
            cin >> pos >> val;
            seg.update(pos, val);
            cout << "  → Updated A[" << pos << "] = " << val << endl;

        } else {
            // Query max in window of size K ending at index i
            int i;
            cin >> i;

            if (i < K - 1) {
                cout << "  → Error: window [" << (i - K + 1) << ".." << i 
                     << "] goes out of bounds (need i >= " << (K - 1) << ")" << endl;
            } else {
                int l = i - K + 1;
                long long result = seg.query(l, i);
                cout << "  → Max in window [" << l << ".." << i << "] = " << result << endl;
            }
        }
    }

    cout << "\n=== All queries completed ===" << endl;
    return 0;
}

#include <iostream>
#include <queue>   // priority_queue
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    priority_queue<int> maxHeap; // max-heap by default

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        maxHeap.push(x);
    }

    // Extract top K elements
    for (int i = 0; i < k; i++) {
        cout << maxHeap.top();
        maxHeap.pop();
        if (i != k - 1) cout << " ";
    }
    cout << "\n";

    return 0;
}

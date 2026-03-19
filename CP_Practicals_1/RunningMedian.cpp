#include <iostream>
#include <queue>    // priority_queue
#include <iomanip>  // fixed, setprecision
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Max-heap for lower half
    priority_queue<int> lower;
    // Min-heap for upper half
    priority_queue<int, vector<int>, greater<int>> upper;

    int n;
    cin >> n;

    cout << fixed << setprecision(1);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        // Step 1: Add to appropriate heap
        if (lower.empty() || x <= lower.top()) {
            lower.push(x);
        } else {
            upper.push(x);
        }

        // Step 2: Balance the heaps (size difference <= 1)
        if (lower.size() > upper.size() + 1) {
            upper.push(lower.top());
            lower.pop();
        } else if (upper.size() > lower.size()) {
            lower.push(upper.top());
            upper.pop();
        }

        // Step 3: Compute and print the running median
        if (lower.size() == upper.size()) {
            // Even total: average of both tops
            cout << (lower.top() + upper.top()) / 2.0 << "\n";
        } else {
            // Odd total: lower always has one more element
            cout << (double)lower.top() << "\n";
        }
    }

    return 0;
}

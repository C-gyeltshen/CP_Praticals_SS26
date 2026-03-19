#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Deque stores indices of useful elements (in decreasing order of value)
    deque<int> dq;
    vector<int> result;

    for (int i = 0; i < n; i++) {
        // Remove indices that are out of the current window
        while (!dq.empty() && dq.front() < i - k + 1) {
            dq.pop_front();
        }

        // Remove from back all indices whose values are <= arr[i]
        // They can never be the maximum for any future window
        while (!dq.empty() && arr[dq.back()] <= arr[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        // Window is fully formed starting from index k-1
        if (i >= k - 1) {
            result.push_back(arr[dq.front()]);
        }
    }

    for (int i = 0; i < (int)result.size(); i++) {
        cout << result[i];
        if (i != (int)result.size() - 1) cout << " ";
    }
    cout << "\n";

    return 0;
}

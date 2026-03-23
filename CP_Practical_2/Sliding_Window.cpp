#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== Sliding Window Maximum ===" << endl;

    int N, K;
    cout << "Enter N (array size) and K (window size): ";
    cin >> N >> K;

    vector<long long> A(N);
    cout << "Enter " << N << " integers: ";
    for (int i = 0; i < N; i++) cin >> A[i];

    if (K > N) {
        cout << "Error: K cannot be greater than N." << endl;
        return 0;
    }

    // Monotonic deque stores indices
    // Front = index of the maximum element in current window
    // Deque is always in decreasing order of A values
    deque<int> dq;

    cout << "\nMaximum of each window of size " << K << ":" << endl;

    for (int i = 0; i < N; i++) {
        // 1. Remove indices that are out of the current window
        while (!dq.empty() && dq.front() < i - K + 1) {
            dq.pop_front();
        }

        // 2. Remove from back all indices whose values are <= A[i]
        //    (they can never be the maximum while A[i] is in the window)
        while (!dq.empty() && A[dq.back()] <= A[i]) {
            dq.pop_back();
        }

        // 3. Add current index
        dq.push_back(i);

        // 4. Once we have our first full window, record the maximum
        if (i >= K - 1) {
            cout << A[dq.front()];
            if (i < N - 1) cout << " ";
        }
    }

    cout << endl;
    cout << "\nTotal windows: " << (N - K + 1) << endl;

    return 0;
}

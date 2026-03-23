#include <iostream>
#include <vector>
using namespace std;

// Check if there exists a subarray of length K
// where all elements have all bits of 'candidate' set
bool hasValidSubarray(const vector<int>& A, int K, int candidate) {
    int count = 0;
    for (int i = 0; i < (int)A.size(); i++) {
        // Check if current element has all bits of candidate set
        if ((A[i] & candidate) == candidate) {
            count++;
            if (count >= K) return true; // found K consecutive valid elements
        } else {
            count = 0; // reset streak
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cout << "=== Maximum AND Subarray ===" << endl;
    cout << "Enter number of test cases (1-10): ";
    cin >> T;

    int caseNum = 1;
    while (T--) {
        cout << "\n--- Test Case " << caseNum++ << " ---" << endl;

        int N, K;
        cout << "Enter N (array size) and K (subarray length): ";
        cin >> N >> K;

        vector<int> A(N);
        cout << "Enter " << N << " integers: ";
        for (int i = 0; i < N; i++) cin >> A[i];

        // Greedily build the answer bit by bit from MSB to LSB
        int answer = 0;
        for (int bit = 29; bit >= 0; bit--) {
            int candidate = answer | (1 << bit);
            if (hasValidSubarray(A, K, candidate)) {
                answer = candidate; // safely set this bit
            }
        }

        cout << "Maximum AND value of any subarray of length " << K << ": " << answer << endl;
    }

    cout << "\n=== All test cases completed ===" << endl;
    return 0;
}

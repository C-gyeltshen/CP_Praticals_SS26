#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cout << "=== Dinner Table Arrangement ===" << endl;
    cout << "Enter number of test cases: ";
    cin >> T;

    int caseNum = 1;
    while (T--) {
        cout << "\n--- Test Case " << caseNum++ << " ---" << endl;

        int N;
        cout << "Enter number of friends (1-20): ";
        cin >> N;

        vector<int> allergy(N, 0);
        for (int i = 0; i < N; i++) {
            int M;
            cout << "Friend " << (i + 1) << " - Enter number of allergies: ";
            cin >> M;
            if (M > 0) {
                cout << "Friend " << (i + 1) << " - Enter " << M << " allergy ID(s) (1-30): ";
                for (int j = 0; j < M; j++) {
                    int id;
                    cin >> id;
                    allergy[i] |= (1 << (id - 1));
                }
            }
        }

        // Edge case: only 1 person
        if (N == 1) {
            cout << "\nResult: YES (only one person, no adjacency conflict)" << endl;
            continue;
        }

        auto compatible = [&](int i, int j) {
            return (allergy[i] & allergy[j]) == 0;
        };

        int FULL = (1 << N) - 1;
        vector<vector<bool>> dp(1 << N, vector<bool>(N, false));

        // Fix friend 0 at the first seat to avoid counting rotations
        dp[1][0] = true;

        for (int mask = 1; mask < (1 << N); mask++) {
            for (int last = 0; last < N; last++) {
                if (!dp[mask][last]) continue;
                if (!(mask & (1 << last))) continue;

                for (int next = 1; next < N; next++) {
                    if (mask & (1 << next)) continue;
                    if (!compatible(last, next)) continue;
                    dp[mask | (1 << next)][next] = true;
                }
            }
        }

        // Check if the circle can be closed
        bool found = false;
        for (int last = 1; last < N; last++) {
            if (dp[FULL][last] && compatible(last, 0)) {
                found = true;
                break;
            }
        }

        cout << "\nResult: " << (found ? "YES - A valid seating arrangement exists!" 
                                       : "NO - No valid seating arrangement possible.") << endl;
    }

    cout << "\n=== All test cases completed ===" << endl;
    return 0;
}

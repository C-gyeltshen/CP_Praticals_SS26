#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== Shortest Path with Toll Booths ===" << endl;

    int N, K;
    long long M;
    cout << "Enter N (number of booths), M (starting coins), K (max skips): ";
    cin >> N >> M >> K;

    vector<long long> toll(N + 1);
    cout << "Enter " << N << " toll values (toll[1] to toll[" << N << "]): ";
    for (int i = 1; i <= N; i++) cin >> toll[i];

    // dp[i][j] = min time to reach booth i having used j skips
    // coins[i][j] = coins remaining at state (i, j)
    // We use INF to mark unreachable states
    const long long INF = LLONG_MAX / 2;

    // dp and coins arrays: size (N+1) x (K+1)
    vector<vector<long long>> dp(N + 1, vector<long long>(K + 1, INF));
    vector<vector<long long>> coins(N + 1, vector<long long>(K + 1, -1));

    // Start at booth 1 with M coins, 0 skips used, 0 time elapsed
    dp[1][0] = 0;
    coins[1][0] = M;

    for (int i = 1; i < N; i++) {
        for (int j = 0; j <= K; j++) {
            if (dp[i][j] == INF) continue; // unreachable state

            long long curTime  = dp[i][j];
            long long curCoins = coins[i][j];

            // ── Option 1: PAY toll[i] and move to booth i+1 (1 minute) ──
            if (curCoins >= toll[i]) {
                long long newTime  = curTime + 1;
                long long newCoins = curCoins - toll[i];

                // Update if this is better time, or same time with more coins
                if (newTime < dp[i + 1][j] ||
                   (newTime == dp[i + 1][j] && newCoins > coins[i + 1][j])) {
                    dp[i + 1][j]    = newTime;
                    coins[i + 1][j] = newCoins;
                }
            }

            // ── Option 2: SKIP booth i and move to i+1 (2 minutes, use 1 skip) ──
            if (j < K) {
                long long newTime  = curTime + 2;
                long long newCoins = curCoins; // no coin cost for skipping

                if (newTime < dp[i + 1][j + 1] ||
                   (newTime == dp[i + 1][j + 1] && newCoins > coins[i + 1][j + 1])) {
                    dp[i + 1][j + 1]    = newTime;
                    coins[i + 1][j + 1] = newCoins;
                }
            }
        }
    }

    // Find minimum time to reach booth N across all skip counts
    long long ans = INF;
    for (int j = 0; j <= K; j++) {
        if (dp[N][j] < ans) {
            ans = dp[N][j];
        }
    }

    cout << "\nResult: ";
    if (ans == INF)
        cout << -1 << " (impossible to reach booth " << N << ")" << endl;
    else
        cout << "Minimum time to reach booth " << N << " = " << ans << " minutes" << endl;

    return 0;
}

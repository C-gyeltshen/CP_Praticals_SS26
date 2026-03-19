#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int totalSubsets = (1 << n); // 2^n subsets

    for (int mask = 0; mask < totalSubsets; mask++) {
        cout << "{";
        bool first = true;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) { // Check if i-th bit is set
                if (!first) cout << " ";
                cout << arr[i];
                first = false;
            }
        }
        cout << "}\n";
    }

    return 0;
}

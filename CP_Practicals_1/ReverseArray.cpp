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

    // Reverse traversal
    for (int i = n - 1; i >= 0; i--) {
        cout << arr[i];
        if (i != 0) cout << " ";
    }
    cout << "\n";

    return 0;
}

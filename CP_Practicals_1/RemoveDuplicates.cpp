#include <iostream>
#include <vector>
#include <algorithm>  // sort, unique
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

    // Sort first, then use unique to remove consecutive duplicates
    sort(arr.begin(), arr.end());
    auto it = unique(arr.begin(), arr.end());
    arr.erase(it, arr.end());

    for (int i = 0; i < (int)arr.size(); i++) {
        cout << arr[i];
        if (i != (int)arr.size() - 1) cout << " ";
    }
    cout << "\n";

    return 0;
}

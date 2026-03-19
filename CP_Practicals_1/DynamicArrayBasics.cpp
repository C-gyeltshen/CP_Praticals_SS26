#include <iostream>
#include <vector>
#include <algorithm>  // max_element, min_element
#include <numeric>    // accumulate
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

    int maxVal = *max_element(arr.begin(), arr.end());
    int minVal = *min_element(arr.begin(), arr.end());
    long long sum = 0;
    for (int x : arr) sum += x;

    cout << "Maximum: " << maxVal << "\n";
    cout << "Minimum: " << minVal << "\n";
    cout << "Sum: " << sum << "\n";

    return 0;
}

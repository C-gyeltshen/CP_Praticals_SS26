#include <iostream>
#include <deque>
#include <string>
using namespace std;

void printDeque(const deque<int>& dq) {
    cout << "[";
    for (int i = 0; i < (int)dq.size(); i++) {
        cout << dq[i];
        if (i != (int)dq.size() - 1) cout << ", ";
    }
    cout << "]\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    deque<int> dq;
    int q;
    cin >> q;

    while (q--) {
        string op;
        cin >> op;

        if (op == "push_front") {
            int x;
            cin >> x;
            dq.push_front(x);
        } else if (op == "push_back") {
            int x;
            cin >> x;
            dq.push_back(x);
        } else if (op == "pop_front") {
            if (!dq.empty()) dq.pop_front();
            else cout << "Deque is empty!\n";
        } else if (op == "pop_back") {
            if (!dq.empty()) dq.pop_back();
            else cout << "Deque is empty!\n";
        }

        printDeque(dq);
    }

    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// ─────────────────────────────────────────────
//  Manacher's Algorithm
// ─────────────────────────────────────────────
class Manacher {
public:
    string original;
    string transformed;      // e.g. "#a#b#b#a#"
    vector<int> p;           // p[i] = palindrome radius at index i in transformed

    Manacher(const string& s) : original(s) {
        buildTransformed();
        compute();
    }

private:
    // ── Step 1: Transform ───────────────────
    void buildTransformed() {
        transformed = "#";
        for (char c : original) {
            transformed += c;
            transformed += '#';
        }
        // transformed.size() = 2*n + 1
    }

    // ── Step 2: Core Algorithm ───────────────
    void compute() {
        int n = (int)transformed.size();
        p.assign(n, 0);

        int C = 0;  // center of rightmost palindrome
        int R = 0;  // right boundary (exclusive: R = C + p[C] + 1)

        for (int i = 0; i < n; i++) {
            // Mirror of i around C
            int mirror = 2 * C - i;

            if (i < R) {
                // Use mirror's radius, but cap at distance to boundary
                p[i] = min(R - i, p[mirror]);
            }
            // p[i] is now a lower bound; try to expand

            int left  = i - (p[i] + 1);
            int right = i + (p[i] + 1);

            while (left >= 0 && right < n && transformed[left] == transformed[right]) {
                p[i]++;
                left--;
                right++;
            }

            // Update C and R if this palindrome extends beyond R
            if (i + p[i] > R) {
                C = i;
                R = i + p[i];
            }
        }
    }

public:
    // ── Find Longest Palindromic Substring ──
    string longestPalindrome() {
        int maxLen = 0, center = 0;
        for (int i = 0; i < (int)p.size(); i++) {
            if (p[i] > maxLen) {
                maxLen = p[i];
                center = i;
            }
        }
        // Map back to original indices:
        // center in transformed corresponds to (center-1)/2 in original (approximately)
        // start = (center - maxLen) / 2
        int start = (center - maxLen) / 2;
        return original.substr(start, maxLen);
    }

    // ── Find ALL Palindromic Substrings ─────
    // Returns every distinct palindrome (deduplicated by position)
    vector<string> allPalindromes() {
        vector<string> result;
        for (int i = 0; i < (int)p.size(); i++) {
            if (p[i] > 0) {
                int start = (i - p[i]) / 2;
                int len   = p[i];
                result.push_back(original.substr(start, len));
            }
        }
        return result;
    }

    // ── Count Palindromic Substrings ────────
    // Each position i contributes floor((p[i]+1)/1) palindromes
    // (both odd and even length already handled by transformation)
    int countPalindromes() {
        int count = 0;
        for (int r : p) count += (r + 1) / 2;   // number of palindromes centered here
        return count;
    }

    // ── Print Diagnostic Table ───────────────
    void printTable() {
        cout << "\nTransformed string:\n  ";
        for (int i = 0; i < (int)transformed.size(); i++)
            cout << transformed[i] << " ";
        cout << "\n  ";
        for (int i = 0; i < (int)p.size(); i++)
            cout << p[i] << " ";
        cout << "\n";
    }
};

// ─────────────────────────────────────────────
//  Driver
// ─────────────────────────────────────────────
int main() {
    cout << "\n══════════════════════════════════\n";
    cout << "      MANACHER'S ALGORITHM DEMO\n";
    cout << "══════════════════════════════════\n";

    // ── Test 1: Classic example ──────────────
    {
        string s = "babad";
        Manacher m(s);
        cout << "\nInput: \"" << s << "\"\n";
        m.printTable();
        cout << "Longest palindrome   : \"" << m.longestPalindrome() << "\"\n";
        cout << "Total palindrome count: " << m.countPalindromes() << "\n";
    }

    // ── Test 2: Even-length palindrome ───────
    {
        string s = "cbbd";
        Manacher m(s);
        cout << "\nInput: \"" << s << "\"\n";
        m.printTable();
        cout << "Longest palindrome   : \"" << m.longestPalindrome() << "\"\n";
    }

    // ── Test 3: Entire string is a palindrome
    {
        string s = "racecar";
        Manacher m(s);
        cout << "\nInput: \"" << s << "\"\n";
        m.printTable();
        cout << "Longest palindrome   : \"" << m.longestPalindrome() << "\"\n";
        cout << "Total palindrome count: " << m.countPalindromes() << "\n";
    }

    // ── Test 4: All characters same ──────────
    {
        string s = "aaaa";
        Manacher m(s);
        cout << "\nInput: \"" << s << "\"\n";
        m.printTable();
        cout << "Longest palindrome   : \"" << m.longestPalindrome() << "\"\n";
        cout << "Total palindrome count: " << m.countPalindromes() << "\n";
    }

    // ── Test 5: Long mixed string ────────────
    {
        string s = "abacabadabacaba";
        Manacher m(s);
        cout << "\nInput: \"" << s << "\"\n";
        cout << "Longest palindrome   : \"" << m.longestPalindrome() << "\"\n";
        cout << "Total palindrome count: " << m.countPalindromes() << "\n";
    }

    return 0;
}